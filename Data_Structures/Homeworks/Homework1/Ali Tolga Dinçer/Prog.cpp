/* @Author
 * Student Name: Ali Tolga Dinçer
 * Student ID : 150150730
 * Date: 1.10.2017
 */

/* 
Before you start reading, I want to state that [] operators are 
only used for converting strings to char arrays. 
*/

#include <fstream>
#include <iostream>
#include <string>
#include "Word.h"
#include "Search.h"
#include "Print.h"

using namespace std;

void selectionSort(searchedWord *arr, int n) // Selection sort for sorting the words by id.
{
	searchedWord temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if ((arr+j)->id < (arr+i)->id) // Sorting the words by their id.
			{
				temp = *(arr + i);
				*(arr + i) = *(arr + j);
				*(arr + j) = temp;
			}
		}
	}
}

int main()
{
	ifstream myfile;
	string temp;
	int size = 15;

	myfile.open("puzzle.txt");
	char **puzzleArray = new char*[size];
	for (int i = 0; i < size; i++)  // Creating the puzzle matrix.
	{
		*(puzzleArray + i) = new char[size];
	}

	for (int i = 0; i < size; i++)  // Initializing the puzzle by reading from the file..
	{
		for (int j = 0; j < size; j++)
		{
			myfile >> *(*(puzzleArray+i)+j);
		}
	}
	myfile.close();


	searchedWord *list;
	list = new searchedWord[size]; // Creating the array for the words to be searched.

	int count, i = 0, wordcount = 0; // a temp variable, an index and the number of the words.
	myfile.open("searchedwords.txt");
	while (true)
	{
		myfile >> count;
		if (myfile.eof()) 
		{
			break;
		}
		(list + i)->id = count; // Reading and setting the id.

		myfile >> temp; // Reading the word as a string.
		
		(list + i)->word = new char[temp.length()+1];
		for (unsigned int j = 0; j < (temp.length()); j++)
		{
			((list + i)->word)[j] = temp[j]; // Converting the string to a char array.
		}
		((list + i)->word)[temp.length()] = '\0'; // Putting the null character to the end.
		(list + i)->wordLength = temp.length();
		wordcount++;
		i++;
	}

	selectionSort(list, wordcount); // Sorting the words in case, the id's are not sorted.
	
	bool result;
	for (int i = 0; i < wordcount; i++) // Searching for the words.
	{
		result = verticalSearch(puzzleArray, (list + i));
		if (result == true) continue;
		result = horizontalSearch(puzzleArray, (list + i));
		if (result == true) continue;
		result = diagonalSearch(puzzleArray, (list+i));
		if (result == true) continue;
	}

	erasePuzzle(puzzleArray); // Erasing the words in the puzzle

	for (int i = 0; i < size; i++)
	{
		delete[] * (puzzleArray + i);
	}
	delete[] puzzleArray;


	
	return 0;
}