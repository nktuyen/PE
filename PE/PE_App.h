
// PE.h : main header file for the PROJECT_NAME application
//

#pragma once

#define	__AFXWIN_H__
#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <afx.h>

// CPEApp:
// See PE.cpp for the implementation of this class
//

class PE_App : public CWinApp
{
public:
	PE_App();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern PE_App theApp;