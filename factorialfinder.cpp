// Copyright (C) 2015 by Michael Lin
// under the Microsoft Reference Source License (MS-RSL)

#include "stdafx.h"
#include <iostream>
using namespace std;

void findfactorial(__int64 num, __int64 factorialanswer)
{
	factorialanswer = factorialanswer * num;
	if (num == 1)
	{
		cout << factorialanswer << endl;
		return;
	}
	findfactorial (num - 1, factorialanswer);
}

int main()
{
	__int64 num, factorialanswer = 1;
	do
	{
		cout << "Must be positive integer equal to or greater than 1" << endl <<
				"Insert positive integer to be factored: ";
		cin >> num;
		cin.ignore();
	} while (num < 1);
	findfactorial (num, factorialanswer);
	cin.get();
	return 0;
}