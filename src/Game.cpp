//============================================================================
// Name        : WhatIsLifeHahahaha.cpp
// Author      : Not me haha
// Version     : idk honestly
// Copyright   : Your copyright notice
// Description : Three dots for depression, the game for the excitement... ;)
//============================================================================

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include "conio.h"

using namespace std;
bool beginGame, gameOver;
const int width = 20, height = 20;
int x, y, fruitX, fruitY, score;
int tailX[400], tailY[400];
int nTails;
enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT};
eDirection dir;

void Setup() {
	// The beginning of the program...
	beginGame = true;
	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;

	// This creates the original location of the fruit...
	bool created;

	do {
		created = true;
		// The creation of the location of the fruit without it being inside of the tail or head...
		srand(time(NULL));
		fruitX = rand()%(18)+1;
		srand(time(NULL));
		fruitY = rand()%(18)+1;

		for (int i = 1; i < nTails; i++) {
			if ((tailX[i] == fruitX && tailY[i] == fruitY) || (x == fruitX && y == fruitY)) {
				created = false;
			}

		}

	} while(!created);
	score = 0;
}


void Draw() {

	// This is the startup screen in the beginning of the game... :)
	if (beginGame) {
		cout << endl << "Press any button to play :)" << endl << endl;
		system ("PAUSE");
		beginGame = false;
	}

	// This clears the screen... Though it's not very good lol I'm so lonely...
	system ("CLS");

	cout << endl << "Score: " << score << endl;
	// This is the logic to draw the 20x20 grid aka the barriers...
	for(int j = 0 ; j < height ; ++j) {

		for(int i = 0; i < width ; ++i) {

		   if(i == 0 || i == (width-1) || j == 0 || j == (height-1))
			   cout << "# ";
		   else if(i == fruitX && j == fruitY)
			   cout << "$ ";
		   else if(i == x && j == y)
			   cout << "0 ";
		   else {
			   bool print = false;
			   for (int k = 0; k < nTails; ++k) {

				   if(tailX[k] == i && tailY[k] == j) {
					   cout << "o ";
					   print = true;
				   }
			   }
			   if(!print)
				   cout << "  ";
		   }
		}
		cout << endl;
	}

}

void Input() {

	// Changes the enum variable 'eDirection' based on the input...
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

	// This creates the logic for the tail of the Snake
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTails; i++) {

		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}

	// This creates the barriers and the triggers the game to end if crossed...
	if (x >= width-1 || x == 0 || y >= height-1 || y == 0)
			gameOver = true;

	// Logic behind the changing in direction.
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

	if(x == fruitX && y == fruitY) {

		// Increases the score by 10, then generates another position for the fruit and adds a segment to the tail...
		bool created;
		nTails++;
		score += 10;
		do {

			created = true;
			// The creation of the location of the fruit without it being inside of the tail or head...
			srand(time(NULL));
			fruitX = rand()%(18)+1;
			srand(time(NULL));
			fruitY = rand()%(18)+1;

			for (int i = 1; i < nTails; i++) {
				if ((tailX[i] == fruitX && tailY[i] == fruitY) || (x == fruitX && y == fruitY)) {
					created = false;
				}

			}

		} while(!created);
	}
}

void reset() {

	x = width/2;
	y = width/2;

	for (int i = 0; i < nTails; ++i) {
		tailX[i] = NULL;
		tailY[i] = NULL;
	}
	nTails = 0;
	score = 0;

}

int main() {

	bool restart = false;
	char res;
	do {
		restart = false;
		reset();
		Setup();
		while(!gameOver) {
			Draw();
			Sleep(50);
			Input();
			Logic();
		}

		system ("CLS");
		cout << "# # # # # # # # # # # # # # # # # # # #" << endl;
		cout << endl << "Game Over...	You Scored: " << score << " Points" << endl;
		cout << "Press 'R' to play again." << endl;
		cout << endl << "# # # # # # # # # # # # # # # # # # # #" << endl;
		cin >> res;
		if(res == 'r' || res == 'R') {
			restart = true;
			gameOver = false;
			system ("CLS");
		}

	} while (restart);

	return 0;
}
