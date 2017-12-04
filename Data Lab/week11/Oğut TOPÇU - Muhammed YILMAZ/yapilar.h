#ifndef YAPILAR_H
#define YAPILAR_H

#define MAZESIZE 8
/*
#define INITIAL_Y 2
#define INITIAL_X 0
#define FINISH_Y 2
#define FINISH_X 7*/

#define DOWN 1
#define RIGHT 2
#define UP 3
#define LEFT 4



/*typedef */struct cell {

	/* right = false when a wall does not exist otherwise,
	 * right = true means there is a wall
	 */
	bool left, right, up, down;
	/* initially this is empty (' '), when the cell is
	 * used to reach the exit, this becomes 'o'
	 */
	char val;
	/* this variable will be used while generating maze
	 * randomly (look the pseudo code for further information)
	 */
	bool visited;
};


#endif