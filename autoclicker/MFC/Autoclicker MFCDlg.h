// Autoclicker MFC
// Copyright 2016 Michael Lin
// Autoclicker MFCDlg.h : header file
//

#pragma once

#include "ClickingThread.h"
#include <sstream>
#include <vector>
#include "afxcmn.h"
#include "afxwin.h"

typedef struct TwoIntsStruct
{
	int waittime, position;
}TwoInts;

// CAutoclickerMFCDlg dialog
class CAutoclickerMFCDlg : public CDialogEx
{
// Construction
public:
	CAutoclickerMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOCLICKERMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString CStr_IDC_EDIT1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg LRESULT ChangeSelection(WPARAM wParam, LPARAM lParam);
	CClickingThread* pClickThread;
	CListCtrl SequenceListBox;
	CHotKeyCtrl StartkeyControl, StopkeyControl, AutokeyCtrl;
	CComboBox ComboBoxCtrl;
	CString DelayValue;
	BOOL RadioButtonSelUp;
	int insertbefore, lastposition;
};
