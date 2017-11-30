#include <iostream>
#include <vector>
#include <random>
#include <unistd.h>

#include "cell.h"

#define MAZESIZE 10

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

typedef struct pos{
	int before_position;
	int up;
	int right;
	int down;
	int left;
	int x;
	int y;
}position;

struct coordinate{int i, j;};

template <typename StackDataType>
struct StackNode{
	StackDataType data;
	StackNode *next;
};

template <typename StackDataType>
struct Stack{
	StackNode<StackDataType> *top;
	void push(StackDataType);
	StackDataType pop();
	bool isEmpty();
	void create();
	void close();
};

template <typename StackDataType>
void Stack<StackDataType>::push(StackDataType data){
	StackNode<StackDataType> *new_node = new StackNode<StackDataType>;
	new_node->data = data;
	new_node->next = top;
	top = new_node;
}

template <typename StackDataType>
StackDataType Stack<StackDataType>::pop(){
	StackDataType temp;
	temp = top->data;
	StackNode<StackDataType> *temp_node = top;
	top = top->next;
	delete temp_node;
	return temp;
}

template <typename StackDataType>
bool Stack<StackDataType>::isEmpty(){ return top == 0 ? true : false; }
template <typename StackDataType>
void Stack<StackDataType>::create(){ top = 0;}
template <typename StackDataType>
void Stack<StackDataType>::close(){ while(!isEmpty()) pop(); }

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
				cout << " _";
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
			cout << " _";
	}
	cout << endl;
}

void create_maze(cell maze[][MAZESIZE], coordinate current, Stack<coordinate> *cells, int *visited_count){

	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(0, 1e9 + 7);

	if(*visited_count != MAZESIZE * MAZESIZE){

		coordinate currents_unvisited_neighbours[4];

		int size = 0;

		if(current.i != 0 && !maze[current.i - 1][current.j].visited){ // up
			currents_unvisited_neighbours[0].i = current.i - 1; currents_unvisited_neighbours[0].j = current.j;
			size++;
		}
		else currents_unvisited_neighbours[0].i = -1;
		if(current.i != MAZESIZE - 1 && !maze[current.i + 1][current.j].visited){ // down
			currents_unvisited_neighbours[1].i = current.i + 1; currents_unvisited_neighbours[1].j = current.j;
			size++;
		}
		else currents_unvisited_neighbours[1].i = -1; // left
		if(current.j != 0 && !maze[current.i][current.j - 1].visited){
			currents_unvisited_neighbours[2].i = current.i; currents_unvisited_neighbours[2].j = current.j - 1;
			size++;
		}
		else currents_unvisited_neighbours[2].i = -1; // right
		if(current.j != MAZESIZE - 1 && !maze[current.i][current.j + 1].visited){
			currents_unvisited_neighbours[3].i = current.i; currents_unvisited_neighbours[3].j = current.j + 1;
			size++;
		}
		else currents_unvisited_neighbours[3].i = -1;
		// Decide the unvisited neighbours and push them into a vector

		if(size != 0){

			int decision;
			int random_decision = dist(gen) % size;
			int count = 0;

			for(int i = 0; i < 4; ++i){
				if(currents_unvisited_neighbours[i].i == -1) continue;
				if(count == random_decision) decision = i;
				++count;
			}


			coordinate random = currents_unvisited_neighbours[decision];
			cells->push(current);
			int vertical = random.i - current.i, horizontal = random.j - current.j;

			if(vertical == -1){ maze[current.i][current.j].up = false; maze[random.i][random.j].down = false; }
			else if(vertical == 1){ maze[current.i][current.j].down = false; maze[random.i][random.j].up = false; }
			else if(horizontal == -1){ maze[current.i][current.j].left = false; maze[random.i][random.j].right = false; }
			else{ maze[current.i][current.j].right = false; maze[random.i][random.j].left = false; }

			maze[random.i][random.j].visited = true; ++(*visited_count);
			create_maze(maze, random, cells, visited_count);
		}
		else if(!cells->isEmpty()){
			create_maze(maze, cells->pop(), cells, visited_count);
		}
		else{
			int random_i, random_j;
			random_i = dist(gen) % MAZESIZE; random_j = dist(gen) % MAZESIZE;
			if(!maze[random_i][random_j].visited) maze[random_i][random_j].visited = true; ++(*visited_count);
			coordinate random; random.i = random_i; random.j = random_j;
			create_maze(maze, random, cells, visited_count);
		}
	}
}

