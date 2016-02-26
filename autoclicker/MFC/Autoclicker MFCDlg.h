
// Autoclicker MFCDlg.h : header file
//

#pragma once

#include <sstream>

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
	INT RadioChoice;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton1();
	CString CStr_IDC_EDIT1;
	afx_msg void OnBnClickedButton2();
	CString Hotkeystr;
	CString Stopkeystr;
	CString *Hotkeystrptr;
	CString *Stopkeystrptr;
	CString Clicktimestr;
	CString Durationstr;
	INT ComboBoxChoice;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CString XCoordstr;
	CString YCoordstr;
	afx_msg void OnBnClickedButton6();
	DOUBLE ScreenResX, ScreenResY, XScaleFactor, YScaleFactor;
	std::stringstream ss;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnCbnSelchangeCombo1();
	BOOL Bindstart, Bindstop;
};
