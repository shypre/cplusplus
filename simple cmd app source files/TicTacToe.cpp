#include "stdafx.h"
#include <iostream>

using namespace std;

char XorO;
char grid[9] {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int choice;
bool win;
void ChooseSquareO();
char Replay;
bool GoodInput = false;
void DrawGrid();

void CheckWin()
{
	if ((grid[0] == 'x' && grid[1] == 'x' && grid[2] == 'x') || (grid[3] == 'x' && grid[4] == 'x' && grid[5] == 'x') ||
		(grid[6] == 'x' && grid[7] == 'x' && grid[8] == 'x') || (grid[0] == 'x' && grid[3] == 'x' && grid[6] == 'x') ||
		(grid[1] == 'x' && grid[4] == 'x' && grid[7] == 'x') || (grid[2] == 'x' && grid[5] == 'x' && grid[8] == 'x') ||
		(grid[0] == 'x' && grid[4] == 'x' && grid[8] == 'x') || (grid[2] == 'x' && grid[4] == 'x' && grid[6] == 'x'))
	{
		win = true;
		DrawGrid();
		cout << "X wins!\n";
	}
	else if ((grid[0] == 'o' && grid[1] == 'o' && grid[2] == 'o') || (grid[3] == 'o' && grid[4] == 'o' && grid[5] == 'o') ||
		(grid[6] == 'o' && grid[7] == 'o' && grid[8] == 'o') || (grid[0] == 'o' && grid[3] == 'o' && grid[6] == 'o') ||
		(grid[1] == 'o' && grid[4] == 'o' && grid[7] == 'o') || (grid[2] == 'o' && grid[5] == 'o' && grid[8] == 'o') ||
		(grid[0] == 'o' && grid[4] == 'o' && grid[8] == 'o') || (grid[2] == 'o' && grid[4] == 'o' && grid[6] == 'o'))
	{
		win = true;
		DrawGrid();
		cout << "O wins!\n";
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

void DrawGrid()
{
	cout << "+---+---+---+" << endl << "| " << grid[0] << " | " << grid[1] << " | " << grid[2] << " |" << endl 
	<< "+---+---+---+" << endl << "| " << grid[3] << " | " << grid[4] << " | " << grid[5] << " |" << endl 
	<< "+---+---+---+" << endl << "| " << grid[6] << " | " << grid[7] << " | " << grid[8] << " |" << endl 
	<< "+---+---+---+" << endl;
}

void ChooseSquareX()
{
	if (win == false)
	{
		DrawGrid();
		GoodInput = false;
		cout << "Enter the square you want to place your x marker: ";
		while (GoodInput == false)
		{
			cin >> choice;
			while (cin.fail() || choice < 1 || choice > 9)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "That is not a number between 1 and 9. Try again: ";
				cin >> choice;
			}
			while (grid[choice - 1] == 'x' || grid[choice - 1] == 'o')
			{
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "That square is taken! Try again: ";
				cin >> choice;
			}
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			GoodInput = true;
		}
		grid[choice - 1] = 'x';
		CheckWin();
		ChooseSquareO();
	}
}

void ChooseSquareO()
{
	if (win == false)
	{
		DrawGrid();
		GoodInput = false;
		cout << "Enter the square you want to place your o marker: ";
		while (GoodInput == false)
		{
			cin >> choice;
			while (cin.fail() || choice < 1 || choice > 9)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "That is not a number between 1 and 9. Try again: ";
				cin >> choice;
			}
			while (grid[choice - 1] == 'x' || grid[choice - 1] == 'o')
			{
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "That square is taken! Try again: ";
				cin >> choice;
			}
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			GoodInput = true;
		}
		grid[choice - 1] = 'o';
		CheckWin();
		ChooseSquareX();
	}
}

int main()
{
	while (true)
	{
		XorO = ' ';
		win = false;
		cout << "Welcome to TicTacToe!" << endl;
		DrawGrid();
		cout << "Would you like to be x or o?" << endl;
		while (XorO == ' ')
		{
			cin >> XorO;
			if (cin.fail())
			{
				cout << "That is not a valid choice. Try again: ";
				XorO = ' ';
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
			else if (XorO == 'x')
			{
				cout << "You are player X.\n";
				ChooseSquareX();
			}
			else if (XorO == 'o')
			{
				cout << "You are player O\n";
				ChooseSquareO();
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
		if (Replay == 'y')
		{
		}
		else
		{
			break;
		}
	}
	return 0;
}