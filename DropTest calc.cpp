// DropTest calc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	cout << "DropTest Calculator. Finds out which test to drop so you get the highest mark.\nWhen you are done inserting numbers type 0 and press enter.\n";
	vector<vector<float>> marklist (0, vector<float> (2));
	int lettercounter = 0, i = 0;
	float num;
	bool input0 = false;
	for (; ; ++i, ++lettercounter)
	{
		for (; ;)
		{
			cout << "What did you get on test " << static_cast<char>('A' + lettercounter) << " ? ";
			cin >> num;
			if  (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input, try again." << endl;
			}
			else if (num < 0)
			{
				cout << "Must be positive number or 0" << endl;
			}
			else if (num == 0)
			{
				if (i > 0)
				{
					--i;
					input0 = true;
					break;
				}
				else
				{
					cout << "Must be positive number on first entry" << endl;
				}
			}
			else if (num > 0)
			{
				break;
			}
		}
		if (input0 == true)
		{
			break;
		}
		marklist.push_back(vector<float>(2));
		marklist[i][0] = num;
		for (; ;)
		{
			cout << "out of? ";
			cin >> num;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input, try again." << endl;
			}
			else if (num < 0)
			{
				cout << "Must be positive number or 0" << endl;
			}
			else if (num == 0)
			{
				if (i > 0)
				{
					--i;
					input0 = true;
					break;
				}
				else
				{
					cout << "Must be positive number on first entry" << endl;
				}
			}
			else if (num > 0)
			{
				break;
			}
		}
		if (input0 == true)
		{
			marklist.pop_back();
			break;
		}
		marklist[i][1] = num;
	}
	if (i == 0)
	{
		cout << "Only 1 entry recorded. Please rerun program.\nPress the enter key to exit.";
		cin.ignore();
		cin.get();
		return 0;
	}
	//cout << "ok" << endl << i << endl;
	int k = 0;
	float sumtop = 0, sumbot = 0;
	for (; k <= i; ++k)
	{
		sumtop += marklist[k][0];
		sumbot += marklist[k][1];
	}
	//cout << "ok" << endl << i << endl << k << endl;
	// cout << sumtop << ", " << sumbot << endl;
	vector<float> percents (i+1);
	for (k = 0; k <= i; ++k)
	{
		percents[k] = (sumtop - marklist[k][0]) / (sumbot - marklist[k][1]);
		// cout << percents[k] << endl;
	}
	//cout << "ok" << endl << i << endl << k << endl;
	int largestpos = distance(begin(percents), max_element(percents.begin(), percents.end()));
	float largestpercent = percents[largestpos];
	cout << "You should drop test " << static_cast<char>('A' + (largestpos)) << ". Doing so will give you a percent of " << largestpercent * 100 << "%." << endl;


	/* for (int j = 0; j < i ; ++j)
	{
		cout << marklist[j][0] << ", " << marklist[j][1] << endl;
	} */


	cout << "End of program. Rerun if you wish to use again.\nPress the enter key to exit." << endl;
	cin.ignore();
	cin.get();
	return 0;
}