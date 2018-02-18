#ifndef PRINT_H
#define PRINT_H

#include <string>

using namespace std;

void writeFoundWord(char* word, string direction, int rowbeg, int rowend, int colbeg, int colend);
void erasePuzzle(char **puzzleArray);

#endif