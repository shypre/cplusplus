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
	char details;
	cout << "Factorial Finder  Copyright (C) 2014  Michael Lin \n" << 
		"This program comes with ABSOLUTELY NO WARRANTY; \n" <<
		"for details type `w' and press enter. \n" <<
		"This is free software, and you are welcome to \n" <<
		"redistribute it under certain conditions; \n" <<
		"type `c' and press enter for details. \n" <<
		"To continue, type `y'."<< endl;
license:
	cin >> details;
	cin.ignore();
	if (details == 'w')
	{
		cout << "This program is free software: you can redistribute it and/or modify \n" <<
				"it under the terms of the GNU General Public License as published by \n" <<
				"the Free Software Foundation, either version 3 of the License, or \n" <<
				"(at your option) any later version." << endl << endl;
		goto license;
	}
	else if (details == 'c')
	{
		cout << " This program is distributed in the hope that it will be useful, \n" <<
				"but WITHOUT ANY WARRANTY; without even the implied warranty of \n" <<
				"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. \n" <<
				"See the GNU General Public License for more details." << endl << endl;
		goto license;
	}
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