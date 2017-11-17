#include <iostream>
#include "hareket.h"

using namespace std;

int hareket::kontrol(int row, int col){

	if(maze[row+1][col] == ' ')		//hareket.asagi()
	{
		return 1;
	}
	if(maze[row][col+1] == ' ')		//hareket.sag()
	{
		return 2;
	}
	if(maze[row][col-1] == ' ')		//hareket.sol()
	{
		return 3;
	}
	if(maze[row-1][col] == ' ')		//hareket.yukari()
	{
		return 4;
	}
	if( maze[row+1][col] == 'E' || maze[row+1][col] == 'e' ||
		maze[row][col+1] == 'E' || maze[row][col+1] == 'e' ||
		maze[row][col-1] == 'E' || maze[row][col-1] == 'e' ||
		maze[row-1][col] == 'E' || maze[row-1][col] == 'e' )
	{
		cout << "You are winner!" << endl;
		return 5;
	}
	if( maze[row+1][col] == 'O' || maze[row+1][col] == 'o' ||
		maze[row][col+1] == 'O' || maze[row][col+1] == 'o' ||
		maze[row][col-1] == 'O' || maze[row][col-1] == 'o' ||
		maze[row-1][col] == 'O' || maze[row-1][col] == 'o' )
	{
		return 6;
	}

	return 0;
}

void hareket::print(){

	cout << endl << endl;
	for (int i = 0; maze[i] != NULL; ++i)
	{
		cout << maze[i] << endl;
	}
}