// Autoclicker MFC
// Copyright 2016 Michael Lin
// ClickingThread.cpp : implementation file
//

#include "stdafx.h"
#include "Autoclicker MFCDlg.h"
#include "ClickingThread.h"
#include <string>
#include <cstring>


// CClickingThread

IMPLEMENT_DYNCREATE(CClickingThread, CWinThread)

CClickingThread::CClickingThread()
{
}

CClickingThread::~CClickingThread()
{
}

BOOL CClickingThread::InitInstance()
{
	//Initial values
	isArmed = false;
	timerID = 0;
	SequencePos = 0;
	Payload temppayload;

	INPUT tempinput{ 0 };
	ZeroMemory(&tempinput, sizeof(INPUT));
	tempinput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	temppayload.Input = tempinput;
	temppayload.iskeydown = true;
	temppayload.waittime = 10;

	Sequence.push_back(temppayload);

	tempinput.mi.dwFlags = MOUSEEVENTF_LEFTUP;

	temppayload.Input = tempinput;
	temppayload.iskeydown = false;
	temppayload.waittime = 10;

	Sequence.push_back(temppayload);
	return TRUE;
}

//Thread only exits when app exits
int CClickingThread::ExitInstance()
{
	UnregisterHotKey(NULL, STARTKEY_ID);
	UnregisterHotKey(NULL, STOPKEY_ID);
	return CWinThread::ExitInstance();
}

