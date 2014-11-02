// practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	long long n1, n2;
	long long x = 1;
	cout << "first number and second number: ";
	cin >> n1 >> n2;
	long double dn1 = n1, dn2 = n2;
	if (n1 <= 1 || n2 <= 1)
	{
		cout << "Number cannot be less than 1" << endl << "Press enter to continue" << endl;
		cin.ignore();
		cin.get();
		return 1;
	}
	long double sqn1 = sqrt(dn1), sqn2 = sqrt(dn2);
	long long lsqn1 = sqn1, lsqn2 = sqn2;
	while (x <= lsqn1 || x <= lsqn2)
	{
		if ((n1 % x == 0) && (n2 % x == 0))
		{
			cout << n1/x << ", " << x << endl;
		}
		x++;
	}
	cout << "Press enter to continue" << endl;
	cin.ignore();
	cin.get();
	return 0;
}