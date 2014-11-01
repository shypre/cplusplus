// practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	long double a, b, c, ans1, ans2;
start:
	cout << "Quadratic equation ax^2 + bx + c = 0. Enter a, b, c" << endl;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "c = ";
	cin >> c;
	if ((b*b - 4 * a*c) < 0)
	{
		cout << "discriminant is negative. Try again." << endl << "Press enter to reuse." << endl;
		cin.ignore();
		cin.get();
		goto start;
	}
	ans1 = ((sqrt((b*b - 4*a*c))) - b) / (2*a);
	ans2 = ((sqrt((b*b - 4*a*c))) + b) / (2*a);
	cout << ans1 << endl << ans2 << endl;
	cout << "Press enter to reuse." << endl;
	cin.ignore();
	cin.get();
	goto start;
	return 0;
}