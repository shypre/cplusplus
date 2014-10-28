// practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	long long n;
	long long x = 1;
	cin >> n;
	if (n <= 1)
	{
		cout << "Number cannot be less than 1" << endl << "Press enter to continue" << endl;
		cin.ignore();
		cin.get();
		return 0;
	}
	long long sqn = sqrt(n);
	while (x <= sqn)
	{
		if (n % x == 0)
		{
			cout << n/x << ", " << x << endl;
		}
		x++;
	}
	cout << "Press enter to continue" << endl;
	cin.ignore();
	cin.get();
	return 0;
}