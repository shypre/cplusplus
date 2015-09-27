// vector calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
	char repeat = 'y';
	while (repeat == 'y')
	{
		unsigned int n;
		cout << "How many vectors do you want to add? ";
		cin >> n;
		vector<long double> lengths, angles;
		vector<char> quadrants;
		lengths.resize(n);
		quadrants.resize(n);
		angles.resize(n);
		char quadrant;
		long double length, angle;
		for (unsigned int i = 0; i < n; ++i)
		{
			cout << "Enter length of vector, start of vector is at orgin: ";
			cin >> length;
			lengths[i] = length;
			cout << "Enter quadrant the vector is pointing at.\nIf it is horizontal or vertical enter u, d, l, or r: ";
			cin >> quadrant;
			quadrants[i] = quadrant;
			cout << "Enter angle of vector from x-axis.\nIf vector is horizontal or vertical, enter 0: ";
			cin >> angle;
			angles[i] = angle/180 * 3.1415926535;
		}
		long double sumX = 0, sumY = 0, FinalLength, FinalAngle;
		char FinalQuadrant;
		for (unsigned int i = 0; i < n; ++i)
		{
			switch (quadrants[i])
			{
			case '1':
				sumX += lengths[i] * cos(angles[i]);
				sumY += lengths[i] * sin(angles[i]);
				break;
			case '2':
				sumX -= lengths[i] * cos(angles[i]);
				sumY += lengths[i] * sin(angles[i]);
				break;
			case '3':
				sumX -= lengths[i] * cos(angles[i]);
				sumY -= lengths[i] * sin(angles[i]);
				break;
			case '4':
				sumX += lengths[i] * cos(angles[i]);
				sumY -= lengths[i] * sin(angles[i]);
				break;
			case 'u':
				sumY += lengths[i];
				break;
			case 'd':
				sumY -= lengths[i];
				break;
			case 'l':
				sumX -= lengths[i];
				break;
			case 'r':
				sumX += lengths[i];
				break;
			}
		}
		if (sumX > 0 && sumY > 0)
		{
			FinalQuadrant = '1';
		}
		else if (sumX < 0 && sumY > 0)
		{
			FinalQuadrant = '2';
		}
		else if (sumX < 0 && sumY < 0)
		{
			FinalQuadrant = '3';
		}
		else if (sumX > 0 && sumY < 0)
		{
			FinalQuadrant = '4';
		}
		else
		{
			FinalQuadrant = 'l';
		}
		FinalLength = hypot(fabs(sumX), fabs(sumY));
		FinalAngle = atan(fabs(sumY) / fabs(sumX));
		FinalAngle = FinalAngle / 3.1415926535 * 180;
		for (unsigned int i = 0; i < n; ++i)
		{
			cout << quadrants[i] << endl << lengths[i] << endl << angles[i] << endl;
		}
		if (FinalQuadrant != 'l')
		{
			cout << "The final vector is pointing towards quadrant " << FinalQuadrant << ", has length " << FinalLength << ", and has angle "
				<< FinalAngle << " degrees from the x-axis." << endl << "The coordinates are (" << sumX << ", " << sumY << ").";
		}
		else
		{
			cout << "The final vector is either horizontal or vertical and has coordinates (" << sumX << ", " << sumY << ").";
		}
		cout << endl << "Repeat? y/n: ";
		cin >> repeat;
	}
	cin.get();
	return 0;
}
