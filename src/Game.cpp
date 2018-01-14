//============================================================================
// Name        : Hello.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "conio.h"

using namespace std;
bool gameOver;
const int width = 20, height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT};
eDirection dir;


void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {

//	system ("CLS");
	clrscr();
	for(int j = 0 ; j < height ; ++j) {
		for(int i = 0; i < width ;++i) {

		   if(i == 0 || i == (width - 1) || j == 0 || j == (height - 1))
			   cout << "# ";
		   else if(i == fruitX && j == fruitY)
			   cout << "$ ";
		   else if(i == x && j == y)
			   cout << "O ";
		   else
			   cout << "  ";


		}
		cout << endl;
	}


}

void Input() {
	if (_kbhit()) {

		switch (_getch()) {
			case 'a':
				dir = LEFT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'x':
				gameOver = true;
				break;
		}

	}

}

void Logic() {

	switch (dir) {
		case STOP:
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case RIGHT:
			x++;
			break;
		case LEFT:
			x--;
			break;
	}

	if (x > width-1 || x < 1 || y > height-1 || y < 1)
		gameOver = true;

	if(x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width-1;
		fruitY = rand() % height-1;

	}

}

void ClearScreen (void) {
	DWORD n;                         /* Number of characters written */
	DWORD size;                      /* number of visible characters */
	COORD coord = {0};               /* Top left screen position */
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	/* Get a handle to the console */
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

	GetConsoleScreenBufferInfo ( h, &csbi );

	/* Find the number of characters to overwrite */
	size = csbi.dwSize.X * csbi.dwSize.Y;

	/* Overwrite the screen buffer with whitespace */
	FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
	GetConsoleScreenBufferInfo ( h, &csbi );
	FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

	/* Reset the cursor to the top left position */
	SetConsoleCursorPosition ( h, coord );
}

int main() {

	Setup();
	while(!gameOver) {
		Draw();
		Input();
		Logic();
		ClearScreen();
	}
	system ("PAUSE");

	return 0;
}
