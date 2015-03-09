// Copyright (C) 2015 by Michael Lin
// under the Microsoft Reference Source License (MS-RSL)

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