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
	if ((b*b - 4*a*c) < 0)
	{
		cout << "discriminant is negative. Try again." << endl;
		goto start;
	}
	ans1 = (-1 * b) + (sqrt((b*b - 4*a*c)))/ 2*a;
	ans2 = (-1 * b) - (sqrt((b*b - 4*a*c)))/ 2*a;
	cout << ans1 << endl << ans2 << endl;
	cin.get();
	cin.ignore();
	return 0;
}