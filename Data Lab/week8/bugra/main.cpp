#include <iostream>
#include <unistd.h>

#define ROW 14
#define COL 21

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
}StackDataType, position;

struct Node{
	StackDataType data;
	Node *next;
};

struct Stack{
	Node *top;
	void push(StackDataType);
	StackDataType pop();
	bool isEmpty();
	void create();
	void close();
};

void Stack::push(StackDataType data){
	Node *new_node = new Node;
	new_node->data = data;
	new_node->next = top;
	top = new_node;
}

StackDataType Stack::pop(){
	if(this->isEmpty()) return {-1,-1,0,0,0,0,0};
	StackDataType temp;
	temp = top->data;
	Node *temp_node = top;
	top = top->next;
	free(temp_node);
	return temp;
}

bool Stack::isEmpty(){
	return top == NULL ? true : false;
}

void Stack::create(){
	top = NULL;
}

void Stack::close(){
	while(!(this->isEmpty())){
		this->pop();
	}
}

void print_maze(char maze[ROW][COL+1]){
	for(int i = 0; i < ROW; ++i){
		cout << maze[i] << endl;
	}
	cout << endl;
}

position find_entrance(char maze[ROW][COL+1]){
	position entrance;
	entrance.up = 0;
	entrance.right = 0;
	entrance.down = 0;
	entrance.left = 0;
	entrance.before_position = 0;
	for(int i = 0; i < ROW; ++i){
		for(int j = 0; j < COL; ++j){
			if(maze[i][j] == 'o'){
				entrance.x = i;
				entrance.y = j;
				return entrance;
			}
		}
	}
	return {-1,-1,0,0,0,0,0};
}

position find_exit(char maze[ROW][COL+1]){
	position exit;
	exit.up = 0;
	exit.right = 0;
	exit.down = 0;
	exit.left = 0;
	exit.before_position = 0;
	for(int i = 0; i < ROW; ++i){
		for(int j = 0; j < COL; ++j){
			if(maze[i][j] == 'E'){
				exit.x = i;
				exit.y = j;
				return exit;
			}
		}
	}
	return {-1,-1,0,0,0,0,0};
}

int main(){

	char Maze[ROW][COL+1] = {
		"#o###################",
		"#     #      #    # #",
		"# ### # #### # ## # #",
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
		"###################E#" };

	Stack s;
	s.create();
	Stack steps;
	steps.create();

	position entrance = find_entrance(Maze);
	position exit = find_exit(Maze);
	position current = entrance;
	current.before_position = UP;
	steps.push(current);
	print_maze(Maze);

	bool go_back = false;
	while(current.x != exit.x || current.y != exit.y){
		Maze[current.x][current.y] = '*';
		print_maze(Maze);
		usleep(100000);

		if(!go_back){
			current.up = 0; current.right = 0; current.down = 0; current.left = 0;
			if(current.y > 0 && Maze[current.x][current.y-1] != '#') current.left = 1;
			if(current.y < COL-2 && Maze[current.x][current.y+1] != '#') current.right = 1;
			if(current.x > 0 && Maze[current.x-1][current.y] != '#') current.up = 1;
			if(current.x < ROW-1 && Maze[current.x+1][current.y] != '#') current.down = 1;
		}
		else go_back = false;

		bool moved = true;
		position past = current;
		if(current.up && current.before_position != UP){ current.x--; current.before_position = DOWN; past.up = 0; }
		else if(current.right && current.before_position != RIGHT){ current.y++; current.before_position = LEFT; past.right = 0; }
		else if(current.down && current.before_position != DOWN){ current.x++; current.before_position = UP; past.down = 0; }
		else if(current.left && current.before_position != LEFT){ current.y--; current.before_position = RIGHT; past.left = 0; }
		else moved = false;

		if(current.x != exit.x || current.y != exit.y){
			if(current.up + current.right + current.down + current.left > 2)
				s.push(past);
		}

		if(!moved){
			if( !( s.isEmpty() ) ){
				position desicion_point = s.pop();
				while(current.x != desicion_point.x || current.y != desicion_point.y){
					current = steps.pop();
					Maze[current.x][current.y] = ' ';
					print_maze(Maze);
					usleep(100000);
				}
				current = desicion_point;
				steps.push(current);
				go_back = true;
			}
		}
		else{
			steps.push(current);
		}

	}

	Maze[current.x][current.y] = 'X';
	print_maze(Maze);
	cout << "PATH found." << endl;


	s.close();
	steps.close();

	return 0;
}