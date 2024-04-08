/*

ZamLDEV.cpp

Ce fichier est un des elements constituant un ensemble de logiciels de controle-commande de processus industriels developpes en C++ standard et en Python
 par la Societe ZAMIREN (http://zamiren.fr).
Ces developpements s’appuient sur les normes de l’IEC et en particulier la norme IEC 61850 ainsi que sur des standards en matiere de composants C++ ou Python.
La mise en œuvre de la norme IEC61850 repose sur la bibliotheque "LIBIEC61850" developpee et geree par MZ Automation GmbH (http://libiec61850.com). 
La liste complete des sources est fournie dans le fichier « sources_zamiren.txt »
*/

#include "ZamLDEV.hpp"
#include "ZamReport.hpp"
#include "ZamLPHD.hpp"
#include "ZamLLN0.hpp"
#include "ZamDEEVP.hpp"

CZamLDEV::CZamLDEV ()
{
}

CZamLDEV::~CZamLDEV ()
{
}

int CZamLDEV::Demarrage ()
{
	try
	{
		m_lphd = static_pointer_cast<CZamLPHD>(m_de["LPHD1"]);
		m_lln0 = static_pointer_cast<CZamLLN0>(m_de["LLN0"]);
		m_deev = static_pointer_cast<CZamDEEVP>(m_de["DEEV1"]);
		if (m_lphd->Demarrage()) throw string("Pb lancement lphd");
		if (m_lln0->Demarrage()) throw string("Pb lancement lln0");
		m_IED = m_zp->m_nomied;
		m_LD = m_IED + m_nom + "/";
		if (m_deev->Demarrage()) throw string("Pb lancement deev");
		auto zcb(make_shared<CZamReport>());
		m_zcb = zcb;
		m_zcb->m_zs = m_zs;
		m_zcb->m_zp = m_zp;
		m_zcb->m_zl = m_zl;
		m_zcb->m_adresse = m_adresse_ve;
		m_zcb->m_inst = m_inst;
		m_zcb->m_nom = "IEDEV";
		if (Lance()) throw string("Pb lancement boucle LDEV");
		m_zcb->Demarrage();
	}
	catch (string exc)
	{
		m_zl->info(fmt::format("Exception dans LDEV Demarrage: ", exc));
	}
	return 0;
}

int CZamLDEV::Lance ()
{
	m_stop= false;
	thread thr(&CZamLDEV::ZamProc, this, 1);
	thr.detach();
	return 0;
}

bool CZamLDEV::Initialisation ()
{
	this_thread::sleep_for(chrono::seconds(5));
	return true;
} // Initialisation

void CZamLDEV::ZamProc (int i)
{
	try
	{
		if (Initialisation ())
		{
			while (true)
			{
				if (m_stop)
				{
					return;
				}
// Beh est impose par LDEVSE
// OFF fonction inactive
				if ((m_ibeh == 2) || (m_ibeh == 5)) goto finboucle;
// fonction active
// rien a faire !!
			finboucle:
				this_thread::sleep_for(chrono::seconds(2));
			} // boucle
		} // if init
		else
		{
			m_zl->info(fmt::format(" {}: Init impossible", m_nom));
		}
	}
	catch (string exc)
	{
		m_zl->info(fmt::format("Exception dans LDEV Demarrage : ", exc));
	}
	m_zl->info(fmt::format("{}: Arret du programme", m_nom));
} // ZamProcess