void solve_maze_recurse(cell maze[][MAZESIZE],
						position *current,
						position *exit,
						Stack<position> *s,
						Stack<position> *steps,
						Stack<position> *temp_steps,
						bool *go_back){
	if(current->x != exit->x || current->y != exit->y){
		maze[current->x][current->y].val = 'o';
		print_maze(maze);
		usleep(50000);

		if(!(*go_back)){
			current->up = 0; current->right = 0; current->down = 0; current->left = 0;
			if(!maze[current->x][current->y].left) current->left = 1;
			if(!maze[current->x][current->y].right) current->right = 1;
			if(!maze[current->x][current->y].up) current->up = 1;
			if(!maze[current->x][current->y].down) current->down = 1;
		}
		else *go_back = false;

		bool moved = true;
		position past = *current;
		if(current->up && current->before_position != UP){ current->x--; current->before_position = DOWN; past.up = 0; }
		else if(current->right && current->before_position != RIGHT){ current->y++; current->before_position = LEFT; past.right = 0; }
		else if(current->down && current->before_position != DOWN){ current->x++; current->before_position = UP; past.down = 0; }
		else if(current->left && current->before_position != LEFT){ current->y--; current->before_position = RIGHT; past.left = 0; }
		else moved = false;

		if(current->x != exit->x || current->y != exit->y){
			if(current->up + current->right + current->down + current->left >= 2){
				bool flag = false;
				position temp_current = steps->pop();
				while(!steps->isEmpty()){
					position temp = steps->pop();
					temp_steps->push(temp);
					if(temp.x == temp_current.x && temp.y == temp_current.y)
						flag = true;
				}
				while(!temp_steps->isEmpty()){
					steps->push(temp_steps->pop());
				}
				if(flag){
					*current = steps->pop();
					maze[current->x][current->y].val = ' ';
					moved = false;
				}
				else{
					steps->push(temp_current);
					s->push(past);
				}
			}
		}

		if(!moved){
			if( !( s->isEmpty() ) ){
				position decision_point = s->pop();
				while(current->x != decision_point.x || current->y != decision_point.y){
					*current = steps->pop();
					maze[current->x][current->y].val = ' ';
					print_maze(maze);
					usleep(50000);
				}
				*current = decision_point;
				steps->push(*current);
				*go_back = true;
			}
		}
		else{
			steps->push(*current);
		}
		solve_maze_recurse(maze, current, exit, s, steps, temp_steps, go_back);
	}
}

void solve_maze(cell maze[][MAZESIZE]){
	Stack<position> s;
	s.create();
	Stack<position> steps;
	steps.create();
	Stack<position> temp_steps;
	temp_steps.create();

	position entrance;
	position exit;

	cout << "Enter the entrance coordinates: ";
	cin >> entrance.x >> entrance.y;

	cout << "Enter the exit coordinates: ";
	cin >> exit.x >> exit.y;

	position current = entrance;
	current.before_position = UP;
	steps.push(current);
	print_maze(maze);

	bool go_back = false;

	solve_maze_recurse(maze, &current, &exit, &s, &steps, &temp_steps, &go_back);

	maze[current.x][current.y].val = 'X';
	print_maze(maze);
	cout << "PATH found." << endl;

	while(!steps.isEmpty()){
		temp_steps.push(steps.pop());
	}

	while(!temp_steps.isEmpty()){
		position temp = temp_steps.pop();
		cout << "[" << temp.x << "," << temp.y << "]" << endl;
	}

	s.close();
	steps.close();
	temp_steps.close();
}

int main(){
	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(0, 1e9 + 7);
	Stack<coordinate> cells; cells.create(); 
	cell maze[MAZESIZE][MAZESIZE]; init_maze(maze);
	coordinate current; current.i = dist(gen) % MAZESIZE; current.j = dist(gen) % MAZESIZE; //entrance
	maze[current.i][current.j].visited = true;
	int visited_count = 0;
	create_maze(maze, current, &cells, &visited_count);
	print_maze(maze);

	solve_maze(maze);

	return EXIT_SUCCESS;
}