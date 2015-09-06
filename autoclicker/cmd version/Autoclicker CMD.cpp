//Autoclicker (cmd version). Copyright 2015 by Michael Lin.

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
	string Repeat = "y";
	while (Repeat == "y")
	{
		double ScreenResX = GetSystemMetrics(SM_CXSCREEN),							//Gets screen resolution of main monitor
			ScreenResY = GetSystemMetrics(SM_CYSCREEN);
		double XScaleFactor = 65535 / (ScreenResX - 1);								//The scale factor between SendInput's 65535 mapping and screen resolution. Go on MSDN for more info
		double YScaleFactor = 65535 / (ScreenResY - 1);								//The subtract 1 is because C++ always rounds toward 0
		unsigned short Choice;
		cout << "To have the mouse autoclick at a certain point, enter 0.\n"
			<< "To have the mouse autoclick at a specific pixel, enter 1.\n"
			<< "To have the mouse autoclick wherever the cursor is, enter 2.\n";
		cin >> Choice;
		while (cin.fail() || Choice > 2)											//In case the user is stupid and/or can't read
		{
			cin.clear();															//Proper way to handle cin.fail() is to 1. clear cin.fail flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');					//and 2. reset the buffer
			cout << "Invalid input, please try again.\n";
			cin >> Choice;
		}
		stringstream ss;															//Declare it right now because we can reuse this over and over
		INPUT Input = { 0 };															//INPUT structure used by SendInput. 0 is mouse input
		ZeroMemory(&Input, sizeof(Input));											//Apparently this helps avoid blackscreens with SendInput. Fills Input struct with 0s in memory
		if (Choice == 0)															//If user wants to autoclick at a certain spot
		{
			Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE |			//DWORD flags
				MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
			POINT CursorPos;														//POINT structure to store mouse location
			string PosKeyStr = "0xA0";												//Example key (Left Shift). Full list on MSDN
			int PosKey;																//The virtual keycodes on MSDN is in hex but the actual keycodes used by C++ functions is in decimal
			ss << hex << PosKeyStr;													//The good part about stringstreams, it can receive hex input and output it as decimal
			ss >> PosKey;
			stringstream().swap(ss);												//Reset the stringstream to a brand new one
			unsigned long long Delay, Countdown, UserClicks, MouseClicks = 0;
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
			Input.mi.dx = round(CursorPos.x * XScaleFactor);						//Explicitly saying to round because C++ always rounds towards zero by default
			Input.mi.dy = round(CursorPos.y * YScaleFactor);
			cout << "Countdown has started!\n";
			Sleep(Countdown);
			cout << "Clicking has started\n";
			while (MouseClicks < UserClicks)
			{
				SendInput(1, &Input, sizeof(INPUT));
				Sleep(Delay);
				MouseClicks++;
			}
			cout << MouseClicks << " Done!\n";
		}
		else if (Choice == 1)														//If user wants to autoclick at a specific pixel
		{
			Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE |			//DWORD flags
				MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
			unsigned long long Delay, Countdown, UserClicks, MouseClicks = 0, CursorPosX, CursorPosY;
			cout << "Set X pixel position of cursor (left is 0 and right is max)\nHorizontal cursor position: ";
			cin >> CursorPosX;
			cout << "Set Y pixel position of cursor (up is 0 and down is max)\nVertical cursor position: ";
			cin >> CursorPosY;
			cout << "Set number of clicks.\n";
			cin >> UserClicks;
			cout << "Set time between each click (in milliseconds).\n";
			cin >> Delay;
			cout << "Set countdown (in milliseconds).\n";
			cin >> Countdown;
			Input.mi.dx = round(CursorPosX * XScaleFactor);						//Explicitly saying to round because C++ always rounds towards zero by default
			Input.mi.dy = round(CursorPosY * YScaleFactor);
			cout << "Countdown has started!\n";
			Sleep(Countdown);
			cout << "Clicking has started\n";
			while (MouseClicks < UserClicks)
			{
				SendInput(1, &Input, sizeof(INPUT));
				Sleep(Delay);
				MouseClicks++;
			}
			cout << "Done!\n";
		}
		else if (Choice == 2)														//If user wants to autoclick wherever their cursor is
		{
			Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;			//DWORD flags
			string HotkeyStr = "0xA2";												//Example key (Left Control)
			int Hotkey;
			ss << hex << HotkeyStr;
			ss >> Hotkey;
			stringstream().swap(ss);
			unsigned long long Delay;
			cout << "Set time between each click (in milliseconds).\n";
			cin >> Delay;
			cout << "Press " << HotkeyStr << " to start clicking\n";
			while (true)															//While user holds down key, it will click
			{
				while (GetAsyncKeyState(Hotkey) < 0)
				{
					SendInput(1, &Input, sizeof(INPUT));
					Sleep(Delay);
				}
			}
		}
		cout << "Repeat?\ny/n: ";
		cin >> Repeat;
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