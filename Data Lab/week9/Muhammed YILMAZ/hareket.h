#ifndef HAREKET_H
#define HAREKET_H

struct hareket
{
	char **maze;
	void create(char **Maze);
	void asagi(int row, int col);	//1
	void sag(int row, int col);		//2
	void sol(int row, int col);		//3
	void yukari(int row, int col);	//4
	int kontrol(int row, int col);
	void print();
};


#endif