
// AdderMFC.h : fichier d'en-tête principal de l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'pch.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux


// CAdderMFCApp :
// Consultez AdderMFC.cpp pour l'implémentation de cette classe
//

class CAdderMFCApp : public CWinApp
{
public:
	CAdderMFCApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CAdderMFCApp theApp;
