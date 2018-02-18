#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search.h"
#include "word.h"

#define PUZZLE_ROW_NUMBER 15 // Number of rows in the puzzle matrix
#define PUZZLE_COL_NUMBER 15 // Number of columns in the puzzle matrix

typedef foundHolder Holder;

bool verticalSearch(char **puzzleArray, searchedWord *word){ // If found word vertically return true
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i){
		for(int j = 0; j < PUZZLE_COL_NUMBER; ++j){
			if(southSearch(puzzleArray, word, j, i) || northSearch(puzzleArray, word, j, i)){
				return true;
			}
		}
	}
	return false;
}

bool horizontalSearch(char **puzzleArray, searchedWord *word){ // If found word horizontally return true
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i){
		for(int j = 0; j < PUZZLE_COL_NUMBER; ++j){
			if(eastSearch(puzzleArray, word, j, i) || westSearch(puzzleArray, word, j, i)){
				return true;
			}
		}
	}
	return false;
}

bool diagonalSearch(char **puzzleArray, searchedWord *word){ // If found word diagonally return true
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i){
		for(int j = 0; j < PUZZLE_COL_NUMBER; ++j){
			if(northeastSearch(puzzleArray, word, j, i) ||
				    southeastSearch(puzzleArray, word, j, i) ||
				    northwestSearch(puzzleArray, word, j, i) ||
				    southwestSearch(puzzleArray, word, j, i)){
				return true;
			}
		}
	}
	return false;
}

Holder verticalSearchIndex(char **puzzleArray, searchedWord *word){ // Just like the boolean version but returns index
	Holder pointer; // To hold the found word with coordinates and lenght
	pointer.direction = -1;
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i){
		for(int j = 0; j < PUZZLE_COL_NUMBER; ++j){
			if(southSearch(puzzleArray, word, j, i)){
				pointer.direction = 4;
				pointer.x_1 = j;
				pointer.y_1 = i;
				pointer.x_2 = j;
				pointer.y_2 = i + word->wordLength - 1;
				pointer.len = word->wordLength;
				pointer.id = word->id;
			}
			else if(northSearch(puzzleArray, word, j, i)){
				pointer.direction = 0;
				pointer.x_1 = j;
				pointer.y_1 = i;
				pointer.x_2 = j;
				pointer.y_2 = i - word->wordLength + 1;
				pointer.len = word->wordLength;
				pointer.id = word->id;
			}
		}
	}
	return pointer;
}

Holder horizontalSearchIndex(char **puzzleArray, searchedWord *word){ // Just like the boolean version but returns index
	Holder pointer; // To hold the found word with coordinates and lenght
	pointer.direction = -1;
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i){
		for(int j = 0; j < PUZZLE_COL_NUMBER; ++j){
			if(eastSearch(puzzleArray, word, j, i)){
				pointer.direction = 2;
				pointer.x_1 = j;
				pointer.y_1 = i;
				pointer.x_2 = j + word->wordLength - 1;
				pointer.y_2 = i;
				pointer.len = word->wordLength;
				pointer.id = word->id;
			}
			else if(westSearch(puzzleArray, word, j, i)){
				pointer.direction = 6;
				pointer.x_1 = j;
				pointer.y_1 = i;
				pointer.x_2 = j - word->wordLength + 1;
				pointer.y_2 = i;
				pointer.len = word->wordLength;
				pointer.id = word->id;
			}
		}
	}
	return pointer;
}

Holder diagonalSearchIndex(char **puzzleArray, searchedWord *word){ // Just like the boolean version but returns index
	Holder pointer; // To hold the found word with coordinates and lenght
	pointer.direction = -1;
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i){
		for(int j = 0; j < PUZZLE_COL_NUMBER; ++j){
			if(northeastSearch(puzzleArray, word, j, i)){
				pointer.direction = 1;
				pointer.x_1 = j;
				pointer.y_1 = i;
				pointer.x_2 = j + word->wordLength - 1;
				pointer.y_2 = i - word->wordLength + 1;
				pointer.len = word->wordLength;
				pointer.id = word->id;
			}
			else if(southeastSearch(puzzleArray, word, j, i)){
				pointer.direction = 3;
				pointer.x_1 = j;
				pointer.y_1 = i;
				pointer.x_2 = j + word->wordLength - 1;
				pointer.y_2 = i + word->wordLength - 1;
				pointer.len = word->wordLength;
				pointer.id = word->id;
			}
			else if(southwestSearch(puzzleArray, word, j, i)){
				pointer.direction = 5;
				pointer.x_1 = j;
				pointer.y_1 = i;
				pointer.x_2 = j - word->wordLength + 1;
				pointer.y_2 = i + word->wordLength - 1;
				pointer.len = word->wordLength;
				pointer.id = word->id;
			}
			else if(northwestSearch(puzzleArray, word, j, i)){
				pointer.direction = 7;
				pointer.x_1 = j;
				pointer.y_1 = i;
				pointer.x_2 = j - word->wordLength + 1;
				pointer.y_2 = i - word->wordLength + 1;
				pointer.len = word->wordLength;
				pointer.id = word->id;
			}
		}
	}
	return pointer;
}

