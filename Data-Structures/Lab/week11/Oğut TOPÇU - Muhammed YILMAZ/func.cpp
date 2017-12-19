#include <iostream>
#include <cstdlib>
#include <time.h>
#include "func.h"
#include "yapilar.h"
#include "stack.h"
#include <stdlib.h>
#include <Windows.h>
using namespace std;


void print(cell m[][MAZESIZE]){

	for(int i = 0; i < MAZESIZE; i++)
	{
		for(int j = 0; j < MAZESIZE; j++)
		{
			if(m[i][j].up) 
				cout << " -";
			else
				cout << "  ";
		}

		cout << endl;
		cout << "|";

		for(int j = 0; j < MAZESIZE; j++)
		{
			if(m[i][j].right)
				cout << m[i][j].val << "|";
			else
				cout << m[i][j].val << " ";
		}

		cout << endl;
	}

	for(int i = 0; i < MAZESIZE; i++)
	{
		if(m[MAZESIZE-1][i].down)
			cout << " -";
	}
	cout << endl;
}


void create(cell m[][MAZESIZE], int INITIAL_Y, int INITIAL_X){
	for (int i = 0; i < MAZESIZE; ++i)
	{
		for (int j = 0; j < MAZESIZE; ++j)
		{
			m[i][j].left = true;
			m[i][j].right = true;
			m[i][j].down = true;
			m[i][j].up = true;
			m[i][j].visited = false;
			m[i][j].val = ' ';
		}
	}
	stack biriktir;
	biriktir.create();
	int unvisited = MAZESIZE*MAZESIZE;
	int visited = random_wall(m, INITIAL_Y, INITIAL_X, &biriktir);
	cout << "------" << visited << "------" << endl;
/*	int currentX = INITIAL_X,
		currentY = INITIAL_Y;
	int goY, goX;
	int randomWay = 0;
	while(!unvisited)
	{
		randomWay = random_unvisited_neighbor(m, currentY, currentX);
	
		if(!randomWay)
		{
			goY = currentY;
			goX = currentX;
			biriktir.push(currentY, currentX);

			if (randomWay == UP)
			{
				goY--;
				m[currentY][currentX].up = false;
				m[goY][goX].down = false;
			}
			else if (randomWay == DOWN)
			{
				goY++;
				m[currentY][currentX].down = false;
				m[goY][goX].up = false;
			}
			else if (randomWay == RIGHT)
			{
				goX++;
				m[currentY][currentX].right = false;
				m[goY][goX].left = false;
			}
			else if (randomWay == LEFT)
			{
				goX--;
				m[currentY][currentX].left = false;
				m[goY][goX].right = false;
			}
			else 
			{
				cout << "\t-------" << endl;
				cout << "\t-------" << endl;
				cout << "\tErr: 01" << endl;
				cout << "\t-------" << endl;
				cout << "\t-------" << endl;
			}

		}
		m[currentY][currentX].visited = true;
		unvisited--;
		
	}*/
}

int random_wall(cell m[][MAZESIZE], int y, int x,
	 stack *biriktir){

	
	int currentY = y,
		currentX = x;
	int goY, goX;
	int randomWay = random_unvisited_neighbor(m, currentY, currentX);

	m[currentY][currentX].visited = true;
	if(randomWay)
	{
		goY = currentY;
		goX = currentX;
		biriktir->push(currentY, currentX);

		if (randomWay == UP)
		{
			goY--;
			m[currentY][currentX].up = false;
			m[goY][goX].down = false;
		}
		else if (randomWay == DOWN)
		{
			goY++;
			m[currentY][currentX].down = false;
			m[goY][goX].up = false;
		}
		else if (randomWay == RIGHT)
		{
			goX++;
			m[currentY][currentX].right = false;
			m[goY][goX].left = false;
		}
		else if (randomWay == LEFT)
		{
			goX--;
			m[currentY][currentX].left = false;
			m[goY][goX].right = false;
		}
		else 
		{
			cout << "\t-------" << endl;
			cout << "\t-------" << endl;
			cout << "\tErr: 01" << endl;
			cout << "\t-------" << endl;
			cout << "\t-------" << endl;
		}

		currentY = goY;
		currentX = goX;

		return 1 + random_wall(m, currentY, currentX, biriktir);
	}
	else if(biriktir->tepeEleman != NULL)
	{
		currentY = biriktir->top()->y;
		currentX = biriktir->top()->x;
		biriktir->pull();
		return random_wall(m, currentY, currentX, biriktir);
	}/*
	else
	{
		currentY = rand() % MAZESIZE;
		currentX = rand() % MAZESIZE;
		return 1 + random_wall(m, currentY, currentX, biriktir);
	}*/
	
}

int random_unvisited_neighbor(cell m[][MAZESIZE], int y, int x){

	int sec[4], say = 0;

	if(y>0 && m[y-1][x].visited == false)
	{
		sec[say++] = UP;
	}
	if(y<MAZESIZE-1 && m[y+1][x].visited == false)
	{
		sec[say++] = DOWN;
	}
	if(x>0 && m[y][x-1].visited == false)
	{
		sec[say++] = LEFT;
	}
	if(x<MAZESIZE-1 && m[y][x+1].visited == false)
	{
		sec[say++] = RIGHT;
	}
	if(say == 0)
	{
		return 0;
	}
	else
	{
		return sec[rand() % say];
	}
}

bool find_path(cell lab[][MAZESIZE], int y, int x, int camefrom, int FINISH_Y, int FINISH_X) {
	
	lab[y][x].val = 'o';
	
	print(lab);
	Sleep(100);
	system("cls");
	cout << "d" << lab[y][x].down << "u" << lab[y][x].up << "l"


		<< lab[y][x].left << "r" << lab[y][x].right << endl;
	

	if (x == FINISH_X && y == FINISH_Y){
		return true;
	}

	if(x>0 && lab[y][x].left != true && camefrom != LEFT )
	{	
		if (find_path(lab, y, x - 1, RIGHT, FINISH_Y, FINISH_X)) // go left
			return true;
	}		
	if(y<MAZESIZE-1 && lab[y][x].down != true && camefrom != DOWN )
	{
		if (find_path(lab, y + 1, x, UP, FINISH_Y, FINISH_X)) // go down
			return true;
	}
	if(y>0 && lab[y][x].up != true && camefrom != UP )
	{	
		if (find_path(lab, y - 1, x, DOWN, FINISH_Y, FINISH_X)) // go up
			return true;
	}
	if(x<MAZESIZE-1 && lab[y][x].right != true && camefrom != RIGHT)
	{
		if (find_path(lab, y, x + 1, LEFT, FINISH_Y, FINISH_X)) // go right
			return true;
	}
	lab[y][x].val = ' ';
	return false;
}
