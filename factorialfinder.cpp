    /* Factorial Finder. Finds factorials of numbers through CLI.
    Copyright (C) 2014  Michael Lin

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

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