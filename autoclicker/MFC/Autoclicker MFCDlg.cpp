
// Autoclicker MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Autoclicker MFC.h"
#include "Autoclicker MFCDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <string>

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
	, Hotkey(_T("162"))
	, Stopkey(_T("160"))
	, Clicktime(_T("100"))
	, Duration(_T("50"))
	, ComboBoxChoice(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoclickerMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, Radio1);
	DDX_Text(pDX, IDC_EDIT1, CStr_IDC_EDIT1);
	DDX_Text(pDX, IDC_EDIT2, Hotkey);
	//DDV_MaxChars(pDX, Hotkey, 8);
	DDX_Text(pDX, IDC_EDIT3, Stopkey);
	//DDV_MaxChars(pDX, Stopkey, 8);
	DDX_Text(pDX, IDC_EDIT4, Clicktime);
	//DDV_MaxChars(pDX, Clicktime, 8);
	DDX_Text(pDX, IDC_EDIT5, Duration);
	//DDV_MaxChars(pDX, Duration, 8);
	DDX_CBIndex(pDX, IDC_COMBO1, ComboBoxChoice);
}

BEGIN_MESSAGE_MAP(CAutoclickerMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CAutoclickerMFCDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAutoclickerMFCDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoclickerMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoclickerMFCDlg::OnBnClickedButton2)
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
	volatile bool isRunning = false;
	int Hotkey = 0xA2;
	int Stopkey = 0xA0;
	int Clicktime = 100;
	int Duration = 50;
	DWORD InputFlags1 = MOUSEEVENTF_LEFTDOWN;
	DWORD InputFlags2 = MOUSEEVENTF_LEFTUP;
} ClickingInfo;

static ClickingInfo *ClickingInfoptr = new ClickingInfo;


static UINT StartAutoclick(LPVOID pParam)
{
	static ClickingInfo *theParam = static_cast<ClickingInfo*> (pParam);
	theParam->isRunning = true;
	ZeroMemory(&(theParam->Input), sizeof(theParam->Input));
	while (theParam->isRunning == true)
	{
		if (GetAsyncKeyState(theParam->Stopkey) < 0)
		{
			break;
		}
		if (GetAsyncKeyState(theParam->Hotkey) < 0)
		{
			theParam->Input.mi.dwFlags = theParam->InputFlags1;
			SendInput(1, &(theParam->Input), sizeof(INPUT));
			Sleep(theParam->Clicktime);
			theParam->Input.mi.dwFlags = theParam->InputFlags2;
			SendInput(1, &(theParam->Input), sizeof(INPUT));
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
}


void CAutoclickerMFCDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgRadio2 = _T("Radio button 2 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgRadio2;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
}


void CAutoclickerMFCDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	static CString clickMsgButton1 = _T("Push button 1 was pressed. ");
	CStr_IDC_EDIT1 += clickMsgButton1;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	UpdateData(FALSE);
	if (ClickingInfoptr->isRunning == false)
	{
		CWinThread *pThread = AfxBeginThread(StartAutoclick, (LPVOID)ClickingInfoptr);
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
	ClickingInfoptr->isRunning = false;
}

