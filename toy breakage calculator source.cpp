#include "stdafx.h"
#include <iostream>

using namespace std;

class Toy
{
public:
	Toy();
	~Toy();
	void chNofailure(int v);
	int chFailureoutput();
protected:
	int chFailure;
};

Toy::Toy()
{
	chFailure = 0;
}

Toy::~Toy()
{

}

void Toy::chNofailure ( int v )
{
	chFailure = 100 - v;
}

int Toy::chFailureoutput()  
{
	return chFailure;
}

int main()
{
	Toy play;  
	cout << "Insert precent chance you want this toy to not break when you use it." << endl <<"Must be less than 100% and greater than 0%." << endl << "Only numeric characters. Chance = ";
	int v;
	cin >> v;
	if (v > 100)
	{
		cout << "Well done on not reading the instructions. You broke the program, now you have to restart it" << endl;
		cin.get();
		cin.ignore();
		return 0;
	}
	else if (v <= 0)
	{
		cout << "Well done on not reading the instructions. You broke the program, now you have to restart it" << endl;
		cin.get();
		cin.ignore();
		return 0;
	}
	else
	{
		play.chNofailure ( v ); 
		cout<< play.chFailureoutput() << "% chance to break when you use it.";
	}
	cin.get();
	cin.ignore();
}