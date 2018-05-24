/* @Author
* Student Name: Yavuz Koca
* Student ID : 150150043
* Date: 10.10.2017
*/
#include <iostream>
#include <cstring>
#include "File.h"
#include "searchedWord.h"

using namespace std;
File File;
typedef searchedWord Word;
Word wordsArray[100];

char** puzzleArray;
char** newPuzzleArray;
void storeInArray();
void createDynamicArray();
void deleteDynamicArray();
void printPuzzle();
void printSearchedWord();
bool verticalSearch (char** puzzleArray, searchedWord* word);
void writeToFoundWordsInfoV(int, string, string, int, int, int);
bool horizontalSearch (char** puzzleArray, searchedWord* word);
void writeToFoundWordsInfoH(int, string, string, int, int, int);
bool diagonalSearch(char** puzzleArray, searchedWord* word);
void writeToFoundWordsInfoD(int, string, string, int, int, int, int);
void writeResultsToFoundWords();
void writeNewPuzzle();
void copyArray();

int numberOfWords;
FILE *foundWords;
FILE *newPuzzle;

int main(){
    File.openFiles(); // Open txt files
    createDynamicArray(); // Create necessary arrays
    storeInArray(); // Store txt files in arrays

    writeResultsToFoundWords(); // For all words, search in array and write to foundWordsInfo.txt if have found
    writeNewPuzzle();

    deleteDynamicArray();
    File.closeFiles();
    return 0;
}

void storeInArray(){
    File.storePuzzle(puzzleArray); // Store puzzle and words
    numberOfWords = File.storeWords(wordsArray); // Getting # of words
    File.sortWords(wordsArray); // Sorting target words with respect to their index numbers
    copyArray(); // Copying puzzle into another one
}

void createDynamicArray(){
    puzzleArray = new char*[15];
    for(int i=0; i<15; i++)
        *(puzzleArray+i) = new char[15];
    newPuzzleArray = new char*[15];
    for(int i=0; i<15; i++)
        *(newPuzzleArray+i) = new char[15];
}

void deleteDynamicArray(){
    for(int i=0; i<15; i++)
        delete[] *(puzzleArray+i);
    delete[] puzzleArray;

    for(int i=0; i<15; i++)
        delete[] *(newPuzzleArray+i);
    delete[] newPuzzleArray;

    for(int i=0; i<wordsArray[i].wordLength; i++)
        delete[] wordsArray[i].word;
}

void printPuzzle(){
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++)
            //puzzleArray[i][j] = '1';
            cout << puzzleArray[i][j] << " ";
        cout << endl;
    }
}

void printSearchedWord(){
    for(int i=0; i<wordsArray[i].wordLength; i++)
        cout << wordsArray[i].word << endl;
}

bool verticalSearch (char** puzzleArray, searchedWord* word){
    int len = word->wordLength,cnt = 0;

    // First search from up to down
    for(int i=0; i<15; i++)
        for(int j=0; j<15; j++)
            for(int k=j; k<15; k++){
                if(*(*(puzzleArray+k)+i) == word->word[cnt])
                    cnt++;
                else{
                    cnt = 0;
                    break;
                }
                if(cnt == len-1){ // If word has found, write the indices to txt file and put blank characters
                    writeToFoundWordsInfoV(len-1,word->word,"VERTICAL",k+2-len,i,k);
                    for(int l=j; l<j+len-1; l++){
                        *(*(newPuzzleArray+l)+i) = ' ';
                    }
                    return 1;
                }
            }

    cnt = 0;
    // Then search from down to up
    for(int i=0; i<15; i++)
        for(int j=14; j>=0; j--)
            for(int k=j; k>=0; k--){
                if(*(*(puzzleArray+k)+i) == word->word[cnt]){
                    cnt++;
                }
                else{
                    cnt = 0;
                    break;
                }

                if(cnt == len-1){ // If word has found, write the indices to txt file and put blank characters
                    writeToFoundWordsInfoV(len-1,word->word, "VERTICAL", k-2+len, i,k);
                    for(int l=j; l>j-len+1; l--){
                        *(*(newPuzzleArray+l)+i) = ' ';
                    }
                    return 1;
                }

            }



    return 0;
}

void writeToFoundWordsInfoV(int len,string word, string direction, int beg, int i, int end){
    for(int j=0; j<len; j++)
        fprintf(foundWords,"%c",word[j]);
    fprintf(foundWords," %s [%d][%d] - [%d][%d]\n",direction.c_str(),beg,i,end,i);

}

