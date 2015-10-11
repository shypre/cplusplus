#include "stdafx.h"
#include <iostream>

using namespace std;

char XorO;
char grid[9];
unsigned int choice;
bool win;
char Replay = 'y';

void DrawGrid()
{
	cout<< "+---+---+---+" << endl << "| " << grid[0] << " | " << grid[1] << " | " << grid[2] << " |" << endl
		<< "+---+---+---+" << endl << "| " << grid[3] << " | " << grid[4] << " | " << grid[5] << " |" << endl
		<< "+---+---+---+" << endl << "| " << grid[6] << " | " << grid[7] << " | " << grid[8] << " |" << endl
		<< "+---+---+---+" << endl;
}

void CheckWin()
{
	if ((grid[0] == XorO && grid[1] == XorO && grid[2] == XorO) || (grid[3] == XorO && grid[4] == XorO && grid[5] == XorO) ||
		(grid[6] == XorO && grid[7] == XorO && grid[8] == XorO) || (grid[0] == XorO && grid[3] == XorO && grid[6] == XorO) ||
		(grid[1] == XorO && grid[4] == XorO && grid[7] == XorO) || (grid[2] == XorO && grid[5] == XorO && grid[8] == XorO) ||
		(grid[0] == XorO && grid[4] == XorO && grid[8] == XorO) || (grid[2] == XorO && grid[4] == XorO && grid[6] == XorO))
	{
		win = true;
		DrawGrid();
		cout << "X wins!\n";
	}
	else if (grid[0] == '1' || grid[1] == '2' || grid[2] == '3' || grid[3] == '4' || grid[4] == '5' || grid[5] == '6' ||
		grid[6] == '7' || grid[7] == '8' || grid[8] == '9')
	{}
	else
	{
		win = true;
		DrawGrid();
		cout << "It's a draw!\n";
	}
}

void ChooseSquare(char XorO)
{
	if (win == false)
	{
		DrawGrid();
		cout << "Enter the square you want to place your " << XorO << " marker: ";
		while (true)
		{
			cin >> choice;
			if (cin.fail() || choice < 1 || choice > 9)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "That is not a number between 1 and 9. Try again: ";
				continue;
			}
			if (grid[choice - 1] == 'x' || grid[choice - 1] == 'o')
			{
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "That square is taken! Try again: ";
				continue;
			}
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			break;
		}
		grid[choice - 1] = XorO;
		CheckWin();
		if (XorO == 'x')
		{
			XorO = 'o';
		}
		else
		{
			XorO = 'x';
		}
		ChooseSquare(XorO);
	}
}

int main()
{
	while (Replay == 'y')
	{
		for (int i = 0; i < 9; i++)
		{
			grid[i] = '0' + i + 1;
		}
		XorO = ' ';
		win = false;
		cout << "Welcome to TicTacToe!" << endl;
		DrawGrid();
		cout << "Would you like to be x or o?" << endl;
		while (XorO == ' ')
		{
			cin >> XorO;
			if (XorO == 'x' || XorO == 'o')
			{
				cout << "You are player " << XorO << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				ChooseSquare(XorO);
			}
			else
			{
				cout << "Invalid input. Please try again: ";
				XorO = ' ';
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
		}
		cout << "Replay? y/n";
		cin >> Replay;
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	}
	cout << "Press enter to exit\n";
	cin.get();
	return 0;
}