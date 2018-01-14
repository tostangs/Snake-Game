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
enum eDirection {stop = 0, up, down, left, right};
eDirection dir;


void Setup() {
	gameOver = false;
	dir = stop;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {

	system("cls");
	for(int j = 0 ; j < height ; ++j) {
		for(int i = 0; i < width ;++i) {

		   if(i == 0 || i == (width - 1) || j == 0 || j == (height - 1))
			   cout << "* ";
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

		switch (char val = _getch()) {
			case 'a':
				dir = left;
				break;
			case 'w':
				dir = up;
				break;
			case 's':
				dir = down;
				break;
			case 'd':
				dir = right;
			case 'x':
				gameOver = true;
				break;
		}

	}

}

void Logic() {

}

int main() {
	Setup();
	while(!gameOver) {
		Draw();
		Input();
		Logic();
	}

	return 0;
}
