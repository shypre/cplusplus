// TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

char XorO;
bool PlayerX;
char grid[9];
bool SideChosen;
int choice;
int i;
bool win;
void ChooseSquareO();

void CheckWin()
{
	if (grid[0] == '1' || grid[1] == '2' || grid[2] == '3' || grid[3] == '4' || grid[4] == '5' || grid[5] == '6' ||
		grid[6] == '7' || grid[7] == '8' || grid[8] == '9')
	{
		if ((grid[0] == 'x' && grid[1] == 'x' && grid[2] == 'x') || (grid[3] == 'x' && grid[4] == 'x' && grid[5] == 'x') ||
			(grid[6] == 'x' && grid[7] == 'x' && grid[8] == 'x') || (grid[0] == 'x' && grid[3] == 'x' && grid[6] == 'x') ||
			(grid[1] == 'x' && grid[4] == 'x' && grid[7] == 'x') || (grid[2] == 'x' && grid[5] == 'x' && grid[8] == 'x') ||
			(grid[0] == 'x' && grid[4] == 'x' && grid[8] == 'x') || (grid[2] == 'x' && grid[4] == 'x' && grid[6] == 'x'))
		{
			win = true;
			cout << "X wins!\n";
		}
		else if ((grid[0] == 'o' && grid[1] == 'o' && grid[2] == 'o') || (grid[3] == 'o' && grid[4] == 'o' && grid[5] == 'o') ||
			(grid[6] == 'o' && grid[7] == 'o' && grid[8] == 'o') || (grid[0] == 'o' && grid[3] == 'o' && grid[6] == 'o') ||
			(grid[1] == 'o' && grid[4] == 'o' && grid[7] == 'o') || (grid[2] == 'o' && grid[5] == 'o' && grid[8] == 'o') ||
			(grid[0] == 'o' && grid[4] == 'o' && grid[8] == 'o') || (grid[2] == 'o' && grid[4] == 'o' && grid[6] == 'o'))
		{
			win = true;
			cout << "O wins!\n";
		}
	}
	else
	{
		win = true;
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
		cout << "Enter the square you want to place your x marker: ";
		cin >> choice;
		/* if (choice != 1 || choice != 2 || choice != 3 || choice != 4 || choice != 5 || choice != 6 || choice != 7 || choice != 8 || choice != 9)
		{
			cout << "That is not a sqaure on the board!";
			ChooseSquareX();
		} */
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
		cout << "Enter the square you want to place your o marker: ";
		cin >> choice;
		/*if (choice != 1 || choice != 2 || choice != 3 || choice != 4 || choice != 5 || choice != 6 || choice != 7 || choice != 8 || choice != 9)
		{
			cout << "That is not a sqaure on the board!";
			ChooseSquareO();
		} */
		grid[choice - 1] = 'o';
		CheckWin();
		ChooseSquareX();
	}
}

int main()
{
start:
	SideChosen = false;
	win = false;
	i = 0;
	cout << "Welcome to TicTacToe!" << endl;
	for (; i < 9; i++)
	{
		grid[i] = '0' + (i + 1);
	}
	DrawGrid();
	cout << "Would you like to be x or o?" << endl;
	while (SideChosen == false)
	{
		cin >> XorO;
		if (XorO == 'x')
		{
			cout << "You are player X.\n";
			PlayerX = true;
			SideChosen = true;
		}
		else if (XorO == 'o')
		{
			cout << "You are player O\n";
			PlayerX = false;
			SideChosen = true;
		}
		else
		{
			cout << "Invalid input. Please try again.\n";
		}
	}
	if (PlayerX == true)
	{
		ChooseSquareX();
	}
	else
	{
		ChooseSquareO();
	}
	goto start;
	return 0;
}