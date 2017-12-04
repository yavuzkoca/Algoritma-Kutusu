#ifndef FUNC_H
#define FUNC_H
#include "yapilar.h"
#include "stack.h"

void print(cell m[][MAZESIZE]);
void create(cell m[][MAZESIZE], int INITIAL_Y, int INITIAL_X);
int random_wall(cell m[][MAZESIZE], int y, int x,
	 stack *biriktir);
bool find_path(cell lab[][MAZESIZE], int y, int x, int camefrom, int FINISH_Y, int FINISH_X);
int random_unvisited_neighbor(cell m[][MAZESIZE], int y, int x);
#endif