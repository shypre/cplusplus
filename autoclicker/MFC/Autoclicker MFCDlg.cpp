
// Autoclicker MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualKeys.h"
#include "Autoclicker MFC.h"
#include "Autoclicker MFCDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <string>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoclickerMFCDlg dialog



CAutoclickerMFCDlg::CAutoclickerMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTOCLICKERMFC_DIALOG, pParent)
	, Radio1(0)
	, CStr_IDC_EDIT1(_T(""))
	, Hotkeystr("")
	, Stopkeystr("")
	, Clicktime("")
	, Duration("")
	, ComboBoxChoice(0)
	, XCoordstr("")
	, YCoordstr("")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoclickerMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, Radio1);
	DDX_Text(pDX, IDC_EDIT1, CStr_IDC_EDIT1);
	DDX_Text(pDX, IDC_EDIT2, Hotkeystr);
	//DDV_MaxChars(pDX, Hotkey, 8);
	DDX_Text(pDX, IDC_EDIT3, Stopkeystr);
	//DDV_MaxChars(pDX, Stopkey, 8);
	DDX_Text(pDX, IDC_EDIT4, Clicktime);
	//DDV_MaxChars(pDX, Clicktime, 8);
	DDX_Text(pDX, IDC_EDIT5, Duration);
	//DDV_MaxChars(pDX, Duration, 8);
	DDX_CBIndex(pDX, IDC_COMBO1, ComboBoxChoice);
	DDX_Text(pDX, IDC_EDIT6, XCoordstr);
	DDX_Text(pDX, IDC_EDIT7, YCoordstr);
}

BEGIN_MESSAGE_MAP(CAutoclickerMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CAutoclickerMFCDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAutoclickerMFCDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoclickerMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoclickerMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAutoclickerMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAutoclickerMFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAutoclickerMFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAutoclickerMFCDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CAutoclickerMFCDlg message handlers

BOOL CAutoclickerMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	for (int i = 0; i < 177; ++i)
	{
		if (VKeyList[i].VKey == 162)
		{
			Hotkeystr = VKeyList[i].Description;
		}
		if (VKeyList[i].VKey == 160)
		{
			Stopkeystr = VKeyList[i].Description;
		}
	}
	Clicktime = std::to_string(100).c_str();
	Duration = std::to_string(50).c_str();
	XCoordstr = _T("0");
	YCoordstr = _T("0");
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAutoclickerMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAutoclickerMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAutoclickerMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


typedef struct ClickingInfoStruct
{
	INPUT Input { 0 };
	volatile BOOL isRunning = FALSE;
	UINT Hotkey = 0xA2;
	UINT Stopkey = 0xA0;
	UINT Clicktime = 100;
	INT Duration = 50;
	DWORD InputFlags1 = MOUSEEVENTF_LEFTDOWN;
	DWORD InputFlags2 = MOUSEEVENTF_LEFTUP;
} ClickingInfo;

static ClickingInfo *ClickingInfoptr = new ClickingInfo;


static UINT StartAutoclick(LPVOID pParam)
{
	static ClickingInfo *theParam = static_cast<ClickingInfo*> (pParam);
	theParam->isRunning = TRUE;
	ZeroMemory(&(theParam->Input), sizeof(theParam->Input));
	while (theParam->isRunning == TRUE)
	{
		if (GetAsyncKeyState(theParam->Stopkey) < 0)
		{
			break;
		}
		if (GetAsyncKeyState(theParam->Hotkey) < 0)
		{
			if (theParam->InputFlags2 == 0)
			{
				theParam->Input.mi.mouseData = theParam->Duration;
			}
			theParam->Input.mi.dwFlags = theParam->InputFlags1;
			SendInput(1, &(theParam->Input), sizeof(INPUT));
			if (theParam->InputFlags2 != 0)
			{
				Sleep(theParam->Clicktime);
				theParam->Input.mi.dwFlags = theParam->InputFlags2;
				SendInput(1, &(theParam->Input), sizeof(INPUT));
			}
		}
		Sleep(theParam->Clicktime - theParam->Duration);
	}
	static CString msgboxstr1 = _T("Thread 1 has finished");
	AfxMessageBox(msgboxstr1);
	return 0;
}


void CAutoclickerMFCDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgRadio1 = _T("Radio button 1 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgRadio1;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	static CString disablecoordbox = _T("X and Y coordinate boxes disabled. ");
	CStr_IDC_EDIT1 += disablecoordbox;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
}


void CAutoclickerMFCDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgRadio2 = _T("Radio button 2 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgRadio2;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
	static CString enablecoordbox = _T("X and Y coordinate boxes enabled. ");
	CStr_IDC_EDIT1 += enablecoordbox;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
}


void CAutoclickerMFCDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton1 = _T("Push button 1 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton1;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	UpdateData(FALSE);
	if (ClickingInfoptr->isRunning == FALSE)
	{
		CWinThread *pThread = AfxBeginThread(StartAutoclick, static_cast<LPVOID>(ClickingInfoptr));
		static CString ThreadStart1 = _T("Thread 1 has started. ");
		CStr_IDC_EDIT1 += ThreadStart1;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	}
	else
	{
		CString msgboxstr2 = _T("Thread 1 is already running!");
		AfxMessageBox(msgboxstr2);
	}
}


void CAutoclickerMFCDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton2 = _T("Push button 2 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton2;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	ClickingInfoptr->isRunning = FALSE;
}



void CAutoclickerMFCDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
}


void CAutoclickerMFCDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
}


void CAutoclickerMFCDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton5 = _T("Push button 5 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton5;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	UpdateData(TRUE);
	if (_ttoi(Duration) >= _ttoi(Clicktime) && (ComboBoxChoice != 2))
	{
		CStr_IDC_EDIT1 += "Error: Duration is not less than Time between clicks, changing Duration to half of Time between clicks. ";
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
		TCHAR *buffer = new TCHAR[30];
		Duration = _itot(_ttoi(Clicktime) / 2, buffer, 10);
		delete[] buffer;
	}
	ClickingInfoptr->Clicktime = abs(_ttoi(Clicktime));
	ClickingInfoptr->Duration = _ttoi(Duration);
	UINT Hotkey, Stopkey;
	for (int i = 0; i < 177; ++i)
	{
		
		if (Hotkeystr == VKeyList[i].Description)
		{
			Hotkey = VKeyList[i].VKey;
			ClickingInfoptr->Hotkey = Hotkey;
			break;
		}
		else if (abs(_ttoi(Hotkeystr)) == VKeyList[i].VKey)
		{
			Hotkey = VKeyList[i].VKey;
			ClickingInfoptr->Hotkey = Hotkey;
			Hotkeystr = VKeyList[i].Description;
			break;
		}
		if (i == 176)
		{
			static CString nomatchmsg1 = _T("Hotkey was not assigned, check key spelling. ");
			CStr_IDC_EDIT1 += nomatchmsg1;
			SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
			break;
		}
	}
	for (int i = 0; i < 177; ++i)
	{
		
		if (Stopkeystr == VKeyList[i].Description)
		{
			Stopkey = VKeyList[i].VKey;
			ClickingInfoptr->Stopkey = Stopkey;
			break;
		}
		else if (abs(_ttoi(Stopkeystr)) == VKeyList[i].VKey)
		{
			Stopkey = VKeyList[i].VKey;
			ClickingInfoptr->Stopkey = Stopkey;
			Stopkeystr = VKeyList[i].Description;
			break;
		}
		if (i == 176)
		{
			static CString nomatchmsg2 = _T("Stopkey was not assigned, check key spelling. ");
			CStr_IDC_EDIT1 += nomatchmsg2;
			SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
			break;
		}
	}
	if (ComboBoxChoice == 0)
	{
		ClickingInfoptr->InputFlags1 = MOUSEEVENTF_LEFTDOWN;
		ClickingInfoptr->InputFlags2 = MOUSEEVENTF_LEFTUP;
	}
	else if (ComboBoxChoice == 1)
	{
		ClickingInfoptr->InputFlags1 = MOUSEEVENTF_RIGHTDOWN;
		ClickingInfoptr->InputFlags2 = MOUSEEVENTF_RIGHTUP;
	}
	else if (ComboBoxChoice == 2)
	{
		ClickingInfoptr->InputFlags1 = MOUSEEVENTF_WHEEL;
		ClickingInfoptr->InputFlags2 = 0;
	}
	UpdateData(FALSE);
}


void CAutoclickerMFCDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton6 = _T("Push button 6 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton6;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
}
