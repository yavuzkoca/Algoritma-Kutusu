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
void readInput(char*);

int main(){
	for (i = 0; i < 9 ; i++)
		for (j = 0; j < 9 ; j++)
			cin >> arr[i][j];


	if (sudokuChecker(arr))
		cout << "Valid";
	else
		cout << "Not Valid";
	
	cin >> last;
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
				cout << i << " " << j << endl;
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
			cout << i << " " << j << endl;
			return false;
		}
		for (int m = 0; m < 10; m++)
			visited[m] = false;
	}
	return true;
}

void readInput(char *filename){
	FILE *sudoku;
	sudoku = fopen(filename, "r");
}
