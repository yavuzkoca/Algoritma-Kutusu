#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include "Word.h"
#include "Print.h"

/*
All functions search all the letters one by one. If a letter matches, they check continously
in their directions to find the other letters. If they can't find the other letters,
they continue to search for the first letter.
*/

bool verticalSearch(char** puzzleArray, searchedWord *word)
{
	int i = 0, j = 0, pos = 0, index = 0, length = 0;
	int rowbeg = 0, rowend = 0, colbeg = 0, colend = 0, find = 0;
	while (j < 15)
	{
		if (*((*(puzzleArray + i)) + j) == *((word->word) + index)) // If a matching letter is found.
		{
			if (find == 0) 
			{
				rowbeg = i;  // Keep the beginning pos. of the word.
				colbeg = j;
				find = 1;
			}

			length++;
			if (length == strlen(word->word)) // If the word is found.
			{
				rowend = i; // Keep the ending pos. of the word.
				colend = j;
				writeFoundWord(word->word, "VERTICAL", rowbeg, rowend, colbeg, colend); // Write to file.
				return true;
			}

			if (i + 1 <= 14 && *((*(puzzleArray + i + 1)) + j) == *((word->word) + index + 1))
			{
				i++;
				index++;
				continue;
			}

			if (i - 1 >= 0 && *((*(puzzleArray + i - 1)) + j) == *((word->word) + index + 1) )
			{
				i--;
				index++;
				continue;
			}
		}

		if (length != 0)
		{
			length = 0;
			index = 0;
			find = 0;
		}

		pos++;
		i = pos;
		if (pos == 15)
		{
			pos = 0;
			i = pos;
			j++;
		}

	}
	return false;
}

bool horizontalSearch(char** puzzleArray, searchedWord *word)
{
	int i = 0, j = 0, pos = 0, index = 0, length = 0;
	int rowbeg=0, rowend = 0, colbeg = 0, colend = 0, find=0;
	while (i < 15) 
	{
		if (*((*(puzzleArray + i)) + j) == *((word->word) + index)) // If a matching letter is found.
		{
			if (find == 0) 
			{
				rowbeg = i;  // Keep the beginning pos. of the word.
				colbeg = j;
				find = 1;
			}

			length++;
			if (length == strlen(word->word)) // If the word is found.
			{
				rowend = i; // Keep the ending pos. of the word.
				colend = j;
				writeFoundWord(word->word, "HORIZONTAL", rowbeg, rowend, colbeg, colend); // Write to file.
				return true;
			}

			if (j + 1 <= 14 && *((*(puzzleArray + i)) + j + 1) == *((word->word) + index + 1))
			{
				j++;
				index++;
				continue;
			}

			if (j - 1 >= 0 && *((*(puzzleArray + i)) + j - 1) == *((word->word) + index + 1))
			{
				j--;
				index++;
				continue;
			}
		}

		if (length != 0)
		{
			length = 0;
			index = 0;
			find = 0;
		}

		pos++;
		j = pos;
		if (pos == 15)
		{
			pos = 0;
			j = pos;
			i++;
		}

	}
	return false;
}

bool diagonalSearch(char** puzzleArray, searchedWord *word)
{
	int i = 0, j = 0, posx = 0, posy = 0, index = 0, length = 0;
	int rowbeg = 0, rowend = 0, colbeg = 0, colend = 0, find = 0;
	while (i < 15)
	{
		if (*((*(puzzleArray + i)) + j) == *((word->word) + index)) // If a matching letter is found.
		{
			if (find == 0)
			{
				rowbeg = i;  // Keep the beginning pos. of the word.
				colbeg = j;
				find = 1;
			}

			length++;
			if (length == strlen(word->word)) // If the word is found.
			{
				rowend = i; // Keep the ending pos. of the word.
				colend = j;
				writeFoundWord(word->word, "DIAGONAL", rowbeg, rowend, colbeg, colend); // Write to file.
				return true;
			}

			if (i + 1 <= 14 && j + 1 <= 14 && *((*(puzzleArray + i + 1)) + j + 1) == *((word->word) + index + 1))
			{ // If the word goes from top left to down right.
				i++;
				j++;
				index++;
				continue;
			}

			if (i + 1 <= 14 && j - 1 >= 0 && *((*(puzzleArray + i + 1)) + j - 1) == *((word->word) + index + 1))
			{ // If the word goes from top right to down left.
				i++;
				j--;
				index++;
				continue;
			}

			if (i - 1 >= 0 && j + 1 <= 14 && *((*(puzzleArray + i - 1)) + j + 1) == *((word->word) + index + 1))
			{ // If the word goes from down left to up right.
				i--;
				j++;
				index++;
				continue;
			}

			if (i - 1 >= 0 && j - 1 >= 0 && *((*(puzzleArray + i - 1)) + j - 1) == *((word->word) + index + 1))
			{ // If the word goes from down right to up left.
				i--;
				j--;
				index++;
				continue;
			}

		}

		if (length != 0)
		{
			length = 0;
			index = 0;
			find = 0;
			i = posx;
		}

		posy++;
		j = posy;
		if (posy == 15)
		{
			posy = 0;
			j = posy;
			posx++;
			i = posx;
		}

	}
	return false;
}

