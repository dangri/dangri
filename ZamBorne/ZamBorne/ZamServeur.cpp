/*

ZamServeur.cpp

Ce fichier est un des elements constituant un ensemble de logiciels de controle-commande de processus industriels developpes en C++ standard et en Python
 par la Societe ZAMIREN (http://zamiren.fr).
Ces developpements s’appuient sur les normes de l’IEC et en particulier la norme IEC 61850 ainsi que sur des standards en matiere de composants C++ ou Python.
La mise en œuvre de la norme IEC61850 repose sur la bibliotheque "LIBIEC61850" developpee et geree par MZ Automation GmbH (http://libiec61850.com). 
La liste complete des sources est fournie dans le fichier « sources_zamiren.txt »
*/

#include "ZamServeur.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>
#include "ParamCmd.h"
#include "pugixml.hpp"
#include <boost/interprocess/shared_memory_object.hpp>
#include "ZamProcess.hpp"
#include "ZamLLN0.hpp"

using namespace std;

using namespace pugi;

CZamServer::CZamServer()
{
}

CZamServer::~CZamServer()
{
}

int CZamServer::Demarrage()
{
	int err = 0;
	m_start = false;
	Conf();
	err = Lance();
	if (err != 0)
	{
		m_zl->info("Probleme au lancement du Serveur");
		return -2;
	}
	while (!m_start)
	{
		this_thread::sleep_for(chrono::milliseconds(200));

	}
	return 0;
}

int CZamServer::Conf()
{
	int err = 0;
	/* Create new server configuration object */
	m_config = IedServerConfig_create();
	/* Set buffer size for buffered report control blocks to 200000 bytes */
	IedServerConfig_setReportBufferSize(m_config, 200000);
	/* Set stack compliance to a specific edition of the standard (WARNING: data model has also to be checked for compliance) */
	IedServerConfig_setEdition(m_config, IEC_61850_EDITION_2_1);
	/* Set the base path for the MMS file services */
	IedServerConfig_setFileServiceBasePath(m_config, "./vmd-filestore/");
	/* disable MMS file service */
	IedServerConfig_enableFileService(m_config, false);
	/* enable dynamic data set service */
	IedServerConfig_enableDynamicDataSetService(m_config, true);
	/* disable log service */
	IedServerConfig_enableLogService(m_config, false);
	/* set maximum number of clients */
	IedServerConfig_setMaxMmsConnections(m_config, 15);
	return err;
}

int CZamServer::Lance()
{
	int err = 0;
	thread thr(&CZamServer::ZamProc, this, 1);
	thr.detach();
	return err;
}

//static CheckHandlerResult checkHandler(ControlAction action, void *parameter, MmsValue *ctlVal, bool test, bool interlockCheck)
//{
//	int err = -1;
//	CParamCmd *cpc = static_cast<CParamCmd *>(parameter);
//	CZamServer *ps = (CZamServer *)cpc->pthis;
//	int nc = cpc->nc;
//	err = ps->HandlerCheck(nc, value, test);
//	if (ControlAction_isSelect(action)) cout << "check select ";
//	else ps->cout << "check operate ";
//	if (interlockCheck) ps->cout << "with interlock ";
//	ps->cout << "ctlNum: " << ControlAction_getCtlNum(action) << " ";
//	switch (nc)
//	{
//		case 1:
//			ps->cout << "LDCS.FSCH1.EnaReq" << endl;
//			return CONTROL_ACCEPTED;
//			break;
//		case 2:
//			ps->cout << "LDCS.FSCH1.DsaReq" << endl;
//			return CONTROL_ACCEPTED;
//			break;
//		case 3:
//			ps->cout << "LDCS.FSCH2.EnaReq" << endl;
//			return CONTROL_ACCEPTED;
//			break;
//		case 4:
//			ps->cout << "LDCS.FSCH2.DsaReq" << endl;
//			return CONTROL_ACCEPTED;
//			break;
//		case 5:
//			ps->cout << "LDCS.LLN0.Mod" << endl;
//			return CONTROL_ACCEPTED;
//			break;
//		case 6:
//			ps->cout << "LDEVSE1.LLN0.Mod" << endl;
//			return CONTROL_ACCEPTED;
//			break;
//		case 7:
//			ps->cout << "LDEVSE2.LLN0.Mod" << endl;
//			return CONTROL_ACCEPTED;
//			break;
//		default:
//			ps->cout << "Objet inconnu" << endl;
//			return CONTROL_OBJECT_UNDEFINED;
//			break;
//	}
//	return CONTROL_OBJECT_UNDEFINED;
//}

