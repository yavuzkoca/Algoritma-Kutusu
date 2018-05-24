/* @Author
 * Student Name: Vahit Buğra YEŞİLKAYNAK
 * Student ID : 150150019
 * Date: 7 October 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search.h" // Header containing search operations
#include "word.h" // Header containing searchedWord struct

#define PUZZLE_ROW_NUMBER 15 // Number of rows in the puzzle matrix
#define PUZZLE_COL_NUMBER 15 // Number of columns in the puzzle matrix
#define MAX_LENGTH 80 // Max string from the buffer

char **puzzleArray; // double pointer containing the puzzle

typedef searchedWord Word; // use searchedWord as Word
Word *words; // Define a Word pointer to use as an array
int number_of_lines; // The number of lines in searchedwords.txt

typedef foundHolder Holder; // This struct is used to hold 

int max(int x, int y){ // Returns the max of arguments
	if(x > y) return x;
	else return y;
}

int min(int x, int y){ // Returns the min of arguments
	if(x > y) return y;
	else return x;
}

void loadPuzzleArray(const char *PATH){ // Loads the puzzle array from txt file
	FILE *puzzle_ptr = fopen(PATH, "r"); // Open file pointer
	puzzleArray = (char **)malloc(sizeof(char) * PUZZLE_ROW_NUMBER * PUZZLE_COL_NUMBER); // Allocate the whole puzzle array
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i){ // For every row of the puzzle
		*(puzzleArray + i) = (char *)malloc(sizeof(char) * PUZZLE_COL_NUMBER); // Allocate rows
		for(int j = 0; j < PUZZLE_COL_NUMBER; ++j){ // Read the row and assign the chars to columns
			fscanf(puzzle_ptr, "%c ", *(puzzleArray + i) + j);
		}
	}
	fclose(puzzle_ptr); // Close file pointer
}

void loadSearchedWords(const char *PATH){ // Load searchedWords txt file
	FILE *words_ptr = fopen(PATH, "r"); // Open file pointer
	for(number_of_lines = 0; !feof(words_ptr); ++number_of_lines){ // Determine the number of lines
		fscanf(words_ptr, "%*[^\n]\n", NULL);
	}
	rewind(words_ptr); // Return to the beginning of the file
	words = new Word[number_of_lines]; // Create a Word array
	int id, len_word;
	for(int i = 0; i < number_of_lines; ++i){ // For every line of the file
		char *temp_word = (char *)malloc(sizeof(char) * MAX_LENGTH); // Temp word to read the word
		fscanf(words_ptr, "%d %s", &id, temp_word); // From file read the word and the id
		for(len_word = 0; *(temp_word + len_word) != '\0'; ++len_word); // Determine the length of the word
		(words + i)->id = id; // Assign the id
		(words + i)->wordLength = len_word; // Assign the wordLength
		(words + i)->word = (char *)malloc(sizeof(char) * len_word); // Allocate ith Word's word as the size
		strcpy((words + i)->word, temp_word); // Copy the temp_word to the ith Word's word
		free(temp_word); // Free the allocated memory for temp_word
	}

	int temp_id;
	int temp_wordLength;
	char *temp_word;
	for(int i = 1; i < number_of_lines; ++i){ // SORT BY ID (INSERTION SORT)
		for(int j = 0; j < i; ++j){
			if( (words + i)->id < (words + j)->id ){
				temp_word = (char *)malloc(sizeof(char) * MAX_LENGTH);
				temp_id = (words + i)->id;
				temp_wordLength = (words + i)->wordLength;
				strcpy(temp_word, (words + i)->word);
				(words + i)->word = (char *)realloc((words + i)->word, sizeof(char) * (words + j)->wordLength);
				strcpy((words + i)->word, (words + j)->word);
				(words + i)->id = (words + j)->id;
				(words + i)->wordLength = (words + j)->wordLength;
				(words + j)->word = (char *)realloc((words + j)->word, sizeof(char) * temp_wordLength);
				(words + j)->id = temp_id;
				strcpy((words + j)->word, temp_word);
				free(temp_word);
			}
		}
	}

	fclose(words_ptr); // Close the file pointer
}

void deleteMap(Holder *holders, int size_holders){ // This function deletes the found words from the puzzle
	// Holder is a struct to keep the found words, size_holders is the size of holders array
	int direction; // Direction of the ith holder
	int len; // Length of the found word
	int x_1, x_2, y_1, y_2; // Coordinates of the found word
	for(int i = 0; i < size_holders; ++i){ // For every Holder in holders
		x_1 = (holders + i)->x_1;
		y_1 = (holders + i)->y_1;
		x_2 = (holders + i)->x_2;
		y_2 = (holders + i)->y_2;
		direction = (holders + i)->direction;
		len = (holders + i)->len; // Assign the corresponding values

		if( direction == 0 || direction == 4 ){ // If North of South
			for(int j = 0; j < len; ++j)
				*( *(puzzleArray + min(y_1, y_2) + j) + x_1 ) = ' '; // Delete from the min y to max y
		}
		else if(direction == 2 || direction == 6){ // If East of West
			for(int j = 0; j < len; ++j)
				*( *(puzzleArray + y_1) + min(x_1, x_2) + j ) = ' '; // Delete from the min x to max x
		}
		else if(direction == 1 || direction == 5){ // If Northeast or Southwest
			for(int j = 0; j < len; ++j)
				*( *(puzzleArray + min(y_1, y_2) + j) + max(x_1, x_2) - j ) = ' '; // Delete to Southwest
		}
		else if(direction == 3 || direction == 7){ // If Southeast or Northwest
			for(int j = 0; j < len; ++j)
				*( *(puzzleArray + min(y_1, y_2) + j) + min(x_1, x_2) + j ) = ' '; // Delete to Southeast
		}

	}
}

void saveDeletedMap(const char *PATH, Holder *holders, int size_holders){ // Save the deleted map to the according file
	FILE *puzzle_ptr = fopen(PATH, "w"); // Open file pointer
	deleteMap(holders, size_holders); // Delete the words
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i){ // For every row of puzzle
		for(int j = 0; j < PUZZLE_COL_NUMBER; ++j){ // For every column of puzzle
			fprintf(puzzle_ptr, "%c ", *( *(puzzleArray + i) + j )); // Save the according value to file
		}
		fprintf(puzzle_ptr, "\n"); // New line after a row
	}
	fclose(puzzle_ptr); // Close the file
}

void clearMemory(){ // Clear the allocated memories of global variables
	for(int i = 0; i < number_of_lines; ++i)
		free((words + i)->word); // First free the allocated memory for words
	delete[] words; // Then delete the word array
	for(int i = 0; i < PUZZLE_ROW_NUMBER; ++i)
		free(*(puzzleArray + i)); // Free every row of the puzzle
	free(puzzleArray); // Free the whole puzzle array
}

int main(){

	const char *PATH_PUZZLE_FILE = "puzzle.txt";
	const char *PATH_WORDS_FILE = "searchedwords.txt";
	const char *PATH_OUTPUT_WORDS_FILE = "foundWordsInfo.txt";
	const char *PATH_OUTPUT_PUZZLE_FILE = "lastVersionPuzzle.txt";

	loadPuzzleArray(PATH_PUZZLE_FILE);
	loadSearchedWords(PATH_WORDS_FILE);

	int number_of_existing_words = 0;

	
	for(int i = 0; i < number_of_lines; ++i){
		if(verticalSearch(puzzleArray, words + i)){
			//printf("%d. %s is vertical.\n", i + 1, (words + i)->word);
			++number_of_existing_words;
		}
		if(horizontalSearch(puzzleArray, words + i)){
			//printf("%d. %s is horizontal.\n", i + 1, (words + i)->word);
			++number_of_existing_words;
		}
		if(diagonalSearch(puzzleArray, words + i)){
			//printf("%d. %s is diagonal.\n", i + 1, (words + i)->word);
			++number_of_existing_words;
		}
	} // This implementation is maybe not optimal but I did it because I wanted to show that I am using
	// the boolean version of the search functions as they were requested to be implemented in the homework

	Holder *holders = new Holder[number_of_existing_words]; // Holder array to keep the found words

	int existing_word_counter = 0; // This seperate counter is just for the situation if a word occurs two times
								// in other directions, I also handled that situation

	for(int i = 0; i < number_of_lines; ++i){
		Holder holder1 = verticalSearchIndex(puzzleArray, words + i); // Search the word vertically, if not found direction is -1
		Holder holder2 = horizontalSearchIndex(puzzleArray, words + i); // Search the word horizontally, if not found direction is -1
		Holder holder3 = diagonalSearchIndex(puzzleArray, words + i); // Search the word diagonally, if not found direction is -1
		if(holder1.direction != -1){ // If found
			*(holders + existing_word_counter) = holder1; // Add to the holder array
			++existing_word_counter; // Added a word
		}
		if(holder2.direction != -1){ // If found
			*(holders + existing_word_counter) = holder2;  // Add to the holder array
			++existing_word_counter; // Added a word
		}
		if(holder3.direction != -1){ // If found
			*(holders + existing_word_counter) = holder3;  // Add to the holder array
			++existing_word_counter; // Added a word
		}
	}

	FILE *words_ptr = fopen(PATH_OUTPUT_WORDS_FILE, "w"); // Open file pointer to save the words


	for(int i = 0; i < number_of_existing_words; ++i){ // Save words according to the given template
		if((holders + i)->direction == 0 || (holders + i)->direction == 4){
			fprintf(words_ptr, "%s\tVERTICAL\t[%d][%d] - [%d][%d]\n",
				(words + (holders + i)->id - 1)->word,
				(holders + i)->y_1,
				(holders + i)->x_1,
				(holders + i)->y_2,
				(holders + i)->x_2);
		}
		else if((holders + i)->direction == 2 || (holders + i)->direction == 6){
			fprintf(words_ptr, "%s\tHORIZONTAL\t[%d][%d] - [%d][%d]\n",
				(words + (holders + i)->id - 1)->word,
				(holders + i)->y_1,
				(holders + i)->x_1,
				(holders + i)->y_2,
				(holders + i)->x_2);
		}
		else if((holders + i)->direction == 1 || (holders + i)->direction == 3 || (holders + i)->direction == 5 || (holders + i)->direction == 7){
			fprintf(words_ptr, "%s\tDIAGONAL\t[%d][%d] - [%d][%d]\n",
				(words + (holders + i)->id - 1)->word,
				(holders + i)->y_1,
				(holders + i)->x_1,
				(holders + i)->y_2,
				(holders + i)->x_2);
		}
	}

	saveDeletedMap(PATH_OUTPUT_PUZZLE_FILE, holders, existing_word_counter); // Save the map after deleting the words

	fclose(words_ptr); // Close the file pointer
	delete[] holders; // Delete the Holder array
	clearMemory(); // Clear the allocated memories

	return 0;
}