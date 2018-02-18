/* @Author
* Student Name: Yavuz Koca
* Student ID : 150150043
* Date: 10.10.2017
*/
#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include "searchedWord.h"

class File {
public:
    FILE *puzzle;
    FILE *foundWords;
    int foundWordsCnt;
    //FILE *words;
    void openFiles();
    void closeFiles();
    void storePuzzle(char** puzzleArray);
    int storeWords(searchedWord *);
    void writeResultsToFoundWords();
    void sortWords(searchedWord *);

};
#endif