bool northSearch(char **puzzleArray, searchedWord *word, int x, int y){ // Searchs words to north (RECURSIVE)
	if(y < 0) return false; // If exceed the coordinates of the array
	if( *(*(puzzleArray + y) + x) != *(word->word) ) return false; // If the characters won't match
	if(word->wordLength == 1) return true; // If the word lenght is 1 then every char matched so return true
	searchedWord *less_word = new searchedWord; // Create a new word to send first char deleted word to recurse
	less_word->word = (char *)malloc(sizeof(char) * (word->wordLength - 1)); // Allocate memory for less_word->word
	less_word->wordLength = word->wordLength - 1;
	strcpy(less_word->word, word->word + 1); // Copy the word after the first element
	bool return_value = northSearch(puzzleArray, less_word, x, y - 1); // This would actually be return directly
	free(less_word->word); // free the allocate memory for word
	delete less_word; // But I need to free the less word
	return return_value; // Now return
}

bool northeastSearch(char **puzzleArray, searchedWord *word, int x, int y){ // Searchs words to northeast (RECURSIVE)
	if(y < 0 || x >= PUZZLE_COL_NUMBER) return false; // If exceed the coordinates of the array
	if( *(*(puzzleArray + y) + x) != *(word->word) ) return false; // If the characters won't match
	if(word->wordLength == 1) return true; // If the word lenght is 1 then every char matched so return true
	searchedWord *less_word = new searchedWord; // Create a new word to send first char deleted word to recurse
	less_word->word = (char *)malloc(sizeof(char) * (word->wordLength - 1)); // Allocate memory for less_word->word
	less_word->wordLength = word->wordLength - 1;
	strcpy(less_word->word, word->word + 1); // Copy the word after the first element
	bool return_value = northeastSearch(puzzleArray, less_word, x + 1, y - 1); // This would actually be return directly
	free(less_word->word); // free the allocate memory for word
	delete less_word;// But I need to free the less word
	return return_value; // Now return
}

bool eastSearch(char **puzzleArray, searchedWord *word, int x, int y){ // Searchs words to east (RECURSIVE)
	if(x >= PUZZLE_COL_NUMBER) return false; // If exceed the coordinates of the array
	if( *(*(puzzleArray + y) + x) != *(word->word) ) return false; // If the characters won't match
	if(word->wordLength == 1) return true; // If the word lenght is 1 then every char matched so return true
	searchedWord *less_word = new searchedWord; // Create a new word to send first char deleted word to recurse
	less_word->word = (char *)malloc(sizeof(char) * (word->wordLength - 1)); // Allocate memory for less_word->word
	less_word->wordLength = word->wordLength - 1;
	strcpy(less_word->word, word->word + 1); // Copy the word after the first element
	bool return_value = eastSearch(puzzleArray, less_word, x + 1, y); // This would actually be return directly
	free(less_word->word); // free the allocate memory for word
	delete less_word;// But I need to free the less word
	return return_value; // Now return
}

bool southeastSearch(char **puzzleArray, searchedWord *word, int x, int y){ // Searchs words to southeast (RECURSIVE)
	if(y >= PUZZLE_ROW_NUMBER || x >= PUZZLE_COL_NUMBER) return false; // If exceed the coordinates of the array
	if( *(*(puzzleArray + y) + x) != *(word->word) ) return false; // If the characters won't match
	if(word->wordLength == 1) return true; // If the word lenght is 1 then every char matched so return true
	searchedWord *less_word = new searchedWord; // Create a new word to send first char deleted word to recurse
	less_word->word = (char *)malloc(sizeof(char) * (word->wordLength - 1)); // Allocate memory for less_word->word
	less_word->wordLength = word->wordLength - 1;
	strcpy(less_word->word, word->word + 1); // Copy the word after the first element
	bool return_value = southeastSearch(puzzleArray, less_word, x + 1, y + 1); // This would actually be return directly
	free(less_word->word); // free the allocate memory for word
	delete less_word;// But I need to free the less word
	return return_value; // Now return
}

