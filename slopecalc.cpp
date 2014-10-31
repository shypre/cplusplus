// practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	float y2, y1, x2, x1, m, b;
start:
	cout << "x1: ";
	cin >> x1;
	cout << "x2: ";
	cin >> x2;
	cout << "y1: ";
	cin >> y1;
	cout << "y2: ";
	cin >> y2;
	if (x2 - x1 == 0)
	{
		cout << "Slope is vertical line!" << endl;
		cin.ignore();
		cin.get();
		return 1;
	}
	m = (y2 - y1)/(x2 - x1);
	b = y2 - (m * x2);
	cout << "equation: y = " << m << "x + " << b;
	cin.ignore();
	cin.get();
	goto start;
	return 0;
}