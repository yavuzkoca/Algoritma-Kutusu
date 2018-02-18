#ifndef SEARCH_H
#define SEARCH_H

#include "word.h"

struct foundHolder{
	int direction;
	int x_1, y_1, x_2, y_2;
	int len;
	int id;
};

bool verticalSearch(char **, searchedWord *);
bool horizontalSearch(char **, searchedWord *);
bool diagonalSearch(char **, searchedWord *);

foundHolder verticalSearchIndex(char **, searchedWord *);
foundHolder horizontalSearchIndex(char **, searchedWord *);
foundHolder diagonalSearchIndex(char **, searchedWord *);

bool northSearch(char **, searchedWord *, int, int);
bool northeastSearch(char **, searchedWord *, int, int);
bool eastSearch(char **, searchedWord *, int, int);
bool southeastSearch(char **, searchedWord *, int, int);
bool southSearch(char **, searchedWord *, int, int);
bool southwestSearch(char **, searchedWord *, int, int);
bool westSearch(char **, searchedWord *, int, int);
bool northwestSearch(char **, searchedWord *, int, int);

#endif