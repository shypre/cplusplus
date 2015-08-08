//Autoclicker (cmd version). Copyright 2015 by Michael Lin.
//This is also my first time including comments in my code

#include "stdafx.h"
#define NOMINMAX																//max() is already defined in Windows.h, but it is a different function than what is in <limits>
#include "Windows.h"															//This #define is built into Windows.h so you can undefine min() and max() from that header
#include <iostream>
#include <sstream>																//Better way than stoi() or etc. to convert from string to number is stringstreams
#include <limits>																//Where the max() we want is from

using namespace std;

int main()
{
	cout << "Autoclicker (cmd version). Copyright 2015 by Michael Lin\n";
	cout.precision(16);															//Sets all floating points that are outputted to have 16 decimal places
	short Choice;
	cout << "To have the mouse autoclick at a certain point, enter 1.\n"
		 << "To have the mouse autoclick wherever the cursor is, enter 2.\n";
	cin >> Choice;
	while (cin.fail() || Choice != 1 || Choice != 2)							//In case the user is stupid and/or can't read
	{
		cin.clear();															//Proper way to handle cin.fail() is to 1. clear cin.fail flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n');					//and 2. reset the buffer
		cout << "Invalid input, please try again.\n";
		cin >> Choice;
	}
	stringstream ss;															//Declare it right now because we can reuse this over and over
	INPUT Input;																//INPUT structure used by SendInput
	Input.type = INPUT_MOUSE;													//We want mouse input
	if (Choice == 1)
	{
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;			//DWORD flags
		POINT CursorPos;														//POINT structure to store mouse location
		string PosKeyStr = "0xA0";												//Example key. Full list on MSDN
		int PosKey;																//The virtual keycodes on MSDN is in hex but the actualy keycodes used by C++ functions is in decimal
		ss << hex << PosKeyStr;													//The good part about stringstreams, it can receive hex input and output it as decimal
		ss >> PosKey;
		stringstream().swap(ss);												//Reset the stringstream to a brand new one
		unsigned int Delay, Countdown, UserClicks, MouseClicks = 0;
		cout << "Set number of clicks.\n";
		cin >> UserClicks;
		cout << "Set time between each click (in milliseconds).\n";
		cin >> Delay;
		cout << "Set countdown (in milliseconds).\n";
		cin >> Countdown;
		cout << "Press Left Shift to get the position of the cursor.\n";
		cout << GetAsyncKeyState(PosKey) << endl;
		while (true)															//Checks whether key is down or not with a loop. Takes decimal and not hex as parameter (as stated above)
		{
			if (GetAsyncKeyState(PosKey) < 0)
			{
				GetCursorPos(&CursorPos);
				cout << GetAsyncKeyState(PosKey) << ",  success\n";
				break;
			}
		}
		cout << "Countdown has started!\n";
		Sleep(Countdown);
		while (MouseClicks < UserClicks)
		{
			SetCursorPos(CursorPos.x, CursorPos.y);
			SendInput(1, &Input, sizeof(INPUT));
			Sleep(Delay);
			MouseClicks++;
		}
		cout << MouseClicks << " Done!\n";
	}
	else if (Choice == 2)
	{
		Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE |			//DWORD flags
			MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
		double ScreenResX = GetSystemMetrics(SM_CXSCREEN),						//Gets screen resolution of main monitor
			ScreenResY = GetSystemMetrics(SM_CYSCREEN);
		const double XScaleFactor = 65535 / (ScreenResX - 1);					//The scale factor between SendInput's 65535 mapping and screen resolution. Go on MSDN for more info
		const double YScaleFactor = 65535 / (ScreenResY - 1);					//The subtract 1 is because C++ always rounds toward 0
		string HotkeyStr = "0xA2";												//Example key
		int Hotkey;
		ss << hex << HotkeyStr;													//The ever-useful stringstream again
		ss >> Hotkey;															//No, ss does not stand for Schutzstaffel
		stringstream().swap(ss);
		while (true)															//While user hold down the key, it will click
		{
			while (GetAsyncKeyState(Hotkey) < 0)
			{
				SendInput(1, &Input, sizeof(INPUT));
				Sleep(100);
			}
		}
	}
	cin.get();
    return 0;
}

//A bunch of scrap code that I might use eventually.

/* double ScreenResX = GetSystemMetrics(SM_CXSCREEN), ScreenResY = GetSystemMetrics(SM_CYSCREEN);
const double XScaleFactor = 65535 / (ScreenResX - 1);
const double YScaleFactor = 65535 / (ScreenResY - 1);
cout << XScaleFactor << endl << YScaleFactor << endl;
POINT CursorPos;
GetCursorPos(&CursorPos);
cout << CursorPos.x << endl << CursorPos.y << endl;
Input.mi.dx = CursorPos.x;
Input.mi.dy = CursorPos.y;
Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
SendInput(1, &Input, sizeof(INPUT));
Sleep(1000);
POINT CursorPos2;
GetCursorPos(&CursorPos2);
cout << CursorPos2.x << endl << CursorPos2.y << endl;
double nx = (CursorPos.x * XScaleFactor);
double ny = (CursorPos.y * YScaleFactor);
Input.mi.dx = (LONG)(nx);
Input.mi.dy = (LONG)(ny);
Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
SendInput(1, &Input, sizeof(INPUT));
POINT CursorPos3;
GetCursorPos(&CursorPos3);
cout << CursorPos3.x << endl << CursorPos3.y << endl; */