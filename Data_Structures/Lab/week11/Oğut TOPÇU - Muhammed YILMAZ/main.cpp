#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "yapilar.h"
#include "func.h"

using namespace std;

int main(int argc, char *argv[])
{
	int INITIAL_Y;
	int INITIAL_X;
	int FINISH_Y;
	int FINISH_X;


	srand(time(NULL));
	cell m[MAZESIZE][MAZESIZE]; // this is the maze
	cout << "x"; cin >> INITIAL_X;
	cout << endl << "y:"; cin >> INITIAL_Y;

	create(m, INITIAL_Y, INITIAL_X);
	print(m);
	getchar();
	cout << endl << endl;
	
	cout << "x"; cin >> FINISH_X;
	cout << endl << "y:"; cin >> FINISH_Y;
	find_path(m,INITIAL_Y,INITIAL_X,LEFT, FINISH_Y, FINISH_X);
	print(m);
	system("pause");
	return EXIT_SUCCESS;
}
