#include <iostream>
#include <cstdio>
using namespace std;
int arr[9][9];
int i,j,k,l;
char last;

bool checkEachCell();
bool visited[10];
bool sudokuChecker(int arr[9][9]);
bool checkRow();
bool checkCol();
int openFile(char*);
void readInput();

int main(){
	char s[50];

	printf("Enter the name of the file you want to read.\n");
	scanf("%s",s);
	if(!openFile(s)){
		printf("Couldnt open file\n");
		return 1;
	}

	if (sudokuChecker(arr))
		printf("The sudoku that you entered is VALID\n");
	else
        printf("The sudoku that you entered is INVALID\n");

	return 0;
}


bool checkEachCell(){
	for (i = 0; i < 9; i+=3)
		for (j = 0; j < 9; j += 3)
			for (k = i; k < i + 3; k++){
				for (l = j; l < j + 3; l++)
					if (visited[arr[k][l]] == false)
						visited[arr[k][l]] = true;
					else
						return false;
				
				for (int m = 0; m < 10; m++)
					visited[m] = false;
			}

	return true;
}

bool sudokuChecker(int arr[9][9]){
	if (checkEachCell() && checkRow() && checkCol())
		return true;
	
	return false;
}

bool checkRow(){
	for (i = 0; i < 9; i++){
		for (j = 0; j < 9; j++)
			if (visited[arr[i][j]]==false)
				visited[arr[i][j]] = true;
			else{ 
				//cout << i << " " << j << endl;
				return false;
			}
		for (int m = 0; m < 10; m++)
			visited[m] = false;
	}
	return true;
}

bool checkCol(){
	for (i = 0; i < 9; i++){
		for (j = 0; j < 9; j++)
		if (visited[arr[j][i]] == false)
			visited[arr[j][i]] = true;
		else{
			//cout << i << " " << j << endl;
			return false;
		}
		for (int m = 0; m < 10; m++)
			visited[m] = false;
	}
	return true;
}

int openFile(char *filename){
	FILE *sudoku;
	sudoku = fopen(filename, "r");
	if(!sudoku){
		return false;
	}
    int i=0,j=0;
    while (!feof(sudoku)) {
        //fread(&k, sizeof(Tel_Kayit), 1, sudoku);
        fscanf(sudoku,"%d",&arr[i][j]);
        if(i==9) i=0;
        j++;
        if(j==9){
            j=0;
            i++;
        }
        if (feof(sudoku)) break;
    }
    fclose(sudoku);
    return true;
}
