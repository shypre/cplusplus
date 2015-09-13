//Autoclicker (cmd version). Copyright 2015 by Michael Lin.

#include "stdafx.h"
#define NOMINMAX																	//max() is already defined in Windows.h, but it is a different function than what is in <limits>
#include "Windows.h"																//This #define is built into Windows.h so you can undefine min() and max() from that header
#include <iostream>
#include <sstream>																	//Better way than stoi() or etc. to convert from string to number is stringstreams
#include <limits>																	//Where the max() we want is from
#include <string>

using namespace std;

int main()
{
	cout << "Autoclicker (cmd version). Copyright 2015 by Michael Lin\n";
	cout.precision(16);																//Sets all floating points that are outputted to have 16 decimal places
	char Repeat = 'y';
	while (Repeat == 'y')
	{
		double ScreenResX = GetSystemMetrics(SM_CXSCREEN),							//Gets screen resolution of main monitor
			ScreenResY = GetSystemMetrics(SM_CYSCREEN);
		double XScaleFactor = 65535 / ScreenResX,									//The scale factor between SendInput's 65535 mapping and screen resolution. Go on MSDN for more info
			YScaleFactor = 65535 / ScreenResY;
		unsigned long long Choice;
		cout << "To have the mouse autoclick at a certain point, enter 0\n"
			<< "To have the mouse autoclick at a specific pixel, enter 1\n"
			<< "To have the mouse autoclick wherever the cursor is, enter 2\n";
		cin >> Choice;
		while (cin.fail() || Choice > 2)											//In case the user is stupid and/or can't read
		{
			cin.clear();															//Proper way to handle cin.fail() is to 1. clear cin.fail flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');					//and 2. reset the buffer
			cout << "Invalid input, please try again\n";
			cin >> Choice;
		}
		stringstream ss;															//Declare it right now because we can reuse this over and over
		INPUT Input = { 0 };														//INPUT structure used by SendInput. 0 is mouse input
		ZeroMemory(&Input, sizeof(Input));											//Apparently this helps avoid blackscreens with SendInput. Fills Input struct with 0s in memory
		if (Choice == 0)															//If user wants to autoclick at a certain spot
		{
			Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE |			//DWORD flags
				MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
			POINT CursorPos;														//POINT structure to store mouse location
			string PosKeyStr;
			cout << "Enter hex keycode of key to save cursor position (full list on MSDN)\n";
			cin >> PosKeyStr;
			int PosKey;																//The virtual keycodes on MSDN is in hex but the actual keycodes used by C++ functions is in decimal														
			while (!(ss << hex << PosKeyStr) || !(ss >> PosKey))					//If the entered string is invalid
			{																		//The good part about stringstreams, it can receive hex input and output it as decimal
				cout << "Invalid Input, please try again\n";
				stringstream().swap(ss);
				ss.clear();
				cin >> PosKeyStr;									
			}
			stringstream().swap(ss);												//Reset the stringstream to a brand new one
			unsigned long long Delay, Countdown, UserClicks, MouseClicks = 0;
			cout << "Set number of clicks\n";
			cin >> UserClicks;
			cout << "Set time between each click (in milliseconds)\n";
			cin >> Delay;
			cout << "Set countdown (in milliseconds)\n";
			cin >> Countdown;
			cout << "Press " << PosKeyStr << " to get the position of the cursor\n";
			while (true)															//Checks whether key is down or not with a loop. Takes decimal and not hex as parameter (as stated above)
			{
				if (GetAsyncKeyState(PosKey) < 0)
				{
					GetCursorPos(&CursorPos);
					break;
				}
			}
			Input.mi.dx = round(CursorPos.x * XScaleFactor);						//Explicitly saying to round because C++ always rounds towards zero by default
			Input.mi.dy = round(CursorPos.y * YScaleFactor);
			cout << "Countdown has started\n";
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
		else if (Choice == 1)														//If user wants to autoclick at a specific pixel
		{
			Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE |			//DWORD flags
				MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
			unsigned long long Delay, Countdown, UserClicks, MouseClicks = 0,
				CursorPosX, CursorPosY;
			cout << "Set X pixel position of cursor (left is 0 and right is max)"
				<< endl << "Horizontal cursor position: ";
			cin >> CursorPosX;
			cout << "Set Y pixel position of cursor (up is 0 and down is max)"
				<< endl << "Vertical cursor position: ";
			cin >> CursorPosY;
			cout << "Set number of clicks\n";
			cin >> UserClicks;
			cout << "Set time between each click (in milliseconds)\n";
			cin >> Delay;
			cout << "Set countdown (in milliseconds)\n";
			cin >> Countdown;
			Input.mi.dx = round(CursorPosX * XScaleFactor);							//Explicitly saying to round because C++ always rounds towards zero by default
			Input.mi.dy = round(CursorPosY * YScaleFactor);
			cout << "Countdown has started\n";
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
			string HotkeyStr;
			int Hotkey;
			cout << "Enter hex keycode of key to start clicking (full list on MSDN)\n";
			cin >> HotkeyStr;
			while (!(ss << hex << HotkeyStr) || !(ss >> Hotkey))					//If the entered string is invalid
			{
				cout << "Invalid Input, please try again\n";
				stringstream().swap(ss);
				ss.clear();
				cin >> HotkeyStr;
			}
			stringstream().swap(ss);
			unsigned long long Delay;
			cout << "Set time between each click (in milliseconds)\n";
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