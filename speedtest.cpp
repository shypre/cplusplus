// practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	time_t timer;
	unsigned long long x = 0, y = time(&timer);
	while (x <= 100000000)
	{
		x++;
	}
	cout << endl << y << endl << time(&timer);
	cin.get();
	cin.ignore();
}