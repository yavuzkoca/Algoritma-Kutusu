#include <iostream>
#include <cstdlib>
#define SIZE 20

using namespace std;

char **minesField, **emptyField;

void create_fields();
void print_field(char **field);
void place_mines(int number, char **field);
void zero_fields(char **, char **);
int openBox(int, int);
void mines_say(int row, int col);
int control(int);
int putFlag (int row, int col);
int doOperation();


int main(int argc, char *argv[]) {
	
	create_fields();

	int numberMines;
	cout << "Enter a number of mines: ";
	cin >> numberMines;
	cout << "Number of mines: " << numberMines << endl;

	zero_fields(emptyField, minesField);
	place_mines(numberMines, minesField);

	print_field(minesField);

	int exit = 0;
	while(!exit)
	{
		print_field(emptyField);
		exit = doOperation();
		if(control(numberMines) == 0)
		{
			cout << endl << "\nYOU ARE WINNER!" << endl;
			print_field(minesField);
			cout << endl << "\nYOU ARE WINNER!" << endl;
			return EXIT_SUCCESS;
		}
	}
	cout << endl << endl <<	 "\t\tGAME OVER!" << endl;
	print_field(emptyField);
	cout << endl <<	 "\t\tGAME OVER!" << endl;
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
 //			field2[i][j]='-';
		}
	}
}

int openBox(int row, int col){

	int say = 0;
	/* Game Over */
	if(minesField[row][col] == 'X')	{

		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				if(minesField[i][j] == 'X')	emptyField[i][j]='X';
			}
		}
		return 1;

	} else if (emptyField[row][col] == '*') {

		return 0;

	} else if (emptyField[row][col] == '-') {

		mines_say(row, col);
		return 0;

	} else if (isdigit(emptyField[row][col])) {

		for (int i = -1; i < 2; ++i) {
			
			for (int j = -1; j < 2; ++j) {
				
				if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE){
					
					continue;
				}
				if(emptyField[row+i][col+j]== '*')	say++;
			}
		}

		if(say == emptyField[row][col] - '0') {

			for (int i = -1; i < 2; ++i) {

				for (int j = -1; j < 2; ++j) {

					if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE){
						continue;
					}
					if(emptyField[row+i][col+j]!= '*') {
						mines_say(row+i, col+j);
					}
				}
			}
			return 0;
		}

	}
}

void mines_say(int row, int col){

	if(emptyField[row][col]==' ')	return;

	int say = 0;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE){
				continue;
			}
			if(minesField[row+i][col+j]== 'X')	say++;
		}
	}

	if(say != 0)	emptyField[row][col] = '0' + say;
	else
	{
		emptyField[row][col] = ' ';

		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE) {
					
					continue;
				}	
				mines_say(row+i, col+j);
			}
		}
	}
}

int control(int numberMines){
	
	int say = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if(emptyField[i][j]=='-')	say++;
		}
	}
	
	return (say-numberMines);
}

int putFlag (int row, int col){

	if (emptyField[row][col] == '-') {

		emptyField[row][col] = '*';
	} else if (emptyField[row][col] == '*') {

		emptyField[row][col] = '-';
	}
	return 0;
}

int doOperation() {

	char op;
	int row, col;

	cout << endl << "   Operation (O/P):" << endl
		 << "       Open Box (O) / Put Flag (P)" << endl;
	cout << "Enter \"Operation\", \"Row\" and \"Column\": ";
	cin >> op >> row >> col;

	/* Put Flag */
	if (op == 'P' || op == 'p')	{
		
		return putFlag(row, col);
	} else if (op == 'O' || op == 'o') {
		
		return openBox(row, col);
	} else {
		
		cout << "Please enter valid operations!" << endl;
		return 0;
	}
}