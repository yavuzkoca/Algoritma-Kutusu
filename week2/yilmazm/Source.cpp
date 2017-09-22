#include <iostream>

using namespace std;

bool sudokuChecker(int sudoku[9][9]);
bool scanSudoku(int sudoku[9][9], char *dosyaAdi);
bool printSudoku(int sudoku[9][9]);

int main()
{
	int sudoku[9][9];
	char sudokuAdi[15];
	
	for (int i = 1; i < 4; ++i)
	{
		sprintf(sudokuAdi, "sudoku%d.txt", i);
		scanSudoku(sudoku, sudokuAdi);
		printSudoku(sudoku);

		if (sudokuChecker(sudoku) == 0) {
			cout << "The sudoku #" << i << " is INVALID" << endl;
		}
		else {
			cout << "The sudoku #" << i << " is VALID" << endl;
		}

		cout << endl;
	}

	getchar();

	return EXIT_SUCCESS;	
}

bool scanSudoku(int sudoku[9][9], char *dosyaAdi)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = 0;
		}
	}
	FILE *dg_sudoku;
	dg_sudoku = fopen(dosyaAdi, "r");
	if (dg_sudoku == NULL){
		cout << "Error1" << endl;
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fscanf(dg_sudoku, "%d", &sudoku[i][j]);
		}
	}
	fclose(dg_sudoku);

	return EXIT_SUCCESS;
}

bool printSudoku(int sudoku[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << sudoku[i][j] << " ";
		}
		cout << endl;
	}

	return EXIT_SUCCESS;
}

bool sudokuChecker(int sudoku[9][9])
{
	if (sudoku[8][8] == 0){
		cout << "Boş kutu var" << endl;
		return EXIT_FAILURE;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int t = j+1; t < 9; t++)
			{
				if (j == t) continue;
				if (sudoku[i][j] == sudoku[i][t]) {
					cout << "i-j-t konumu -> " << i << j << t << endl;
					return EXIT_FAILURE;
				}
			}
		}
	}




	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int t = i+1; t < 9; t++)
			{
				if (i == t) continue;
				if (sudoku[i][j] == sudoku[t][j]) {
					cout << "i-j-t konumu -> " << i << j << t << endl;
					return EXIT_FAILURE;
				}
			}
		}
	}






	for (int q = 0; q < 3; q++)
	{
		for (int w = 0; w < 3; w++)
		{
			int temp[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

			for (int a = 0; a < 3; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					temp[a][b] = sudoku[q*3+a][w*3+b];
				}
			}

			for (int a = 0; a < 3; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					for (int c = 0; c < 3; c++)
					{
						for (int d = 0; d < 3; d++)
						{
							if (a == c && b == d) continue;
							if (temp[a][b] == temp[c][d])
							{
								cout << "q-w-a-b-c-d konumu -> " << q + 1 << w + 1 << a + 1 << b + 1 << c + 1 << d + 1 << endl;
								return EXIT_FAILURE;
							}
						}
						
					}
				}
			}
		}
		
	}
	
	return 1;
}