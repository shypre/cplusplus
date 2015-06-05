// DropTest calc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	cout << "DropTest Calculator. Finds out which test to drop so you get the highest mark.\nWhen you are done inserting numbers type done and press enter.\n";
	vector<vector<float>> marklist(1, vector<float>(2));
	cout << "What did you get on test A? ";
	cin >> marklist[0][0];
	cout << "out of? ";
	cin >> marklist[0][1];
	int lettercounter = 1;
	float num;
	int i = 1;
	for (;; ++i, ++lettercounter)
	{
		cout << "What did you get on test " << static_cast<char>('A' + lettercounter) << " ? ";
		cin >> num;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			break;
		}
		marklist.push_back(vector<float>(2));
		marklist[i][0] = num;
		cout << "out of? ";
		cin >> num;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			marklist.pop_back();
			break;
		}
		marklist[i][1] = num;
	}
	int k = 0;
	float sumtop = 0;
	float sumbot = 0;
	while (k < i)
	{
		sumtop += marklist[k][0];
		++k;
	}
	k = 0;
	while (k < i)
	{
		sumbot += marklist[k][1];
		++k;
	}
	// cout << sumtop << ", " << sumbot << endl;
	vector<float> percents(i);
	for (k = 0; k < i;)
	{
		percents[k] = (sumtop - marklist[k][0]) / (sumbot - marklist[k][1]);
		// cout << percents[k] << endl;
		++k;
	}
	int largestpos = distance(begin(percents), max_element(percents.begin(), percents.end()));
	float largestpercent = percents[largestpos];
	cout << "You should drop test " << static_cast<char>('A' + (largestpos)) << ". Doing so will give you a percent of " << largestpercent * 100 << "%." << endl;


	/* for (int j = 0; j < i ; ++j)
	{
	cout << marklist[j][0] << ", " << marklist[j][1] << endl;
	} */


	cout << "End of program. Rerun if you wish to use again.\nPress the enter key to exit." << endl;
	cin.get();
	return 0;
}