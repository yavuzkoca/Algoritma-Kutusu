#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "yapilar.h"
#include "hareket.h"

using namespace std;

#define DEFROW 14
#define DEFCOL 22

stack dizi;
hareket labirent, cikti;

stackKonum find_point(char cLower, char cUpper);
void create_maze(hareket *hMaze, char table[DEFROW][DEFCOL]);
bool ilerle();
void continuePress();

/*
	"#o###################",
	"#     #      #    # #",
	"# ### # ###### ## # #",
	"# # #        # #  # #",
	"# # ### ######## ## #",
	"#     # # ##   #    #",
	"### # # # ## # # ####",
	"# # # # #    #      #",
	"# # # # # ######### #",
	"# # # # # #       # #",
	"# # #   # # #####   #",
	"# # ##### # #   #####",
	"#         #   #     #",
	"###################E#" 
	*/

char Maze[DEFROW][DEFCOL] = {
	"#o###################",
	"#     #      #    # #",
	"# ### # ###### ## # #",
	"# # #        # #  # #",
	"# # ### ######## ## #",
	"#     # # ##   #    #",
	"### # # # ## # # ####",
	"# # # # #    #      #",
	"# # # # # ######### #",
	"# # # # # #       # #",
	"# # #     # #####   #",
	"# # ##### # #   #####",
	"#         #   #     #",
	"###################E#" 
};

int main(int argc, char *argv[])
{
	create_maze(&labirent, Maze);
	create_maze(&cikti, Maze);

	stackKonum startPoint = find_point('o', 'O');
	stackKonum exitPoint = find_point('e', 'E');
	cout << startPoint.row << "-" << startPoint.col << endl;
	cout << exitPoint.row << "-" << exitPoint.col << endl;

	dizi.create();
	dizi.push(&startPoint);
	dizi.show(stdout);

	labirent.print();
	while(1)
	{
		continuePress();
		if(ilerle() == EXIT_SUCCESS)
		{
			cikti.print();
			cout << endl << endl << "You are winner!" << endl;
			return EXIT_SUCCESS;
		}
		
		cikti.print();
	}

	return EXIT_SUCCESS;
}

void continuePress(){

	getchar();
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

stackKonum find_point(char cLower, char cUpper){
	stackKonum temp;
	for (int i = 0; i < DEFROW; ++i)
	{
		for (int j = 0; j < DEFCOL; ++j)
		{
			if(labirent.maze[i][j] == cLower || labirent.maze[i][j] == cUpper)
			{
				temp.row = i;
				temp.col = j;
				return temp;
			}
		}
	}
}


void create_maze(hareket *hMaze, char table[DEFROW][DEFCOL]){

	hMaze->maze = new char*[DEFROW+1];
	for (int i = 0; i < DEFROW; ++i)
	{
		hMaze->maze[i] = new char[DEFCOL];
	}
	for (int i = 0; i < DEFROW; ++i)
	{
		for (int j = 0; j < DEFCOL; ++j)
		{
			hMaze->maze[i][j] = table[i][j];
		}
	}
}

bool ilerle(){

	stackKonum *top = new stackKonum;
	stackKonum topSta = dizi.top();
	top->row = topSta.row;
	top->col = topSta.col;
	int yon = labirent.kontrol(top->row, top->col);

	if (yon == 1)
	{
		top->row++;
		labirent.maze[top->row][top->col] = 'o';
		cikti.maze[top->row][top->col] = 'o';
		dizi.push(top);
	}
	else if (yon == 2)
	{
		top->col++;
		labirent.maze[top->row][top->col] = 'o';
		cikti.maze[top->row][top->col] = 'o';
		dizi.push(top);
	}
	else if (yon == 3)
	{
		top->col--;
		labirent.maze[top->row][top->col] = 'o';
		cikti.maze[top->row][top->col] = 'o';
		dizi.push(top);
	}
	else if (yon == 4)
	{
		top->row--;
		labirent.maze[top->row][top->col] = 'o';
		cikti.maze[top->row][top->col] = 'o';
		dizi.push(top);
	}
	else if(yon == 5)
	{
		return EXIT_SUCCESS;
	}
	else if(yon == 6)
	{
		labirent.maze[top->row][top->col] = '-';
		cikti.maze[top->row][top->col] = ' ';
		dizi.pull();
	}

	return EXIT_FAILURE;
}