bool southSearch(char **puzzleArray, searchedWord *word, int x, int y){ // Searchs words to south (RECURSIVE)
	if(y >= PUZZLE_ROW_NUMBER) return false; // If exceed the coordinates of the array
	if( *(*(puzzleArray + y) + x) != *(word->word) ) return false; // If the characters won't match
	if(word->wordLength == 1) return true; // If the word lenght is 1 then every char matched so return true
	searchedWord *less_word = new searchedWord; // Create a new word to send first char deleted word to recurse
	less_word->word = (char *)malloc(sizeof(char) * (word->wordLength - 1)); // Allocate memory for less_word->word
	less_word->wordLength = word->wordLength - 1;
	strcpy(less_word->word, word->word + 1); // Copy the word after the first element
	bool return_value = southSearch(puzzleArray, less_word, x, y + 1); // This would actually be return directly
	free(less_word->word); // free the allocate memory for word
	delete less_word;// But I need to free the less word
	return return_value; // Now return
}

bool southwestSearch(char **puzzleArray, searchedWord *word, int x, int y){ // Searchs words to southwest (RECURSIVE)
	if(y >= PUZZLE_ROW_NUMBER || x < 0) return false; // If exceed the coordinates of the array
	if( *(*(puzzleArray + y) + x) != *(word->word) ) return false; // If the characters won't match
	if(word->wordLength == 1) return true; // If the word lenght is 1 then every char matched so return true
	searchedWord *less_word = new searchedWord; // Create a new word to send first char deleted word to recurse
	less_word->word = (char *)malloc(sizeof(char) * (word->wordLength - 1)); // Allocate memory for less_word->word
	less_word->wordLength = word->wordLength - 1;
	strcpy(less_word->word, word->word + 1); // Copy the word after the first element
	bool return_value = southwestSearch(puzzleArray, less_word, x - 1, y + 1); // This would actually be return directly
	free(less_word->word); // free the allocate memory for word
	delete less_word;// But I need to free the less word
	return return_value; // Now return
}

bool westSearch(char **puzzleArray, searchedWord *word, int x, int y){ // Searchs words to west (RECURSIVE)
	if(x < 0) return false; // If exceed the coordinates of the array
	if( *(*(puzzleArray + y) + x) != *(word->word) ) return false; // If the characters won't match
	if(word->wordLength == 1) return true; // If the word lenght is 1 then every char matched so return true
	searchedWord *less_word = new searchedWord; // Create a new word to send first char deleted word to recurse
	less_word->word = (char *)malloc(sizeof(char) * (word->wordLength - 1)); // Allocate memory for less_word->word
	less_word->wordLength = word->wordLength - 1;
	strcpy(less_word->word, word->word + 1); // Copy the word after the first element
	bool return_value = westSearch(puzzleArray, less_word, x - 1, y); // This would actually be return directly
	free(less_word->word); // free the allocate memory for word
	delete less_word;// But I need to free the less word
	return return_value; // Now return
}

bool northwestSearch(char **puzzleArray, searchedWord *word, int x, int y){ // Searchs words to northwest (RECURSIVE)
	if(x < 0 || y < 0) return false; // If exceed the coordinates of the array // If exceed the coordinates of the array
	if( *(*(puzzleArray + y) + x) != *(word->word) ) return false; // If the characters won't match
	if(word->wordLength == 1) return true; // If the word lenght is 1 then every char matched so return true
	searchedWord *less_word = new searchedWord; // Create a new word to send first char deleted word to recurse
	less_word->word = (char *)malloc(sizeof(char) * (word->wordLength - 1)); // Allocate memory for less_word->word
	less_word->wordLength = word->wordLength - 1;
	strcpy(less_word->word, word->word + 1); // Copy the word after the first element
	bool return_value = northwestSearch(puzzleArray, less_word, x - 1, y - 1); // This would actually be return directly
	free(less_word->word); // free the allocate memory for word
	delete less_word;// But I need to free the less word
	return return_value; // Now return
}