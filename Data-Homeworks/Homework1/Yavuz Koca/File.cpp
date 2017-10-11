/* @Author
* Student Name: Yavuz Koca
* Student ID : 150150043
* Date: 10.10.2017
*/
#include "File.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
//#include <string.h>

using namespace std;

void File::openFiles(){
    puzzle = fopen("puzzle.txt","r+");
    if(!puzzle){
        cout << "Couldn't open one or both of the files" << endl;
        exit(1);
    }
}

void File::storePuzzle(char** puzzleArray) {
    int i=0,j=0;
    while (!feof(puzzle)) {
        fscanf(puzzle,"%c ",(*(puzzleArray+i)+j));
        if(i==15)
            i=0;
        j++;
        if(j==15){
            j=0;
            i++;
        }
        if (feof(puzzle)) break;
    }
}

int File::storeWords(searchedWord *wordsArray) {
    ifstream words;
    int i=0,j=0,len;
    int a;
    char *temp,ch = '0',*buffer;
    string line;
    words.open("searchedwords.txt");
    while ( getline (words,line) ) {
        temp = strtok (&line[0]," ");
        while (temp != NULL) {
            if(!j){
                wordsArray[i].id = atoi(temp);
                j = 1;
            }else{
                wordsArray[i].word = new char[strlen(temp)+1];
                strcpy(wordsArray[i].word, temp);
                j = 0;
                wordsArray[i].wordLength = strlen(temp);
            }
            temp = strtok (NULL, " ");
        }
        i++;
    }
    File::foundWordsCnt = i;
    return i;
}

void File::closeFiles() {
    fclose(puzzle);
}

void File::writeResultsToFoundWords(){
    foundWords = fopen("“foundWordsInfo.txt","w");
    if(!foundWords){
        cout << "Couldn't open one or both of the files" << endl;
        exit(1);
    }
}

void File::sortWords(searchedWord *wordsArray){ // Sorting words by their indices
    int temp,cnt;
    char tmp[50];
    for(int i=0; i<File::foundWordsCnt; i++){
        for(int j=i+1; j<File::foundWordsCnt; j++){
            if((wordsArray+i)->id > (wordsArray+j)->id){
                temp = (wordsArray+i)->id;
                (wordsArray+i)->id = (wordsArray+j)->id;
                (wordsArray+j)->id = temp;

                strcpy(tmp,(wordsArray+i)->word);
                strcpy((wordsArray+i)->word,(wordsArray+j)->word);
                strcpy((wordsArray+j)->word,tmp);

                cnt = (wordsArray+i)->wordLength;
                (wordsArray+i)->wordLength = (wordsArray+j)->wordLength;
                (wordsArray+j)->wordLength = cnt;
            }
        }
    }
}