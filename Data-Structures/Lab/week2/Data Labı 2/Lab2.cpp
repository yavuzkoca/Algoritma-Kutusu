#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int checkbox(int sudoku[9][9], int row, int col) {

	for (int i = row; i < (row+3); i++)
	{
		for (int j = col; j < (col+3); j++)
		{
			for (int k = row; k < (row + 3); k++)
			{
				for (int l = col; l < (col + 3); l++)
				{
					if (sudoku[i][j] == sudoku[k][l] && (i != k && j != l))
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool sudokuchecker(int sudoku[9][9]){

	for (size_t i = 0; i < 9; i+=3)
	{
		for (size_t j = 0; j < 9; j+=3)
		{
			if (checkbox(sudoku, i, j) == false) 
			{
				return false;
			}
		}
	}

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			for (size_t k = j+1; k < 9; k++)
			{
				if (sudoku[i][j] == sudoku[i][k]) 
				{
					return false;
				}
			}
		}
	}

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			for (size_t k = j + 1; k < 9; k++)
			{
				if (sudoku[j][i] == sudoku[k][i])
				{
					return false;
				}
			}
		}
	}

	return true;
}

int main() {

	int sudoku[9][9];
	FILE *fp;
	fp = fopen("sudoku1.txt", "r");

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			fscanf(fp, "%d", &sudoku[i][j]);
		}
	}

	/*
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			cout << sudoku[i][j];
			cout << " ";
		}
		cout << endl;
	}
	*/

	bool valid;
	valid = sudokuchecker(sudoku);
	if (valid) 
	{
		cout << "The sudoku #1 is VALID";
	}
	else 
	{	
		cout << "The sudoku #1 is INVALID";
	}
	fclose(fp);
	free(fp);

	//system("PAUSE");
	return 0;
}







