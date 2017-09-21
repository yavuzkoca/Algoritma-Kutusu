#include <stdio.h>
#include <stdlib.h>

int *read_sudoku(const char* filename){
    FILE *fp = fopen(filename, "r");
    int *sudoku = (int *)malloc(sizeof(int)* 81);
    for (int i = 0; i < 81; ++i)
        fscanf(fp, "%d", sudoku + i);
    return sudoku;
}

bool sudokuChecker(int sudoku[9][9]){
    for (int i = 0; i < 9; ++i){
        bool line[9];
        for (int j = 0; j < 9; ++j) line[j] = false;
        for (int j = 0; j < 9; ++j)
            line[sudoku[i][j] - 1] = true;
        for (int j = 0; j < 9; ++j){
            if (line[j] == false){
                return false;
            }
        }
    }
    for (int i = 0; i < 9; ++i){
        bool line[9];
        for (int j = 0; j < 9; ++j) line[j] = false;
        for (int j = 0; j < 9; ++j)
            line[sudoku[j][i] - 1] = true;
        for (int j = 0; j < 9; ++j){
            if (line[j] == false){
                return false;
            }
        }
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            bool sqr[9];
            for (int z = 0; z < 9; ++z) sqr[z] = false;
            for (int lil_i = 0; lil_i < 3; ++lil_i){
                for (int lil_j = 0; lil_j < 3; ++lil_j){
                    sqr[sudoku[i * 3 + lil_i][j * 3 + lil_j] - 1] = true;
                }
            }
            for (int z = 0; z < 9; ++z){
                if (sqr[j] == false){
                    return false;
                }
            }
        }
    }

    return true;
}

int main(){
    const char* filename = "sudoku3.txt";
    int *sudoku_raw = read_sudoku(filename);
    int sudoku[9][9];
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j)
            sudoku[i][j] = *(sudoku_raw + i * 9 + j);
    }
    if (sudokuChecker(sudoku)){
        printf("The sudoku #");
        printf("%c", filename[6]);
        printf(" is VALID\n");
    }
    else{
        printf("The sudoku #");
        printf("%c", filename[6]);
        printf(" is INVALID\n");
    }
    getchar();
}
