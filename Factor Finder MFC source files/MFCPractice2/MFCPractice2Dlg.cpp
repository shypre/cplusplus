
// MFCPractice2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCPractice2.h"
#include "MFCPractice2Dlg.h"
#include "afxdialogex.h"
#include <cmath>
#include <string>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#undef UNICODE

using namespace std;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCPractice2Dlg dialog



CMFCPractice2Dlg::CMFCPractice2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCPractice2Dlg::IDD, pParent)
	, stroutput(_T(""))
	, intinput(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCPractice2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, stroutput);
	DDX_Text(pDX, IDC_EDIT1, intinput);
}

BEGIN_MESSAGE_MAP(CMFCPractice2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &CMFCPractice2Dlg::OnClickedButton1)
//ON_EN_CHANGE(IDC_EDIT1, &CMFCPractice2Dlg::OnChangeEdit1)
ON_BN_CLICKED(IDC_BUTTON1, &CMFCPractice2Dlg::OnClickedButton1)
END_MESSAGE_MAP()


// CMFCPractice2Dlg message handlers

BOOL CMFCPractice2Dlg::OnInitDialog()
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

void CMFCPractice2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCPractice2Dlg::OnPaint()
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
HCURSOR CMFCPractice2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCPractice2Dlg::OnClickedButton1()
{
	// TODO: Add your control notification handler code here
	string error2 = "Indalid input, try again.";
	CString error(error2.c_str());
	GetDlgItemText(IDC_EDIT1, strintinput);
	if (!(_wtoi64(strintinput)))
	{
		SetDlgItemText(IDC_EDIT2, error);
		return;
	}
	intinput = _wtoi64(strintinput);
	sqn = sqrt(intinput);
	x = 1;
	while (x <= sqn)
	{
		if (intinput % x == 0)
		{
			strintinput.Format(L"%I64u", intinput/x);
			stroutput = strintinput;
			stroutputcompl += stroutput += ", ";
			strintinput.Format(L"%I64u", x);
			stroutput = strintinput;
			stroutputcompl += stroutput += " | ";
		}
		x++;
	}
	stroutput = stroutputcompl;
	SetDlgItemText(IDC_EDIT2, stroutput);
	strintinput.Empty();
	stroutput.Empty();
	stroutputcompl.Empty();
}
