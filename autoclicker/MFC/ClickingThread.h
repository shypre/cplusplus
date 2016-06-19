// Autoclicker MFC
// Copyright 2016 Michael Lin

#pragma once

#include <vector>

//Custom messages and IDs
#define STARTKEY_ID 5
#define STOPKEY_ID 6
#define UWM_NEWHOTKEY WM_USER+120
#define UWM_NEWSTOPKEY WM_USER+121
#define UWM_ARM WM_USER+100
#define UWM_ADDAUTOKEY WM_USER+300
#define UWM_DELAUTOKEY WM_USER+301
#define UWM_CURRENTNODE WM_USER+400
// CClickingThread

typedef struct PayloadStruct
{
	bool iskeydown;
	INPUT Input;
	long waittime;
} Payload;

typedef struct TwoBytesStruct
{
	BYTE vkey, modifiers;
} TwoBytes;

class CClickingThread : public CWinThread
{
	DECLARE_DYNCREATE(CClickingThread)

protected:
	CClickingThread();           // protected constructor used by dynamic creation
	virtual ~CClickingThread();

public:
	afx_msg void OnHotkey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNewHotkey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNewStopkey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnArm(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNewAutokey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRemAutokey(WPARAM wParam, LPARAM lParam);
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual bool AllKeysDown();
	virtual void AddHotkey(DWORD dWord, bool isStartkey);
	volatile bool isArmed;
	bool GetAsyncKeyStatebool(int virtkey);
	TwoBytes StartkeyCombo;
	TwoBytes StopkeyCombo;
	std::vector<Payload> Sequence;
	UINT_PTR timerID;
	HWND mainwindowhwnd;
	int SequencePos;

protected:
	DECLARE_MESSAGE_MAP()
};
