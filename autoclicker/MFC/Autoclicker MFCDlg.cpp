// Autoclicker MFC
// Copyright 2016 Michael Lin
// Autoclicker MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualKeys.h"
#include "ClickingThread.h"
#include "Autoclicker MFC.h"
#include "Autoclicker MFCDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoclickerMFCDlg dialog



CAutoclickerMFCDlg::CAutoclickerMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTOCLICKERMFC_DIALOG, pParent)
	, CStr_IDC_EDIT1(_T(""))
	, DelayValue(_T(""))
	, RadioButtonSelUp(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//Dynamic data exchange and validation
void CAutoclickerMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, CStr_IDC_EDIT1);
	DDX_Control(pDX, IDC_HOTKEY2, StartkeyControl);
	DDX_Control(pDX, IDC_HOTKEY3, StopkeyControl);
	DDX_Control(pDX, IDC_LIST3, SequenceListBox);
	DDX_Control(pDX, IDC_COMBO1, ComboBoxCtrl);
	DDX_Control(pDX, IDC_HOTKEY1, AutokeyCtrl);
	DDX_Text(pDX, IDC_EDIT3, DelayValue);
	DDV_MaxChars(pDX, DelayValue, 7);
	DDX_Radio(pDX, IDC_RADIO1, RadioButtonSelUp);
}

BEGIN_MESSAGE_MAP(CAutoclickerMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoclickerMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoclickerMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAutoclickerMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAutoclickerMFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAutoclickerMFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_RADIO1, &CAutoclickerMFCDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAutoclickerMFCDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON6, &CAutoclickerMFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAutoclickerMFCDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CAutoclickerMFCDlg::OnBnClickedButton8)
	ON_MESSAGE(UWM_CURRENTNODE, ChangeSelection)
END_MESSAGE_MAP()


// CAutoclickerMFCDlg message handlers

