#include <iostream>
#include <cmath>
using namespace std;

void findfactorial(long long num, long long factorialanswer)
{
	factorialanswer =factorialanswer * num;
	if (num==1)
	{
		cout << factorialanswer << endl;
		return;
	}
	findfactorial (num - 1, factorialanswer);
}

int main()
{
	long long factorialanswer = 1;
	long long num;
input:
	cout << "Insert positive integer to be factored: ";
	cin >> num;
	if (num < 1)
	{
		cout << "Must be positive integer";
		goto input;
	}
	else if (num == 1)
	{
		cout << "Must be positive integer";
		goto input;
	}
	cin.ignore();
	findfactorial (num, factorialanswer);
	cin.get();
	return 0;
}