bool horizontalSearch (char** puzzleArray, searchedWord* word){
    int len = word->wordLength,cnt = 0;
    // Search from left to right
    for(int i=0; i<15; i++)
        for(int j=0; j<15; j++)
            for(int k=j; k<15; k++){
                if(*(*(puzzleArray+i)+k) == word->word[cnt])
                    cnt++;
                else{
                    cnt = 0;
                    break;
                }
                if(cnt == len-1){ // If word has found, write the indices to txt file and put blank characters
                    writeToFoundWordsInfoH(len-1,word->word,"HORIZONTAL",k+2-len,i,k);
                    for(int l=j; l<j+len-1; l++){
                        *(*(newPuzzleArray+i)+l) = ' ';
                    }
                    return 1;
                }
            }

    cnt = 0;
    // Search from right to left
    for(int i=0; i<15; i++)
        for(int j=14; j>=0; j--)
            for(int k=j; k>=0; k--){
                if(*(*(puzzleArray+i)+k) == word->word[cnt])
                    cnt++;
                else{
                    cnt = 0;
                    break;
                }
                if(cnt == len-1){
                    writeToFoundWordsInfoH(len-1,word->word, "HORIZONTAL", k-2+len, i,k);
                    for(int l=j; l>j-len+1; l--){
                        *(*(newPuzzleArray+i)+l) = ' ';
                    }
                    return 1;
                }

            }
    return 0;
}

void writeToFoundWordsInfoH(int len, string word, string direction, int beg, int i, int end){
    for(int j=0; j<len; j++)
        fprintf(foundWords,"%c",word[j]);
    fprintf(foundWords," %s [%d][%d] - [%d][%d]\n",direction.c_str(),i,beg,i,end);

}

bool diagonalSearch(char** puzzleArray, searchedWord* word){
    int len = word->wordLength;
    int cnt;
    // When I found a character that matches, Im checking four directions which are
    // up-right, up-left, down-left, down-right.
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            cnt = 0;
            if(*(*(puzzleArray+i)+j) == *(word->word+cnt)){
                cnt++;
                // Thats why there is four for loops
                for(int k=1; k<len && i+k < 15 && j+k < 15; k++){
                    if(*(*(puzzleArray+i+k)+j+k) == *(word->word+cnt)){
                        cnt++;
                    }else{
                        cnt = 1;
                        break;
                    }
                    if(cnt == len-1){
                        writeToFoundWordsInfoD(len-1, word->word, "DIAGONAL", i, i+len-2, j, j+len-2);
                        for(int l=0; l<len-1; l++){
                            *(*(newPuzzleArray+i+l)+j+l) = ' ';
                        }
                        return 1;
                    }
                }
                for(int k=1; k<len && i+k < 15 && j-k >= 0; k++){
                    if(*(*(puzzleArray+i+k)+j-k) == *(word->word+cnt)){
                        cnt++;
                    }else{
                        cnt = 1;
                        break;
                    }
                    if(cnt == len-1){
                        writeToFoundWordsInfoD(len-1, word->word, "DIAGONAL", i, i+len-2, j, j+2-len);
                        for(int l=0; l<len-1; l++){
                            *(*(newPuzzleArray+i+l)+j-l) = ' ';
                        }
                        return 1;
                    }
                }
                for(int k=1; k<len && i-k >= 0 && j-k >= 0; k++){
                    if(*(*(puzzleArray+i-k)+j-k) == *(word->word+cnt)){
                        cnt++;
                    }else{
                        cnt = 1;
                        break;
                    }
                    if(cnt == len-1){
                        writeToFoundWordsInfoD(len-1, word->word, "DIAGONAL", i, i-len+2, j, j-len+2);
                        for(int l=0; l<len-1; l++){
                            *(*(newPuzzleArray+i-l)+j-l) = ' ';
                        }
                        return 1;
                    }
                }
                for(int k=1; k<len && i-k >= 0 && j+k < 15; k++){
                    if(*(*(puzzleArray+i-k)+j+k) == *(word->word+cnt)){
                        cnt++;
                    }else{
                        cnt = 1;
                        break;
                    }
                    if(cnt == len-1){
                        writeToFoundWordsInfoD(len-1,word->word, "DIAGONAL", i,i-len+2, j,j+len-2);
                        //printf("%d %d\n",i,j);
                        for(int l=0; l<len-1; l++){
                            *(*(newPuzzleArray+i-l)+j+l) = ' ';
                        }
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void writeToFoundWordsInfoD(int len, string word, string direction, int x1, int x2,int y1, int y2){
    for(int j=0; j<len; j++)
        fprintf(foundWords,"%c",word[j]);
    fprintf(foundWords," %s [%d][%d] - [%d][%d]\n",direction.c_str(),x1,y1,x2,y2);
}

void writeResultsToFoundWords(){
    foundWords = fopen("foundWordsInfo.txt","w");
    for(int i=0; i<numberOfWords; i++) // Trying to find all words in given directions
        if(
           !verticalSearch(puzzleArray,wordsArray+i)
           && !horizontalSearch(puzzleArray,wordsArray+i)
           && !diagonalSearch(puzzleArray,wordsArray+i)
           )
            cout << "";
    fclose(foundWords);
}

void writeNewPuzzle(){
    newPuzzle = fopen("lastVersionPuzzle.txt","w");
    char a = ' ';
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            fprintf(newPuzzle,"%c",*(*(newPuzzleArray+i)+j));
            if(j!=14)
                fprintf(newPuzzle,"%c",a);
            else
                fprintf(newPuzzle,"\n");
        }
    }
    fclose(newPuzzle);
}

void copyArray(){
    for(int i=0; i<15; i++)
        for(int j=0; j<15; j++)
            *(*(newPuzzleArray+i)+j) = *(*(puzzleArray+i)+j);
}


