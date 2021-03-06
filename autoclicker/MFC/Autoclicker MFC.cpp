// Autoclicker MFC
// Copyright 2016 Michael Lin
// Autoclicker MFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Autoclicker MFC.h"
#include "Autoclicker MFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAutoclickerMFCApp

BEGIN_MESSAGE_MAP(CAutoclickerMFCApp, CWinApp)
	ON_COMMAND(ID_FILE_QUIT32772, &CAutoclickerMFCApp::OnFileQuit32772)
	ON_COMMAND(ID_HELP_ABOUT, &CAutoclickerMFCApp::OnHelpAbout)
END_MESSAGE_MAP()


// CAutoclickerMFCApp construction

CAutoclickerMFCApp::CAutoclickerMFCApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// Place all significant initialization in InitInstance
}


// The one and only CAutoclickerMFCApp object

CAutoclickerMFCApp theApp;


// CAutoclickerMFCApp initialization

BOOL CAutoclickerMFCApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// SetRegistryKey(_T("Autoclicker MFC"));

	CAutoclickerMFCDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



void CAutoclickerMFCApp::OnFileQuit32772()
//Quit option in menu bar
{
	PostQuitMessage(0);
}


void CAutoclickerMFCApp::OnHelpAbout()
//About option in menu bar
{
	AfxMessageBox(_T("Autoclicker MFC\nCopyright 2016 Michael Lin"), MB_OK | MB_ICONINFORMATION);
}


//Prevents escape or enter key closing the main window by overriding PreTranslateMessage (solution from stackoverflow)
BOOL CAutoclickerMFCApp::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}
	return CWinApp::PreTranslateMessage(pMsg);
}