
// Autoclicker MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualKeys.h"
#include "Autoclicker MFC.h"
#include "Autoclicker MFCDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Used for communication between threads and main window
#define HOTKEYMSG 0x8410
#define STOPKEYMSG 0x8411

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
	, RadioChoice(0)
	, CStr_IDC_EDIT1(_T(""))
	, Hotkeystr("")
	, Stopkeystr("")
	, Clicktimestr("")
	, Durationstr("")
	, ComboBoxChoice(0)
	, XCoordstr("")
	, YCoordstr("")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoclickerMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, RadioChoice);
	DDX_Text(pDX, IDC_EDIT1, CStr_IDC_EDIT1);
	DDX_Text(pDX, IDC_EDIT2, Hotkeystr);
	//DDV_MaxChars(pDX, Hotkey, 8);
	DDX_Text(pDX, IDC_EDIT3, Stopkeystr);
	//DDV_MaxChars(pDX, Stopkey, 8);
	DDX_Text(pDX, IDC_EDIT4, Clicktimestr);
	//DDV_MaxChars(pDX, Clicktimestr, 8);
	DDX_Text(pDX, IDC_EDIT5, Durationstr);
	//DDV_MaxChars(pDX, Durationstr, 8);
	DDX_CBIndex(pDX, IDC_COMBO1, ComboBoxChoice);
	DDX_Text(pDX, IDC_EDIT6, XCoordstr);
	DDX_Text(pDX, IDC_EDIT7, YCoordstr);
}

BEGIN_MESSAGE_MAP(CAutoclickerMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	/* DOESNT WORK YET
	ON_MESSAGE(HOTKEYMSG, Hotkeymsg)
	ON_MESSAGE(STOPKEYMSG, Stopkeymsg) */
	ON_BN_CLICKED(IDC_RADIO1, &CAutoclickerMFCDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAutoclickerMFCDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoclickerMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoclickerMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAutoclickerMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAutoclickerMFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAutoclickerMFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAutoclickerMFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAutoclickerMFCDlg::OnBnClickedButton7)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAutoclickerMFCDlg::OnCbnSelchangeCombo1)
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
	ScreenResX = GetSystemMetrics(SM_CXSCREEN);
	ScreenResY = GetSystemMetrics(SM_CYSCREEN);
	XScaleFactor = 65535 / ScreenResX;
	YScaleFactor = 65535 / ScreenResY;
	for (int i = 0; i < 176; ++i)
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
	Clicktimestr = _T("100");
	Durationstr = _T("50");
	XCoordstr = _T("0");
	YCoordstr = _T("0");
	RadioChoice = 0;
	ComboBoxChoice = 0;
	Bindstart = FALSE;
	Bindstop = FALSE;
	Hotkeystrptr = &Hotkeystr;
	Stopkeystrptr = &Stopkeystr;
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
	UINT Hotkey = 0xA2, Stopkey = 0xA0, Clicktime = 100;
	INT Duration = 50;
	DWORD InputFlags1 = MOUSEEVENTF_LEFTDOWN, InputFlags2 = MOUSEEVENTF_LEFTUP;
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
		if (theParam->InputFlags2 != 0)
		{
			Sleep(theParam->Clicktime - theParam->Duration);
		}
		else
		{
			Sleep(theParam->Clicktime);
		}
	}
	static CString msgboxstr1 = _T("Thread 1 has finished");
	AfxMessageBox(msgboxstr1);
	theParam->isRunning = FALSE;
	return 0;
}


static UINT GetKeyBind(LPVOID pParam)
{
	HWND MainWindowHWND = static_cast<HWND>(pParam);
	CString *Hotkeystr = new CString;
	while (true)
	{
		for (int i = 0; i < 176; ++i)
		{
			if (GetAsyncKeyState(VKeyList[i].VKey < 0))
			{
				*Hotkeystr = VKeyList[i].Description;
				static CString msgboxstr2 = _T("Thread 2 has finished");
				AfxMessageBox(msgboxstr2);
				PostMessage(MainWindowHWND, HOTKEYMSG, reinterpret_cast<WPARAM>(Hotkeystr), 0);
				return 0;
			}
		}
		Sleep(100);
	}
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
		CWinThread *pClickThread = AfxBeginThread(StartAutoclick, ClickingInfoptr);
		static CString ThreadStart1 = _T("Thread 1 has started. ");
		CStr_IDC_EDIT1 += ThreadStart1;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	}
	else
	{
		static CString msgboxstr2 = _T("Thread 1 is already running!");
		AfxMessageBox(msgboxstr2);
	}
}


void CAutoclickerMFCDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton2 = _T("Push button 2 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton2;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	if (ClickingInfoptr->isRunning == TRUE)
	{
		static CString ThreadStop1 = _T("Stopping thread 1. ");
		CStr_IDC_EDIT1 += ThreadStop1;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
		ClickingInfoptr->isRunning = FALSE;
	}
	else
	{
		static CString ThreadStopped1 = _T("Thread 1 not running. ");
		CStr_IDC_EDIT1 += ThreadStopped1;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	}
}


void CAutoclickerMFCDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton3 = _T("Push button 3 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton3;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	if (ClickingInfoptr->isRunning == TRUE)
	{
		static CString Thread1active = _T("Thread 1 is running, stop it then try again. ");
		CStr_IDC_EDIT1 += Thread1active;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
		return;
	}
	if (Bindstart == FALSE)
	{
		static CString bindstartmsg = _T("Press any key to bind as Start key, press escape or either bind button to cancel. ");
		CStr_IDC_EDIT1 += bindstartmsg;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
		Bindstart = TRUE;
		CWinThread *pBindThread1 = AfxBeginThread(GetKeyBind, static_cast<LPVOID>(CWnd::GetSafeHwnd()));
	}
	else
	{
		Bindstart = FALSE;
		static CString bindstopmsg = _T("Binding Start key cancelled. ");
		CStr_IDC_EDIT1 += bindstopmsg;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	}
}


void CAutoclickerMFCDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton4 = _T("Push button 4 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton4;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
}


void CAutoclickerMFCDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton5 = _T("Push button 5 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton5;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	UpdateData(TRUE);
	if (_ttoi(Durationstr) >= _ttoi(Clicktimestr) && ComboBoxChoice != 3)
	{
		CStr_IDC_EDIT1 += "Error: Duration is not less than Clicktime, changing Duration to half of Clicktime. ";
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
		Durationstr = std::to_string(_ttoi(Clicktimestr) / 2).c_str();
	}
	ClickingInfoptr->Clicktime = abs(_ttoi(Clicktimestr));
	ClickingInfoptr->Duration = _ttoi(Durationstr);
	for (int i = 0; i < 176; ++i)
	{
		if (Hotkeystr == VKeyList[i].Description)
		{
			ClickingInfoptr->Hotkey = VKeyList[i].VKey;
			break;
		}
		else if (abs(_ttoi(Hotkeystr)) == VKeyList[i].VKey)
		{
			ClickingInfoptr->Hotkey = VKeyList[i].VKey;
			Hotkeystr = VKeyList[i].Description;
			break;
		}
		if (i == 175)
		{
			static CString nomatchmsg1 = _T("Hotkey was not assigned, check key spelling. ");
			CStr_IDC_EDIT1 += nomatchmsg1;
			SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
			break;
		}
	}
	for (int i = 0; i < 176; ++i)
	{
		if (Stopkeystr == VKeyList[i].Description)
		{
			ClickingInfoptr->Stopkey = VKeyList[i].VKey;
			break;
		}
		else if (abs(_ttoi(Stopkeystr)) == VKeyList[i].VKey)
		{
			ClickingInfoptr->Stopkey = VKeyList[i].VKey;
			Stopkeystr = VKeyList[i].Description;
			break;
		}
		if (i == 175)
		{
			static CString nomatchmsg2 = _T("Stopkey was not assigned, check key spelling. ");
			CStr_IDC_EDIT1 += nomatchmsg2;
			SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
			break;
		}
	}
	if (RadioChoice == 0)
	{
		ClickingInfoptr->InputFlags1 = 0;
		ClickingInfoptr->InputFlags2 = 0;
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
		ClickingInfoptr->InputFlags1 = MOUSEEVENTF_MIDDLEDOWN;
		ClickingInfoptr->InputFlags2 = MOUSEEVENTF_MIDDLEUP;
	}
	else if (ComboBoxChoice == 3)
	{
		ClickingInfoptr->InputFlags1 = MOUSEEVENTF_WHEEL;
		ClickingInfoptr->InputFlags2 = 0;
	}
	if (RadioChoice == 1)
	{
		ClickingInfoptr->InputFlags1 += MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK;
		ClickingInfoptr->InputFlags2 += MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK;
		ClickingInfoptr->Input.mi.dx = _ttol(XCoordstr) * XScaleFactor;
		ClickingInfoptr->Input.mi.dy = _ttol(YCoordstr) * YScaleFactor;
	}
	UpdateData(FALSE);
}


void CAutoclickerMFCDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton6 = _T("Push button 6 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton6;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	for (int i = 0; i < 176; ++i)
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
	Clicktimestr = _T("100");
	Durationstr = _T("50");
	XCoordstr = _T("0");
	YCoordstr = _T("0");
	RadioChoice = 0;
	ComboBoxChoice = 0;
	UpdateData(FALSE);
	CAutoclickerMFCDlg::OnBnClickedButton5();
}


void CAutoclickerMFCDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton7 = _T("Push button 7 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton7;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	if (ComboBoxChoice == 3)
	{
		GetDlgItemText(IDC_EDIT5, Durationstr);
		Durationstr = std::to_string(_ttoi(Durationstr) * -1).c_str();
		SetDlgItemText(IDC_EDIT5, Durationstr);
	}
	else
	{
		static CString reverseerror = _T("Mouse button to simulate must be mouse wheel to reverse direction. ");
		CStr_IDC_EDIT1 += reverseerror;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	}
}


void CAutoclickerMFCDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	static CString ComboBoxSel = _T("Combobox selection changed. ");
	CStr_IDC_EDIT1 += ComboBoxSel;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	UpdateData(TRUE);
}

/* DOESNT WORK YET
LRESULT CAutoclickerMFCDlg::Hotkeymsg(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CAutoclickerMFCDlg::Stopkeymsg(WPARAM, LPARAM)
{
	return LRESULT();
} */