BOOL CAutoclickerMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//Initial values
	ComboBoxCtrl.SetCurSel(0);

	SequenceListBox.SetExtendedStyle(SequenceListBox.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	LVCOLUMN lvColumn;

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 0;
	lvColumn.pszText = _T("");
	SequenceListBox.InsertColumn(0, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 30;
	lvColumn.pszText = _T("");
	SequenceListBox.InsertColumn(1, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 40;
	lvColumn.pszText = _T("Key");
	SequenceListBox.InsertColumn(2, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 40;
	lvColumn.pszText = _T("Wait");
	SequenceListBox.InsertColumn(3, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 60;
	lvColumn.pszText = _T("Down/Up");
	SequenceListBox.InsertColumn(4, &lvColumn);

	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 0;
	lvItem.iSubItem = 0;
	lvItem.pszText = _T("");
	SequenceListBox.InsertItem(&lvItem);
	SequenceListBox.SetItemText(0, 1, _T(">"));
	SequenceListBox.SetItemText(0, 2, _T("LMB"));
	SequenceListBox.SetItemText(0, 3, _T("10"));
	SequenceListBox.SetItemText(0, 4, _T("Down"));

	lvItem.iItem = 1;
	lvItem.pszText = _T("");
	SequenceListBox.InsertItem(&lvItem);
	SequenceListBox.SetItemText(1, 1, _T("2"));
	SequenceListBox.SetItemText(1, 2, _T("LMB"));
	SequenceListBox.SetItemText(1, 3, _T("10"));
	SequenceListBox.SetItemText(1, 4, _T("Up"));

	lastposition = 0;

	UpdateData(FALSE);
	//Start the thread
	pClickThread = (CClickingThread*)AfxBeginThread(RUNTIME_CLASS(CClickingThread), THREAD_PRIORITY_BELOW_NORMAL, 0, CREATE_SUSPENDED);
	//Pass the handle to the main window
	pClickThread->mainwindowhwnd = m_hWnd;
	pClickThread->ResumeThread();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAutoclickerMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
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


void CAutoclickerMFCDlg::OnBnClickedButton1()
//Start Autoclicking button
{
	UpdateData(FALSE);
	if (SequenceListBox.GetItemCount() == 0)
	{
		AfxMessageBox(_T("Can't start autoclicking if there are no entries in the sequence. "));
		return;
	}
	else
	{
		pClickThread->PostThreadMessage(UWM_ARM, true, NULL);
		static CString armedmsg = _T("Armed. ");
		CStr_IDC_EDIT1 += armedmsg;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
	}
}


void CAutoclickerMFCDlg::OnBnClickedButton2()
//Stop Autoclicking button
{
	pClickThread->PostThreadMessage(UWM_ARM, false, NULL);
	static CString unarmedmsg = _T("UnArmed. ");
	CStr_IDC_EDIT1 += unarmedmsg;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
}

void CAutoclickerMFCDlg::OnBnClickedButton3()
//Set Start key button
{
	UpdateData(TRUE);
	PostThreadMessage(pClickThread->m_nThreadID, UWM_NEWHOTKEY, StartkeyControl.GetHotKey(), NULL);
	static CString hotkeymsg = _T("Hotkey set. ");
	CStr_IDC_EDIT1 += hotkeymsg;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
}

void CAutoclickerMFCDlg::OnBnClickedButton4()
//Set Stop key button
{
	UpdateData(TRUE);
	PostThreadMessage(pClickThread->m_nThreadID, UWM_NEWSTOPKEY, StopkeyControl.GetHotKey(), NULL);
	static CString stopkeymsg = _T("Stopkey set. ");
	CStr_IDC_EDIT1 += stopkeymsg;
	SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
}


void CAutoclickerMFCDlg::OnBnClickedButton5()
//Insert before selection button
//Lots of counting required here since CListCtrl doesn't have an easy way to do this
{
	UpdateData(TRUE);

	if (((ComboBoxCtrl.GetCurSel() == 0) && (AutokeyCtrl.GetHotKey()) == 0) || (ComboBoxCtrl.GetCurSel() != 0) && (AutokeyCtrl.GetHotKey() != 0))
	{
		static CString doublesel = _T("Can't have autokey in both or no fields. Change only one field to none. ");
		CStr_IDC_EDIT1 += doublesel;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
		return;
	}
	else if ((HIBYTE(LOWORD(AutokeyCtrl.GetHotKey())) & HOTKEYF_CONTROL) == HOTKEYF_CONTROL || (HIBYTE(LOWORD(AutokeyCtrl.GetHotKey())) & HOTKEYF_SHIFT) == HOTKEYF_SHIFT || (HIBYTE(LOWORD(AutokeyCtrl.GetHotKey())) & HOTKEYF_ALT) == HOTKEYF_ALT)
	{
		static CString nomodkeys = _T("Can't have more than one autokey for each item. For keys like mouse buttons and command keys use the drop down menu. ");
		CStr_IDC_EDIT1 += nomodkeys;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
		return;
	}
	static TwoInts waitandpos;
	waitandpos.position = SequenceListBox.GetSelectionMark();
	if (waitandpos.position == -1)
	{
		waitandpos.position = pClickThread->Sequence.size();
	}
	if (insertbefore != 1)
	{
		insertbefore = 2;
	}
	waitandpos.waittime = _ttoi(DelayValue);
	CString keyname = _T("");
	static INPUT input{ 0 };
	SecureZeroMemory(&input, sizeof(INPUT));
	if (ComboBoxCtrl.GetCurSel() != 0)
	{
		int choice = ComboBoxCtrl.GetCurSel();
		switch (choice)
		{
			case 1:
				input.type = INPUT_MOUSE;
				if (RadioButtonSelUp == FALSE)
				{
					input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				}
				else if (RadioButtonSelUp == TRUE)
				{
					input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
				}
				keyname = _T("LMB");
				break;
			case 2:
				input.type = INPUT_MOUSE;
				if (RadioButtonSelUp == FALSE)
				{
					input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
				}
				else if (RadioButtonSelUp == TRUE)
				{
					input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
				}
				keyname = _T("RMB");
				break;
			case 3:
				input.type = INPUT_MOUSE;
				if (RadioButtonSelUp == FALSE)
				{
					input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
				}
				else if (RadioButtonSelUp == TRUE)
				{
					input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
				}
				keyname = _T("MMB");
				break;
			case 4:
				input.type = INPUT_MOUSE;
				input.mi.dwFlags = MOUSEEVENTF_WHEEL;
				if (RadioButtonSelUp == FALSE)
				{
					input.mi.mouseData = WHEEL_DELTA * -1;
				}
				else if (RadioButtonSelUp == TRUE)
				{
					input.mi.mouseData = WHEEL_DELTA;
				}
				keyname = _T("MW");
				break;
			case 5:
				input.type = INPUT_KEYBOARD;
				input.ki.wVk = 0xA2;
				if (RadioButtonSelUp == TRUE)
				{
					input.ki.dwFlags = KEYEVENTF_KEYUP;
				}
				keyname = _T("LCtrl");
				break;
			case 6:
				input.type = INPUT_KEYBOARD;
				input.ki.wVk = 0xA4;
				if (RadioButtonSelUp == TRUE)
				{
					input.ki.dwFlags = KEYEVENTF_KEYUP;
				}
				keyname = _T("LAlt");
				break;
			case 7:
				input.type = INPUT_KEYBOARD;
				input.ki.wVk = 0xA0;
				if (RadioButtonSelUp == TRUE)
				{
					input.ki.dwFlags = KEYEVENTF_KEYUP;
				}
				keyname = _T("LShift");
				break;
			case 8:
				input.type = INPUT_KEYBOARD;
				input.ki.wVk = 0x20;
				if (RadioButtonSelUp == TRUE)
				{
					input.ki.dwFlags = KEYEVENTF_KEYUP;
				}
				keyname = _T("Space");
				break;
			default:
				AfxMessageBox(_T("Error\nNo matching value found for combobox choice\nKey not added"), MB_ICONSTOP | MB_OK);
				return;
		}
		
	}
	else if (AutokeyCtrl.GetHotKey() != 0)
	{
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = LOBYTE(LOWORD(AutokeyCtrl.GetHotKey()));
		if (RadioButtonSelUp == TRUE)
		{
			input.ki.dwFlags = KEYEVENTF_KEYUP;
		}
		keyname = AutokeyCtrl.GetHotKeyName();
	}
	
	static INPUT* inputptr = &input;
	static TwoInts* waitandposptr = &waitandpos;

	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = waitandpos.position;
	lvItem.iSubItem = 0;
	lvItem.pszText = _T("");
	CString numcstr(std::to_string(waitandpos.position + 1).c_str());
	SequenceListBox.InsertItem(&lvItem);
	SequenceListBox.SetItemText(waitandpos.position, 1, numcstr);
	SequenceListBox.SetItemText(waitandpos.position, 2, keyname);
	SequenceListBox.SetItemText(waitandpos.position, 3, DelayValue);

	for (int i = waitandpos.position; i < SequenceListBox.GetItemCount(); ++i)
	{
		if (SequenceListBox.GetItemText(i + 1, 1) != _T(">"))
		{
			CString numcstr2(std::to_string(i + 2).c_str());
			SequenceListBox.SetItemText(i + 1, 1, numcstr2);
		}
	}

	if (RadioButtonSelUp == FALSE)
	{
		SequenceListBox.SetItemText(waitandpos.position, 4, _T("Down"));
	}
	else if (RadioButtonSelUp == TRUE)
	{
		SequenceListBox.SetItemText(waitandpos.position, 4, _T("Up"));
	}
	if (waitandpos.position >= lastposition)
	{
		++lastposition;
	}
	PostThreadMessage(pClickThread->m_nThreadID, UWM_ADDAUTOKEY, reinterpret_cast<WPARAM>(inputptr), reinterpret_cast<LPARAM>(waitandposptr));
	insertbefore = 0;
}


void CAutoclickerMFCDlg::OnBnClickedButton6()
//Insert at end button
{
	insertbefore = 1;
	CAutoclickerMFCDlg::OnBnClickedButton5();
}


void CAutoclickerMFCDlg::OnBnClickedButton7()
//Remove selected button
{
	if (SequenceListBox.GetSelectionMark() == -1)
	{
		return;
	}
	else if (SequenceListBox.GetItemText(SequenceListBox.GetSelectionMark(), 1) == _T(">"))
	{
		CString noremcurrent = _T("Can't remove item that is next to be executed. ");
		CStr_IDC_EDIT1 += noremcurrent;
		SetDlgItemText(IDC_EDIT1, CStr_IDC_EDIT1);
		return;
	}
	else
	{
		int pos = SequenceListBox.GetSelectionMark();
		SequenceListBox.DeleteItem(pos);
		for (int i = pos; i < SequenceListBox.GetItemCount(); ++i)
		{
			if (SequenceListBox.GetItemText(i, 1) != _T(">"))
			{
				CString numcstr2(std::to_string(i + 1).c_str());
				SequenceListBox.SetItemText(i, 1, numcstr2);
			}
		}
		PostThreadMessage(pClickThread->m_nThreadID, UWM_DELAUTOKEY, pos, false);
	}
}


void CAutoclickerMFCDlg::OnBnClickedButton8()
//Clear all button
{
	if (AfxMessageBox(_T("Are you sure you want to remove all entries? "), MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDYES)
	{
		SequenceListBox.DeleteAllItems();
		PostThreadMessage(pClickThread->m_nThreadID, UWM_DELAUTOKEY, 0, true);
		CAutoclickerMFCDlg::OnBnClickedButton2();
	}
	else
	{
		return;
	}
}


void CAutoclickerMFCDlg::OnBnClickedRadio1()
//Down radio button
{
	UpdateData(TRUE);
}


void CAutoclickerMFCDlg::OnBnClickedRadio2()
//Up radio button
{
	UpdateData(TRUE);
}

//Thread message when the next item to be executed changes
LRESULT CAutoclickerMFCDlg::ChangeSelection(WPARAM wParam, LPARAM lParam)
{
	int pos = static_cast<int>(wParam);
	CString tempnum(std::to_string(lastposition+1).c_str());
	SequenceListBox.SetItemText(lastposition, 1, tempnum);
	SequenceListBox.SetItemText(pos, 1, _T(">"));
	lastposition = pos;
	return LRESULT();
}