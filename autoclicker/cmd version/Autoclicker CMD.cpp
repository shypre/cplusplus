//Autoclicker (cmd version). Copyright 2015 Michael Lin.
//
#include "stdafx.h"
#define NOMINMAX																	//max() is already defined in Windows.h, but it is a different function than what is in <limits>
#include "Windows.h"																//This #define is built into Windows.h so you can undefine min() and max() from that header
#include <iostream>
#include <sstream>																	//Better way than stoi() or etc. to convert from string to number is stringstreams
#include <limits>																	//Where the max() we want is from
#include <algorithm>
#include <string>
#include <conio.h>
#include "VirtualKeys.h"
#include <tclap/CmdLine.h>															//Templatized Command Line Argument Parser from tclap.sourceforge.net
#ifdef _DEBUG
#undef _DEBUG																		//By default python does not include the debug object files
#include "C:\Python27\include\Python.h"												//So we just undefine debug mode, include the header, and redefine it
#define _DEBUG
#else
#include "C:\Python27\include\Python.h"
#endif

using namespace std;

void FailedInput()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Invalid input, please try again\n";
}

void ClearStream()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(int argc, char *argv[])
{
	try
	{
		cout.precision(16);																//Sets all floating points that are outputted to have 16 decimal places
		TCLAP::CmdLine cmd("Command line argument parser", ' ', "v0.1", true);
		TCLAP::SwitchArg swPython("p", "python", "Option to use clicking sequences feature using Python interpreter", cmd, false);
		TCLAP::ValueArg<string> pyfileT("f", "filename", "Name of file that contains the python function", false, "", "Name of file that contains the python function", cmd, false);
		TCLAP::ValueArg<string> pyfunctionT("t", "funcname", "Name of function in the .py file", false, "", "Name of function in the .py file", cmd, false);
		cmd.parse(argc, argv);
		bool usePy = swPython.getValue();
		char Repeat = 'y';
		while (Repeat == 'y')
		{
			double ScreenResX = GetSystemMetrics(SM_CXSCREEN),							//Gets screen resolution of main monitor
				ScreenResY = GetSystemMetrics(SM_CYSCREEN);
			double XScaleFactor = 65535 / ScreenResX,									//The scale factor between SendInput's 65535 mapping and screen resolution. Go on MSDN for more info
				YScaleFactor = 65535 / ScreenResY;
			stringstream ss;															//Declare it right now because we can reuse this over and over
			unsigned long long Choice;
			cout << "To view help, enter 0\n"
				<< "To have the mouse autoclick at a certain point, enter 1\n"
				<< "To have the mouse autoclick at a specific pixel, enter 2\n"
				<< "To have the mouse autoclick wherever the cursor is, enter 3\n"
				<< "To autopress a key, enter 4\n";
			cin >> Choice;
			while (cin.fail() || Choice > 4)											//In case the user is stupid and/or can't read
			{
				FailedInput();
				cin >> Choice;
			}
			ClearStream();
			INPUT Input = { 0 };														//INPUT structure used by SendInput. 0 is mouse input
			INPUT Inputkbd = { 1 };
			ZeroMemory(&Input, sizeof(Input));											//Apparently this helps avoid blackscreens with SendInput. Fills Input struct with 0s in memory
			ZeroMemory(&Inputkbd, sizeof(Inputkbd));
			Inputkbd.type = INPUT_KEYBOARD;
			if (Choice == 0)
			{
				cout << "Autoclicker (cmd version). Copyright 2015 Michael Lin\n"
					<< "This program simulates mouse clicks and keyboard presses.\n"
					<< "Use at your own risk, the creator of this program is not liable for any damages caused.\n"
					<< "End of help\n\n";
				continue;
			}
			else if (Choice == 1)														//If user wants to autoclick at a certain spot
			{
				Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK |		//DWORD flags
					MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
				POINT CursorPos;														//POINT structure to store mouse location
				string PosKeyStr;
				cout << "Enter hex keycode of key to save cursor position (full list on MSDN)\n";
				cin >> PosKeyStr;
				int PosKey;																//The virtual keycodes on MSDN is in hex but the actual keycodes used by C++ functions is in decimal														
				while (!(ss << hex << PosKeyStr) || !(ss >> PosKey))					//If the entered string is invalid
				{																		//The good part about stringstreams, it can receive hex input and output it as decimal
					FailedInput();
					ss.str("");
					ss.clear();
					cin >> PosKeyStr;
				}
				ClearStream();
				ss.str("");
				ss.clear();
				unsigned long long Delay, Countdown, UserClicks, MouseClicks = 0;
				cout << "Set number of clicks\n";
				cin >> UserClicks;
				cout << "Set time between each click (in milliseconds)\n";
				cin >> Delay;
				cout << "Set countdown (in milliseconds)\n";
				cin >> Countdown;
				cout << "Press " << hex << "0x" << PosKey << " to get the position of the cursor\n";
				while (true)															//Checks whether key is down or not with a loop. Takes decimal and not hex as parameter (as stated above)
				{
					if (GetAsyncKeyState(PosKey) < 0)
					{
						GetCursorPos(&CursorPos);
						break;
					}
					Sleep(100);															//Polling period of 100 milliseconds
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
			else if (Choice == 2)														//If user wants to autoclick at a specific pixel
			{
				Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK |		//DWORD flags
					MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
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
			else if (Choice == 3)														//If user wants to autoclick wherever their cursor is
			{
				cout << "Press any key, then hold down the key you want to use to start clicking\n";
				_getch();
				Sleep(500);
				int i = 0, Hotkey;
				for (int j = 0;; j++)
				{
					if (GetAsyncKeyState(i) < 0)
					{
						Hotkey = i;
						i = j - 1;
						break;
					}
					i = VKeyList[j].VKey;
					if (j == 176)
					{
						j = -1;
					}
					Sleep(1);
				}
				cout << VKeyList[i].Description << " is the key to start clicking\n";
				Sleep(1000);
				cout << "Press any key, then hold down the key you want to use to stop clicking\n";
				_getch();
				Sleep(500);
				int k = 0, Stopkey;
				for (int j = 0;; j++)
				{
					if (GetAsyncKeyState(k) < 0)
					{
						Stopkey = k;
						k = j - 1;
						break;
					}
					k = VKeyList[j].VKey;
					if (j == 176)
					{
						j = -1;
					}
					Sleep(1);
				}
				cout << VKeyList[k].Description << " is the key to stop clicking\n";
				unsigned long long Delay, Period;
				bool ZeroIsLeft = 0;
				cout << "Enter 0 for left click or 1 for right click\n";
				cin >> ZeroIsLeft;
				cout << "Set time between each click (in milliseconds)\n";
				cin >> Delay;
				if (usePy == true)
				{
					PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pArgs;				//Python/C API stuff
					string pyfileT2 = pyfileT.getValue();
					const char* pyfile = pyfileT2.c_str();
					string pyfunctionT2 = pyfunctionT.getValue();
					const char* pyfunction = pyfunctionT2.c_str();
					Py_Initialize();														//Start the Python interpreter
					pName = PyString_FromString(pyfile);
					pModule = PyImport_Import(pName);
					pDict = PyModule_GetDict(pModule);
					pFunc = PyDict_GetItemString(pDict, pyfunction);
					if (PyCallable_Check(pFunc))
					{
						pArgs = PyTuple_New(1);
						pValue = PyInt_FromLong(Delay);
						PyTuple_SetItem(pArgs, 0, pValue);
						pValue = PyObject_CallObject(pFunc, pArgs);
						Py_DECREF(pArgs);													//Every time you use a python object you increase its reference count
						Delay = PyInt_AsLong(pValue);
						cout << "Return of call: " << Delay << endl;
						Py_DECREF(pValue);													//And every time you stop using a python object you decrease its reference count
						Py_Finalize();														//Close the python interpreter
					}
					else
					{
						PyErr_Print();
					}
				}
				else
				{
					cout << "Not using Python\nValue of usePy: " << usePy << endl;
				}
				cout << "Set time between clickdown and clickup (in milliseconds)\n";
				cin >> Period;
				cout << "Hold " << VKeyList[i].Description << " to start clicking and " << VKeyList[k].Description << " to stop clicking\n";
				if (ZeroIsLeft == 0)
				{
					while (true)															//While user holds down key, it will click
					{
						if (GetAsyncKeyState(Stopkey) < 0)
						{
							cout << "Stopped autoclicking\n";
							break;
						}
						if (GetAsyncKeyState(Hotkey) < 0)
						{
							Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;						//DWORD flags
							SendInput(1, &Input, sizeof(INPUT));
							Sleep(Period);
							Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;							//DWORD flags
							SendInput(1, &Input, sizeof(INPUT));
						}
						Sleep(Delay - Period);
					}
				}
				else if (ZeroIsLeft == 1)
				{
					while (true)															//While user holds down key, it will click
					{
						if (GetAsyncKeyState(Stopkey) < 0)
						{
							cout << "Stopped autoclicking\n";
							break;
						}
						if (GetAsyncKeyState(Hotkey) < 0)
						{
							Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;						//DWORD flags
							SendInput(1, &Input, sizeof(INPUT));
							Sleep(Period);
							Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;							//DWORD flags
							SendInput(1, &Input, sizeof(INPUT));
						}
						Sleep(Delay - Period);
					}
				}
			}
			else if (Choice == 4)
			{
				cout << "Press any key, then hold down the key you want to use to start autopressing\n";
				_getch();
				Sleep(500);
				int i = 0, Hotkey;
				for (int j = 0;; j++)
				{
					if (GetAsyncKeyState(i) < 0)
					{
						Hotkey = i;
						i = j - 1;
						break;
					}
					i = VKeyList[j].VKey;
					if (j == 176)
					{
						j = -1;
					}
					Sleep(1);
				}
				cout << VKeyList[i].Description << " is the key to start clicking\n";
				Sleep(1000);
				cout << "Press any key, then hold down the key you want to use to stop autopressing\n";
				_getch();
				Sleep(500);
				int k = 0, Stopkey;
				for (int j = 0;; j++)
				{
					if (GetAsyncKeyState(k) < 0)
					{
						Stopkey = k;
						k = j - 1;
						break;
					}
					k = VKeyList[j].VKey;
					if (j == 176)
					{
						j = -1;
					}
					Sleep(1);
				}
				cout << VKeyList[k].Description << " is the key to stop clicking\n";
				Sleep(1000);
				cout << "Press any key, then hold down the key you want to autopress\n";
				_getch();
				Sleep(500);
				int l = 0, Presskey;
				for (int j = 0;; j++)
				{
					if (GetAsyncKeyState(l) < 0)
					{
						Presskey = l;
						l = j - 1;
						break;
					}
					l = VKeyList[j].VKey;
					if (j == 176)
					{
						j = -1;
					}
					Sleep(1);
				}
				Inputkbd.ki.wVk = VKeyList[l].VKey;
				cout << VKeyList[l].Description << " is the key to autopress\n";
				unsigned long long Delay, Period;
				cout << "Set time between each press (in milliseconds)\n";
				cin >> Delay;
				cout << "Set time between pressdown and pressup (in milliseconds)\n";
				cin >> Period;
				cout << "Hold " << VKeyList[i].Description << " to start autopressing " << VKeyList[l].Description << " and " << VKeyList[k].Description << " to stop autopressing\n";
				while (true)															//While user holds down key, it will click
				{
					if (GetAsyncKeyState(Stopkey) < 0)
					{
						cout << "Stopped autoclicking\n";
						break;
					}
					if (GetAsyncKeyState(Hotkey) < 0)
					{
						Inputkbd.ki.dwFlags = 0;											//DWORD flags
						SendInput(1, &Inputkbd, sizeof(INPUT));
						Sleep(Period);
						Inputkbd.ki.dwFlags = KEYEVENTF_KEYUP;								//DWORD flags
						SendInput(1, &Inputkbd, sizeof(INPUT));
					}
					Sleep(Delay - Period);
				}

			}
			cout << "Repeat?\ny/n: ";
			cin >> Repeat;
		}
		cout << "Press any key to exit\n";
		_getch();
		return 0;
	}
	catch (const TCLAP::ArgException& e)
	{
		cerr << "Something went wrong in the command line arguments...\nargID: " << e.argId() << ", errorDesc: " << e.error() << ", typeDesc: " << e.typeDescription() << ", what: " << e.what() << endl;
		_getch();
		return 1;
	}
	catch (int errorNum)
	{
		if (errorNum == 1)
		{
			cerr << "Not enough command line arguments given\nPress any key to exit\n";
			_getch();
			return 1;
		}
		else
		{
			cerr << "Something went wrong somewhere...\nPress any key to exit\n";
			_getch();
			return -1;
		}
	}
}