//Implementation of GetAsyncKeyState but returns a bool instead of a short
bool CClickingThread::GetAsyncKeyStatebool(int virtkey)
{
	if (GetAsyncKeyState(virtkey) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Checks if hotkey is still held down
bool CClickingThread::AllKeysDown()
{
	if (GetAsyncKeyStatebool(StartkeyCombo.vkey) == false)
	{
		return false;
	}
	if ((StartkeyCombo.modifiers & MOD_ALT) == MOD_ALT)
	{
		if (GetAsyncKeyStatebool(VK_MENU) == false)
		{
			return false;
		}
	}
	if ((StartkeyCombo.modifiers & MOD_CONTROL) == MOD_CONTROL)
	{
		if (GetAsyncKeyStatebool(VK_CONTROL) == false)
		{
			return false;
		}
	}
	if ((StartkeyCombo.modifiers & MOD_SHIFT) == MOD_SHIFT)
	{
		if (GetAsyncKeyStatebool(VK_SHIFT) == false)
		{
			return false;
		}
	}
	return true;
}

//Add/replace hotkey to start/stop clicking
void CClickingThread::AddHotkey(DWORD dWord, bool isStartkey)
{
	BYTE tempbyte = HIBYTE(LOWORD(dWord));
	TwoBytes temp2bytes;
	temp2bytes.vkey = LOBYTE(LOWORD(dWord));
	temp2bytes.modifiers = 0;
	if ((tempbyte & HOTKEYF_SHIFT) == HOTKEYF_SHIFT)
	{
		temp2bytes.modifiers |= MOD_SHIFT;
	}
	if ((tempbyte & HOTKEYF_CONTROL) == HOTKEYF_CONTROL)
	{
		temp2bytes.modifiers |= MOD_CONTROL;
	}
	if ((tempbyte & HOTKEYF_ALT) == HOTKEYF_ALT)
	{
		temp2bytes.modifiers |= MOD_ALT;
	}
	if (isStartkey == true)
	{
		StartkeyCombo = temp2bytes;
	}
	else if (isStartkey == false)
	{
		StopkeyCombo = temp2bytes;
	}
}


BEGIN_MESSAGE_MAP(CClickingThread, CWinThread)
	ON_THREAD_MESSAGE(WM_HOTKEY, OnHotkey)
	ON_THREAD_MESSAGE(WM_TIMER, OnTimer)
	ON_THREAD_MESSAGE(UWM_NEWHOTKEY, OnNewHotkey)
	ON_THREAD_MESSAGE(UWM_NEWSTOPKEY, OnNewStopkey)
	ON_THREAD_MESSAGE(UWM_ARM, OnArm)
	ON_THREAD_MESSAGE(UWM_ADDAUTOKEY, OnNewAutokey)
	ON_THREAD_MESSAGE(UWM_DELAUTOKEY, OnRemAutokey)
END_MESSAGE_MAP()


// CClickingThread message handlers
void CClickingThread::OnHotkey(WPARAM wParam, LPARAM lParam)
//When user presses the hotkey
{
	switch (wParam)
	{
		case STARTKEY_ID:
			if (isArmed == true)
			{
				if (SequencePos == Sequence.size())
				{
					SequencePos = 0;
				}
				SendInput(1, &Sequence[SequencePos].Input, sizeof(INPUT));
				::KillTimer(NULL, timerID);
				timerID = ::SetTimer(NULL, 0, Sequence[SequencePos].waittime, NULL);
				++SequencePos;
			}
			break;
		case STOPKEY_ID:
			isArmed = false;
			break;
	}
}

void CClickingThread::OnTimer(WPARAM wParam, LPARAM lParam)
//When the timer set in OnHotkey or this timer expires
{
	if (wParam == timerID && AllKeysDown() == true && isArmed == true)
	{
		if (SequencePos == Sequence.size())
		{
			SequencePos = 0;
		}
		SendInput(1, &Sequence[SequencePos].Input, sizeof(INPUT));
		::KillTimer(NULL, timerID);
		timerID = ::SetTimer(NULL, 0, Sequence[SequencePos].waittime, NULL);
		++SequencePos;

	}
	else
	{
		::KillTimer(NULL, timerID);
		if (SequencePos == Sequence.size())
		{
			SequencePos = 0;
		}
		//Update main window on change
		PostMessage(mainwindowhwnd, UWM_CURRENTNODE, static_cast<WPARAM>(SequencePos), NULL);
	}
}

void CClickingThread::OnNewHotkey(WPARAM wParam, LPARAM lParam)
{
	UnregisterHotKey(NULL, STARTKEY_ID);
	SecureZeroMemory(&StartkeyCombo, sizeof(TwoBytes));
	AddHotkey(wParam, true);
	if (RegisterHotKey(NULL, STARTKEY_ID, StartkeyCombo.modifiers | MOD_NOREPEAT, StartkeyCombo.vkey) == 0)
	{
		AfxMessageBox(_T("Key combo already in use, choose another."));
	}
}

void CClickingThread::OnNewStopkey(WPARAM wParam, LPARAM lParam)
{
	UnregisterHotKey(NULL, STOPKEY_ID);
	SecureZeroMemory(&StopkeyCombo, sizeof(TwoBytes));
	AddHotkey(wParam, false);
	if (RegisterHotKey(NULL, STOPKEY_ID, StopkeyCombo.modifiers | MOD_NOREPEAT, StopkeyCombo.vkey) == 0)
	{
		AfxMessageBox(_T("Key combo already in use, choose another."));
	}
}

void CClickingThread::OnArm(WPARAM wParam, LPARAM lParam)
//When user presses Start or Stop Autoclicking button
{
	bool param = static_cast<bool>(wParam);
	if (isArmed == false && param == false)
	{
		AfxMessageBox(_T("Already UnArmed"));
	}
	else if (isArmed == true && param == true)
	{
		AfxMessageBox(_T("Already Armed"));
	}
	isArmed = param;
}

void CClickingThread::OnNewAutokey(WPARAM wParam, LPARAM lParam)
//When user adds new key to sequence
{
	INPUT* input = reinterpret_cast<INPUT*>(wParam);
	TwoInts* waitandpos = reinterpret_cast<TwoInts*>(lParam);
	Payload temppayload;
	SecureZeroMemory(&temppayload.Input, sizeof(INPUT));
	temppayload.Input = *input;
	temppayload.waittime = waitandpos->waittime;
	if (waitandpos->position >= Sequence.size())
	{
		Sequence.push_back(temppayload);
	}
	else
	{
		Sequence.insert(Sequence.begin() + waitandpos->position, temppayload);
	}
	if (SequencePos >= waitandpos->position)
	{
		++SequencePos;
	}
	SecureZeroMemory(input, sizeof(INPUT));
}

void CClickingThread::OnRemAutokey(WPARAM wParam, LPARAM lParam)
//When user removes key from sequence
{
	bool removeall = static_cast<bool>(lParam);
	int pos = static_cast<int>(wParam);
	if (removeall == false)
	{
		Sequence.erase(Sequence.begin() + pos);
		if (SequencePos > pos)
		{
			--SequencePos;
		}
	}
	else if (removeall == true)
	{
		Sequence.empty();
		SequencePos = 0;
	}
}
