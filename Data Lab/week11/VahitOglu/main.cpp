#include <iostream>
#include <vector>
#include <random>

#include "stack.h"
#include "cell.h"

#define MAZESIZE 10

using namespace std;

void init_maze(cell maze[][MAZESIZE]){
	for(int i = 0; i < MAZESIZE; ++i){
		for(int j = 0; j < MAZESIZE; ++j){
			maze[i][j].visited = false;
			maze[i][j].val = ' ';
			maze[i][j].up = true; maze[i][j].right = true; maze[i][j].down = true; maze[i][j].left = true;
		}
	}

}

void print_maze(cell maze[][MAZESIZE]){
	for(int i = 0; i < MAZESIZE; ++i){
		for(int j = 0; j < MAZESIZE; ++j){
			if(maze[i][j].up)
				cout << " -";
			else
				cout << "  ";
		}
		cout << endl;
		cout << "|";
		for(int j = 0; j < MAZESIZE; ++j){
			if(maze[i][j].right)
				cout << maze[i][j].val << "|";
			else
				cout << maze[i][j].val << " ";
		}
		cout << endl;
	}
	for(int i = 0; i < MAZESIZE; ++i){
		if(maze[MAZESIZE - 1][i].down)
			cout << " -";
	}
	cout << endl;
}

void create_maze(cell maze[][MAZESIZE], coordinate current, Stack *cells, int *visited_count){

	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(0, 1e9 + 7);

	if(*visited_count != MAZESIZE * MAZESIZE){

		cout << "Bismillah " << *visited_count << endl;

		vector<coordinate> currents_unvisited_neighbours;

		if(current.i != 0 && !maze[current.i - 1][current.j].visited){
			coordinate up; up.i = current.i - 1; up.j = current.j;
			currents_unvisited_neighbours.push_back(up);
		}
		if(current.i != MAZESIZE - 1 && !maze[current.i + 1][current.j].visited){
			coordinate down; down.i = current.i + 1; down.j = current.j;
			currents_unvisited_neighbours.push_back(down);
		}
		if(current.j != 0 && !maze[current.i][current.j - 1].visited){
			coordinate left; left.i = current.i; left.j = current.j - 1;
			currents_unvisited_neighbours.push_back(left);
		}
		if(current.j != MAZESIZE - 1 && !maze[current.i][current.j + 1].visited){
			coordinate right; right.i = current.i; right.j = current.j + 1;
			currents_unvisited_neighbours.push_back(right);
		} // Decide the unvisited neighbours and push them into a vector

		cout << "Hadi eyvallah " << currents_unvisited_neighbours.size() << endl;

		if(currents_unvisited_neighbours.size() != 0){
			coordinate random = currents_unvisited_neighbours[dist(gen) % currents_unvisited_neighbours.size()];
			cells->push(current);
			int vertical = random.i - current.i, horizontal = random.j - current.j;

			if(vertical == -1){ maze[current.i][current.j].up = false; maze[random.i][random.j].down = false; }
			else if(vertical == 1){ maze[current.i][current.j].down = false; maze[random.i][random.j].up = false; }
			else if(horizontal == -1){ maze[current.i][current.j].left = false; maze[random.i][random.j].right = false; }
			else{ maze[current.i][current.j].right = false; maze[random.i][random.j].left = false; }

			maze[random.i][random.j].visited = true; ++(*visited_count);
			cout << "1" << endl;
			create_maze(maze, random, cells, visited_count);
		}
		else if(!cells->isEmpty()){
			cout << "2" << endl;
			cells->print();
			create_maze(maze, cells->pop(), cells, visited_count);
		}
		else{
			int random_i, random_j;
			random_i = dist(gen) % MAZESIZE; random_j = dist(gen) % MAZESIZE;
			maze[random_i][random_j].visited = true; ++(*visited_count);
			coordinate random; random.i = random_i; random.j = random_j;
			cout << "3" << endl;
			create_maze(maze, random, cells, visited_count);
		}
	}
}

int main(){
	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(0, 1e9 + 7);
	Stack cells;
	cells.create();
	cell maze[MAZESIZE][MAZESIZE];
	init_maze(maze);
	coordinate current; current.i = dist(gen) % MAZESIZE; current.j = dist(gen) % MAZESIZE; //entrance
	maze[current.i][current.j].visited = true;
	int visited_count = 0;
	create_maze(maze, current, &cells, &visited_count);
	cout << "AA" << endl;
	print_maze(maze);
	return EXIT_SUCCESS;
}