static ControlHandlerResult controlHandler(ControlAction ctlact, void* parameter, MmsValue* value, bool test)
{
	int err = -1;
	CParamCmd *cpc = static_cast<CParamCmd*>(parameter);
	CZamServer *ps = (CZamServer*) cpc->pthis;
	int nc = cpc->nc;
	err = ps->HandlerCommande(nc, value, test);
	if (err)
	{
		return CONTROL_RESULT_FAILED;
	}
	return CONTROL_RESULT_OK;
}


void CZamServer::ZamProc(int i)
{
	try
	{
		m_zl->info(fmt::format("Using libIEC61850 version {}", LibIEC61850_getVersionString()));
		/* Create new server configuration object */
		IedServerConfig config = IedServerConfig_create();
		/* Set buffer size for buffered report control blocks to 200000 bytes */
		IedServerConfig_setReportBufferSize(config, 200000);
		/* Set stack compliance to a specific edition of the standard (WARNING: data model has also to be checked for compliance) */
		IedServerConfig_setEdition(config, IEC_61850_EDITION_2);
		/* Set the base path for the MMS file services */
		IedServerConfig_setFileServiceBasePath(config, "./vmd-filestore/");
		/* disable MMS file service */
		IedServerConfig_enableFileService(config, false);
		/* enable dynamic data set service */
		IedServerConfig_enableDynamicDataSetService(config, true);
		/* disable log service */
		IedServerConfig_enableLogService(config, false);
		/* set maximum number of clients */
		IedServerConfig_setMaxMmsConnections(config, 10);
		/* Create a new IEC 61850 server instance */

//		cout << "entree ZamProc OK" << endl;
		m_nomcfg = m_nomied + ".cfg";
		FileHandle configFile = FileSystem_openFile((char*) m_nomcfg.data(), false);
		if (configFile == nullptr)
		{
			throw string("Erreur ouverture du fichier .cfg");
		}
		m_model = ConfigFileParser_createModelFromConfigFile(configFile);
		FileSystem_closeFile(configFile);
		if (m_model == nullptr)
		{
			throw string("Erreur creation du modele");
		}
//		cout << "creation du modele OK" << endl;
		m_server = IedServer_create(m_model);
		IedServerConfig_destroy(m_config);
		IedServer_start(m_server, m_tcpPort);
		if (!IedServer_isRunning(m_server))
		{
			IedServer_destroy(m_server);
			throw string("Probleme au demarrage du serveur");
		}
// Commandes
		m_fsch01_EnaReq = (DataObject *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH1.EnaReq");
		m_fsch01_DsaReq = (DataObject *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH1.DsaReq");
		m_fsch02_EnaReq = (DataObject *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH2.EnaReq");
		m_fsch02_DsaReq = (DataObject *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH2.DsaReq");
		m_evse_Mod = (DataObject *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/LLN0.Mod");
		m_dpmc_WLimSpt1 = (DataObject *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/DPMC1.WLimSpt1");
		CParamCmd pcmd01, pcmd02, pcmd03, pcmd04, pcmd05, pcmd06;
		pcmd01.pthis = this;
		pcmd01.nc = 1;
		IedServer_setControlHandler(m_server, m_fsch01_EnaReq, (ControlHandler) controlHandler, (void*) &pcmd01);
		pcmd02.pthis = this;
		pcmd02.nc = 2;
		IedServer_setControlHandler(m_server, m_fsch01_DsaReq, (ControlHandler) controlHandler, (void*) &pcmd02);
		pcmd03.pthis = this;
		pcmd03.nc = 3;
		IedServer_setControlHandler(m_server, m_fsch02_EnaReq, (ControlHandler) controlHandler, (void*) &pcmd03);
		pcmd04.pthis = this;
		pcmd04.nc = 4;
		IedServer_setControlHandler(m_server, m_fsch02_DsaReq, (ControlHandler) controlHandler, (void*) &pcmd04);
		pcmd05.pthis = this;
		pcmd05.nc = 5;
		IedServer_setControlHandler(m_server, m_evse_Mod, (ControlHandler) controlHandler, (void *) &pcmd05);
		pcmd06.pthis = this;
		pcmd06.nc = 6;
		IedServer_setControlHandler(m_server, m_dpmc_WLimSpt1, (ControlHandler)controlHandler, (void *)&pcmd06);
//		cout << "Serveur Operationnel sur le port " << to_string(tcpPort) << endl;
// Boucle
		while (true)
		{
			if (!m_start) m_start = true;
			if (m_stop) break;
			this_thread::sleep_for(chrono::milliseconds(10));
		}
// Boucle
		m_zl->info(fmt::format("Arret du serveur"));
		IedServer_stop(m_server);
		IedServer_destroy(m_server);
		IedModel_destroy(m_model);
	}	// try
	catch(string exc)
	{
		m_zl->info(fmt::format("Exception {}", exc));
	}
	catch(exception e)
	{
		m_zl->info(fmt::format("Exception {}",string(e.what())));
	}
	catch(...)
	{
		m_zl->info(fmt::format("Exception ..."));
	}
}


static void connectionHandler(IedServer m_server, ClientConnection connection, bool connected, void* parameter)
{
//	if (connected)
//		cout << "Connexion" << endl;
//	else
//		cout << "Deconnexion" << endl;
}

int CZamServer::HandlerCommande(int nc, MmsValue* value, bool test)
{
	int err = 0;
	int beh;
	DataAttribute *patc, *pavc;
	uint64_t timestamp = Hal_getTimeInMs();
	bool b;
	switch (nc)
	{
	case 1:
// Enable FSCH1
		{
			beh = IedServer_getUInt32AttributeValue(m_server, (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH1.Beh.stVal"));
			if ((beh == 2) || (beh == 5)) // Blocked ou OFF
			{
				err = 1;
				break;
			}
			if (!test && (beh == 3)) // mod test at commende non test
			{
				err = 2;
				break;
			}
			if (test && beh == 4) // Mod test blocked
			{
				err = 3;
				break;
			}
			patc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH1.EnaReq.t");
			pavc = (DataAttribute*) IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH1.EnaReq.stVal");
			if (!test)
			{
				IedServer_updateUTCTimeAttributeValue(m_server, patc, timestamp);
				b = MmsValue_getBoolean(value);
				IedServer_updateBooleanAttributeValue(m_server, pavc, b);
			}
		}
		break;
	case 2:
//Disable FSCH1
		{
			beh = IedServer_getUInt32AttributeValue(m_server, (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH1.Beh.stVal"));
			if ((beh == 2) || (beh == 5))			
			{
				err = 1;
				break;
			}
			patc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH1.DsaReq.t");
			pavc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH1.DsaReq.stVal");
			if (!test)
			{
				IedServer_updateUTCTimeAttributeValue(m_server, patc, timestamp);
				b = MmsValue_getBoolean(value);
				IedServer_updateBooleanAttributeValue(m_server, pavc, b);
			}
		}
		break;
	case 3:
// Enable FSCH2
		{
			beh = IedServer_getUInt32AttributeValue(m_server, (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH2.Beh.stVal"));
			if ((beh == 2) || (beh == 5))			
			{
				err = 1;
				break;
			}
			patc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH2.EnaReq.t");
			pavc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH2.EnaReq.stVal");
			if (!test)
			{
				IedServer_updateUTCTimeAttributeValue(m_server, patc, timestamp);
				b = MmsValue_getBoolean(value);
				IedServer_updateBooleanAttributeValue(m_server, pavc, b);
			}
		}
		break;
	case 4:
//Disable FSCH2
		{
			beh = IedServer_getUInt32AttributeValue(m_server, (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH2.Beh.stVal"));
			if ((beh == 2) || (beh == 5))			
			{
				err = 1;
				break;
			}
			patc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH2.DsaReq.t");
			pavc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/FSCH2.DsaReq.stVal");
			if (!test)
			{
				IedServer_updateUTCTimeAttributeValue(m_server, patc, timestamp);
				b = MmsValue_getBoolean(value);
				IedServer_updateBooleanAttributeValue(m_server, pavc, b);
			}
		}
		break;
// LLNO.Mod
	case 5:
		{
			patc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/LLN0.Mod.t");
			pavc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/LLN0.Mod.stVal");
			if (!test)
			{
				IedServer_updateUTCTimeAttributeValue(m_server, patc, timestamp);
				IedServer_updateAttributeValue(m_server, pavc, value);
			}
		}
		break;
// DPMC
	case 6:
		{
			patc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/DPMC1.WLimSpt1.t");
			pavc = (DataAttribute *)IedModel_getModelNodeByShortObjectReference(m_model, "LDEVSE/DPMC1.WLimSpt1.mxVal");
			if (!test)
			{
				IedServer_updateUTCTimeAttributeValue(m_server, patc, timestamp);
				IedServer_updateAttributeValue(m_server, pavc, value);
			}
		}
		break;
	default:
		err = 1;
	}
	return err;
}



bool CZamServer::Litb(const string& sref)
{
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Litb {}", sref));
	return IedServer_getBooleanAttributeValue(m_server, dav);		
}

int CZamServer::Liti(const string& sref)
{
//	sem_wait(m_sem);
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav)
		m_zl->info(fmt::format("pb Liti {}", sref));
	int val = IedServer_getUInt32AttributeValue(m_server, dav);
//	sem_post(m_sem);
	return val;
}

unsigned int CZamServer::Litui(const string& sref)
{
//	sem_wait(m_sem);
	DataAttribute* dav = (DataAttribute*)IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Litui {}", sref));
	int val = IedServer_getUInt32AttributeValue(m_server, dav);
//	sem_post(m_sem);
	return val;
}

float CZamServer::Litf(const string& sref)
{
//	sem_wait(m_sem);
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav)
		m_zl->info(fmt::format("pb Litf {}", sref));
	//	sem_post(m_sem);
	return IedServer_getFloatAttributeValue(m_server, dav);		
}

double CZamServer::Litd(const string& sref)
{
//	sem_wait(m_sem);
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Litd {}", sref));
	//	sem_post(m_sem);
	return IedServer_getFloatAttributeValue(m_server, dav);		
}

string CZamServer::Lits(const string& sref)
{
//	sem_wait(m_sem);
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Lits {}", sref));
	//	sem_post(m_sem);
	return string(IedServer_getStringAttributeValue(m_server, dav));		
}

unsigned long long CZamServer::Litull(const string &sref)
{
//	sem_wait(m_sem);
	DataAttribute *dav = (DataAttribute *)IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Litull {}", sref));
	//	sem_post(m_sem);
	return IedServer_getUTCTimeAttributeValue(m_server, dav);
}

void CZamServer::Ecrit(const string &doref, const string& daref, bool b)
{
//	sem_wait(m_sem);
	string sref = doref + "." + daref;
	string tref = doref + ".t";
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Ecrit {}", sref));
	DataAttribute *dat = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, tref.data());
	IedServer_lockDataModel(m_server);
	IedServer_updateBooleanAttributeValue(m_server, dav, b);
	if (dat) MmsValue_setUtcTimeMs(dat->mmsValue, Hal_getTimeInMs());
	IedServer_unlockDataModel(m_server);
//	sem_post(m_sem);
}

void CZamServer::Ecrit(const string &doref, const string& daref, int i)
{
//	sem_wait(m_sem);
	string sref = doref + "." + daref;
	string tref = doref + ".t";
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Ecrit {}", sref));
	DataAttribute *dat = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, tref.data());
	IedServer_lockDataModel(m_server);
	IedServer_updateInt32AttributeValue(m_server, dav, i);
	if (dat) MmsValue_setUtcTimeMs(dat->mmsValue, Hal_getTimeInMs());
	IedServer_unlockDataModel(m_server);
//	sem_post(m_sem);
}

void CZamServer::Ecrit(const string &doref, const string& daref, float f)
{
//	sem_wait(m_sem);
	string sref = doref + "." + daref;
	string tref = doref + ".t";
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Ecrit {}", sref));
	DataAttribute* dat = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, tref.data());
	IedServer_lockDataModel(m_server);
	IedServer_updateFloatAttributeValue(m_server, dav, f);
	if (dat) MmsValue_setUtcTimeMs(dat->mmsValue, Hal_getTimeInMs());
	IedServer_unlockDataModel(m_server);
//	sem_post(m_sem);
}

void CZamServer::Ecrit(const string &doref, const string& daref, double d)
{
//	sem_wait(m_sem);
	string sref = doref + "." + daref;
	string tref = doref + ".t";
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Ecrit {}", sref));
	DataAttribute *dat = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, tref.data());
	IedServer_lockDataModel(m_server);
	IedServer_updateFloatAttributeValue(m_server, dav, d);
	if (dat) MmsValue_setUtcTimeMs(dat->mmsValue, Hal_getTimeInMs());
	IedServer_unlockDataModel(m_server);
//	sem_post(m_sem);
}

void CZamServer::Ecrit(const string &doref, const string& daref, string& s)
{
//	sem_wait(m_sem);
	string sref = doref + "." + daref;
	string tref = doref + ".t";
	DataAttribute* dav = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Ecrit {}", sref));
	DataAttribute *dat = (DataAttribute*) IedModel_getModelNodeByObjectReference(m_model, tref.data());
//	MmsValue* mmsval = MmsValue_newMmsString(s.data());
	IedServer_lockDataModel(m_server);
//	IedServer_updateAttributeValue(m_server, dav, mmsval);
	IedServer_updateVisibleStringAttributeValue(m_server, dav, s.data());			
	if(dat) MmsValue_setUtcTimeMs(dat->mmsValue, Hal_getTimeInMs());
	IedServer_unlockDataModel(m_server);
//	sem_post(m_sem);
}

void CZamServer::Ecrit(const string &doref, const string &daref, unsigned long long u)
{
//	sem_wait(m_sem);
	string sref = doref + "." + daref;
	string tref = doref + ".t";
	DataAttribute *dav = (DataAttribute *)IedModel_getModelNodeByObjectReference(m_model, sref.data());
	if (!dav) m_zl->info(fmt::format("pb Ecrit {}", sref));
	DataAttribute *dat = (DataAttribute *)IedModel_getModelNodeByObjectReference(m_model, tref.data());
	IedServer_lockDataModel(m_server);
	IedServer_updateUTCTimeAttributeValue(m_server, dav, u);
	if (dat) MmsValue_setUtcTimeMs(dat->mmsValue, Hal_getTimeInMs());
	IedServer_unlockDataModel(m_server);
//	sem_post(m_sem);
}

float CZamServer::Litmag(const string &phsref)
{
	float f;
	int i;
	string phs = phsref.substr(phsref.length() - 1);
	if (phs == "A") i = 0;
	if (phs == "B") i = 1;
	if (phs == "C") i = 2;
	string pnvref = phsref.substr(0, phsref.length() - 5);
	DataObject *pnv = (DataObject *)IedModel_getModelNodeByObjectReference(m_model, pnvref.data());
	MmsValue *mpnv = IedServer_getFunctionalConstrainedData(m_server, pnv, IEC61850_FC_MX);
	MmsValue *mphs = MmsValue_getElement(mpnv, i);
	MmsValue *cval = MmsValue_getElement(mphs, 0);
	MmsValue *cmv = MmsValue_getElement(cval, 0);
	MmsValue *cValElement = MmsValue_getElement(cmv, 0);
	assert(MmsValue_getArraySize(cValElement) == 2);
	MmsValue *cValElement1 = MmsValue_getElement(cValElement, 0);
	MmsValue *cValElement2 = MmsValue_getElement(cValElement1, 0);
	MmsValue *cValElement_mag_f = MmsValue_getElement(cValElement2, 0);
	f = MmsValue_toFloat(cValElement_mag_f);
	return f;
}

void CZamServer::Ecritmag(const string &phsref, float f)
{
	string pnvref = phsref.substr(0, phsref.length() - 5);
	int i;
	string phs = phsref.substr(phsref.length() - 1);
	if (phs == "A") i = 0;
	if (phs == "B") i = 1;
	if (phs == "C") i = 2;
	DataObject *pnv = (DataObject *)IedModel_getModelNodeByObjectReference(m_model, pnvref.data());
	MmsValue *mpnv = IedServer_getFunctionalConstrainedData(m_server, pnv, IEC61850_FC_MX);
	MmsValue *mphs = MmsValue_getElement(mpnv, i);
	MmsValue *cval = MmsValue_getElement(mphs, 0);
	MmsValue *cmv = MmsValue_getElement(cval, 0);
	MmsValue *cValElement = MmsValue_getElement(cmv, 0);
	assert(MmsValue_getArraySize(cValElement) == 2);
	MmsValue *cValElement1 = MmsValue_getElement(cValElement, 0);
	MmsValue *cValElement2 = MmsValue_getElement(cValElement1, 0);
	MmsValue *cValElement_mag_f = MmsValue_getElement(cValElement2, 0);
	MmsValue_setFloat(cValElement_mag_f, f);
	return;
}

float CZamServer::Litang(const string &phsref)
{
	float f;
	int i;
	string phs = phsref.substr(phsref.length() - 1);
	if (phs == "A") i = 0;
	if (phs == "B") i = 1;
	if (phs == "C") i = 2;
	string pnvref = phsref.substr(0, phsref.length() - 5);
	DataObject *pnv = (DataObject *)IedModel_getModelNodeByObjectReference(m_model, pnvref.data());
	MmsValue *mpnv = IedServer_getFunctionalConstrainedData(m_server, pnv, IEC61850_FC_MX);
	MmsValue *mphs = MmsValue_getElement(mpnv, i);
	MmsValue *cval = MmsValue_getElement(mphs, 0);
	MmsValue *cmv = MmsValue_getElement(cval, 0);
	MmsValue *cValElement = MmsValue_getElement(cmv, 0);
	assert(MmsValue_getArraySize(cValElement) == 2);
	MmsValue *cValElement1 = MmsValue_getElement(cValElement, 0);
	MmsValue *cValElement2 = MmsValue_getElement(cValElement1, 0);
	MmsValue *cValElement_mag_f = MmsValue_getElement(cValElement2, 0);
	MmsValue *cValElement3 = MmsValue_getElement(cValElement, 1);
	MmsValue *cValElement4 = MmsValue_getElement(cValElement3, 0);
	MmsValue *cValElement_ang_f = MmsValue_getElement(cValElement4, 0);
	f = MmsValue_toFloat(cValElement_ang_f);
	return f;
}

void CZamServer::Ecritang(const string &phsref, float f)
{
	string pnvref = phsref.substr(0, phsref.length() - 5);
	int i;
	string phs = phsref.substr(phsref.length() - 1);
	if (phs == "A") i = 0;
	if (phs == "B") i = 1;
	if (phs == "C") i = 2;
	DataObject *pnv = (DataObject *)IedModel_getModelNodeByObjectReference(m_model, pnvref.data());
	MmsValue *mpnv = IedServer_getFunctionalConstrainedData(m_server, pnv, IEC61850_FC_MX);
	MmsValue *mphs = MmsValue_getElement(mpnv, i);
	MmsValue *cval = MmsValue_getElement(mphs, 0);
	MmsValue *cmv = MmsValue_getElement(cval, 0);
	MmsValue *cValElement = MmsValue_getElement(cmv, 0);
	assert(MmsValue_getArraySize(cValElement) == 2);
	MmsValue *cValElement1 = MmsValue_getElement(cValElement, 0);
	MmsValue *cValElement2 = MmsValue_getElement(cValElement1, 0);
	MmsValue *cValElement_mag_f = MmsValue_getElement(cValElement2, 0);
	MmsValue *cValElement3 = MmsValue_getElement(cValElement, 1);
	MmsValue *cValElement4 = MmsValue_getElement(cValElement3, 0);
	MmsValue *cValElement_ang_f = MmsValue_getElement(cValElement4, 0);
	MmsValue_setFloat(cValElement_ang_f, f);
	return;
}
