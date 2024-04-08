/*

ZamEnumType.hpp

Ce fichier est un des elements constituant un ensemble de logiciels de controle-commande de processus industriels developpes en C++ standard et en Python
 par la Societe ZAMIREN (http://zamiren.fr).
Ces developpements s�appuient sur les normes de l�IEC et en particulier la norme IEC 61850 ainsi que sur des standards en matiere de composants C++ ou Python.
La mise en �uvre de la norme IEC61850 repose sur la bibliotheque "LIBIEC61850" developpee et geree par MZ Automation GmbH (http://libiec61850.com). 
La liste complete des sources est fournie dans le fichier � sources_zamiren.txt �
*/

#pragma once

#include <string>
#include <map>
#include "ZamEnumVal.hpp"

using namespace std;

class CZamEnumType
{
public:
	CZamEnumType();
	virtual ~CZamEnumType();
public:
	string id;
	map<string, shared_ptr<CZamEnumVal>> mapenumval;
};



CZamEnumType::CZamEnumType()
{
}


CZamEnumType::~CZamEnumType()
{
}
