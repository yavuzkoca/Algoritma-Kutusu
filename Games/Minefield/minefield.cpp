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
int countFoundBox(char **field, int row, int col, char found);
int solve();
void reverseBoxToFlag(int row, int col);
int countFoundBoxFromField(char **field, char found);
void winner();
void loser();
void finishGame();

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
		cout << endl << "Mines: " << numberMines << "\t\t\t";
		cout << "Flag: " << countFoundBoxFromField(emptyField, '*') << endl;
		print_field(emptyField);
		exit = doOperation();
		if(control(numberMines) == 0)
		{
			winner();
			return EXIT_SUCCESS;
		}
	}
	loser();
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
			field2[i][j]=' ';
		}
	}
}

int openBox(int row, int col){

	/* Bayraklı ise açılmaz. */
	if (emptyField[row][col] == '*') 
	{
	} 
	/* Game Over */
	else if(minesField[row][col] == 'X')	
	{
		finishGame();
		return 1;
	}
	/* Kapalı kutu ise açılır. */
	else if (emptyField[row][col] == '-') 
	{
		mines_say(row, col);
	} 
	/* Sayı var ise ...*/
	else if (isdigit(emptyField[row][col])) 
	{
		int say = countFoundBox(emptyField, row, col, '*');

		if(say == emptyField[row][col] - '0') 
		{
			for (int i = -1; i < 2; ++i) 
			{
				for (int j = -1; j < 2; ++j) 
				{
					if(row+i <0 || row+i >= SIZE || col+j <0 || col+j >= SIZE)
					{
						continue;
					}
					if(emptyField[row+i][col+j]!= '*') 
					{
						mines_say(row+i, col+j);
					}
				}
			}
		}
	}
	return 0;
}

void mines_say(int row, int col){

	if(emptyField[row][col]==' ')	return;

	int say = 0;
	say = countFoundBox(minesField, row, col, 'X');

	if(say != 0)	emptyField[row][col] = '0' + say;
	else
	{
		emptyField[row][col] = ' ';

		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE) 
				{
					continue;
				}	
				mines_say(row+i, col+j);
			}
		}
	}
}

int control(int numberMines){
	
	int mines_say = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if(emptyField[i][j] == '-' || emptyField[i][j] == '*')	
			{
				mines_say++;
			}
		}
	}
	
	if(mines_say - numberMines == 0)
	{
		return 0;
	}
	return !0;
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
	cin >> op;
	if(op == 'S' || op == 's')
	{
		return solve();
	}

	cin >> row >> col;

	if(row >= SIZE || col >= SIZE || row < 0 || col < 0)
	{

		cout << "Please enter valid coordinate!" << endl;
		return 0;
	}
	/* Put Flag */
	else if (op == 'P' || op == 'p')	
	{
		return putFlag(row, col);
	}
	else if (op == 'O' || op == 'o')
	{
		return openBox(row, col);
	}
	else
	{
		cout << "Please enter valid operations!" << endl;
		return 0;
	}
}

int solve(){

	int x = 0;
	for (int row = 0; row < SIZE; ++row)
	{
		for (int col = 0; col < SIZE; ++col)
		{
			if(isdigit(emptyField[row][col]))
			{
				x = countFoundBox(emptyField, row, col, '-')
				  + countFoundBox(emptyField, row, col, '*');
				if (emptyField[row][col] - '0' == x)
				{
					reverseBoxToFlag(row, col);
				}
				if(emptyField[row][col] - '0' ==
					 countFoundBox(emptyField, row, col, '*'))
				{
					openBox(row, col);
				}
			}
		}
	}
	return 0;
}

int countFoundBox(char **field, int row, int col, char found) {

	int say = 0;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE)
			{
				continue;
			}
			if(field[row+i][col+j] == found)	say++;
		}
	}
	return say;
}

void reverseBoxToFlag(int row, int col) {

	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if(row+i < 0 || row+i >= SIZE || col+j < 0 || col+j >= SIZE)
			{
				continue;
			}
			if(emptyField[row+i][col+j] == '-')
			{
				emptyField[row+i][col+j] = '*';
			}
		}
	}
}	

int countFoundBoxFromField(char **field, char found) {

	int say = 0;
	for (int row = 0; row < SIZE; ++row)
	{
		for (int col = 0; col < SIZE; ++col)
		{
			if (field[row][col] == found)
			{	
				say++;
			}
		}
	}
	return say;
}

void winner() {

	finishGame();
	cout << endl << "\n\t\tYOU ARE WINNER!" << endl;
	print_field(emptyField);
	cout << endl << "\n\t\tYOU ARE WINNER!" << endl;
}

void loser() {
	cout << endl << endl <<	 "\t\tGAME OVER!" << endl;
	print_field(emptyField);
	cout << endl <<	 "\t\tGAME OVER!" << endl;
}

void finishGame() {

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if(minesField[i][j] == 'X')	emptyField[i][j]='X';
		}
	}
}
