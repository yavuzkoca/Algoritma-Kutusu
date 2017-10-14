#include <iostream>
#include <cstdlib>
#define SIZE 20

using namespace std;

char **minesField, **emptyField;

void create_fields();
void print_field(char **field);
void place_mines(int number, char **field);
void zero_fields(char **, char **);
int click(int, int);
void mines_say(int row, int col);

int main(int argc, char *argv[])
{
	
	create_fields();

	int numberMines;
	cout << "Enter a number of mines: ";
	cin >> numberMines;
	cout << "Number of mines: "<<numberMines<<endl;

	zero_fields(emptyField, minesField);
	place_mines(numberMines, minesField);

//	print_field(minesField);

	int exit = 0;
	int row, col;
	while(!exit)
	{
		print_field(emptyField);
		cout << "Enter row and column: ";
		cin >> row;
		cin >> col;
		exit = click(row,col);
	}
	cout << "\tGAME OVER!" << endl;
	print_field(emptyField);
	return EXIT_SUCCESS;
}

void print_field(char **field){
	cout << endl;
	for (int i = -1; i < SIZE+1; ++i)
	{
		if(i==-1 || i==SIZE)	cout << "  ";
		else 		cout << i%10 << " ";
		for (int j = 0; j < SIZE; ++j)
		{
			if(i==-1)
			{
				cout<<j%10<<" ";
			}
			else if(i==SIZE)
			{
				cout<<j%10<<" ";
			}
			else	cout << field[i][j] << " ";
		}
		if(i==-1 || i==SIZE)	cout << endl;
		else 					cout << i%10 << endl;
	}
}

void place_mines(int number, char **field){
	srand (time(NULL));
	for (int a = 0; a < number; ++a)
	{
		int i = rand() % SIZE, j = rand() % SIZE;
		if(field[i][j]!='X')	field[i][j]='X';
		else					a--;
	}
}

void create_fields(){

	minesField = new char*[SIZE];
	emptyField = new char*[SIZE];
	for (int i = 0; i < SIZE; ++i)
	{
		*(minesField+i) = new char[SIZE];
		*(emptyField+i) = new char[SIZE];
	}
}

void zero_fields(char **field1, char **field2){

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			field1[i][j]='-';
			field2[i][j]='-';
		}
	}
}

int click(int row, int col){

	if(minesField[row][col] == 'X')	
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				if(minesField[i][j] == 'X')	emptyField[i][j]='X';
			}
		}
		return 1;
	}

	mines_say(row, col);
	
	return 0;
}

void mines_say(int row, int col){

	if(emptyField[row][col]==' ')	return;
	int say = 0;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE)	continue;
			if(minesField[row+i][col+j]== 'X')	say++;
		}
	}

	if(say != 0)	emptyField[row][col] = '0' + say;
	else
	{
		emptyField[row][col] = ' ';
		print_field(emptyField);

		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE)	continue;
				mines_say(row+i, col+j);
			}
		}
	}
}