/* @Author
 * Student Name: Muhammed YILMAZ
 * Student ID : 150150149
 * Date: 09.10.2017
 */


/*			UYARI
 *
 * Açıklamalar "/ * * /" içerisinde verilmiştir. 
 * "//" okunmayacak kodlar için kullanılmıştır.
 *
 */

#include "yapilar.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;


bool verticalSearch(char** puzzleArray, searchedWord* word);
bool horizontalSearch(char** puzzleArray, searchedWord* word);
bool diagonalSearch(char** puzzleArray, searchedWord* word);


bool read_puzzle();
void print_puzzle(char** puzzle, FILE *dg);
bool read_words();
void sort_words();
void sync_array();
bool fprint_puzzle();
bool fprint_word(char y, char *word, int a, int b, int c, int d);

void copcu();

int main(int argc, char *argv[]) {
	/* If there is this file, it is removed. Otherwise my functions does only addind */
	remove("foundWordsInfo.txt");	

	read_puzzle();

	read_words(); 
	sort_words();
	
	/* This loop performs operations in loop for all words. */
	sync_array();

	for (int i = 0; i < numberWords; ++i)				
	{
		if(verticalSearch(puzzleArray, &wordsArray[i])==EXIT_SUCCESS){}
		else if(horizontalSearch(puzzleArray, &wordsArray[i])==EXIT_SUCCESS){}
		else if(diagonalSearch(puzzleArray, &wordsArray[i])==EXIT_SUCCESS){}
	}

	fprint_puzzle();
	
	copcu();
	return EXIT_SUCCESS;
}

bool read_puzzle(){

	/* Sizing the "**PuzzleArray". */
	puzzleArray = new char*[rows];
	for (int i = 0; i < rows; ++i)
	{
		*(puzzleArray+i) = new char[columns];
	}


	FILE *dgReadPuzzle;
	dgReadPuzzle = fopen("puzzle.txt", "r");
	if (dgReadPuzzle == NULL)
	{
		cout << "puzzle.txt is not found." << endl;
		return EXIT_FAILURE;
	}

	/* Veriler puzzle.txt dosyasından **puzzleArray'a okunuyor. */
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			fscanf(dgReadPuzzle, "%c ",(*(puzzleArray+i)+j) );
		}
	}

	fclose(dgReadPuzzle);

	return EXIT_SUCCESS;
}

void print_puzzle(char** puzzle, FILE *dg){
	
	/* **puzzle *dg'ye yazdırılıyor. */
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			fprintf(dg, "%c ",*(*(puzzle+i)+j) );
		}
		fprintf(dg, "\n");
	}
}

bool read_words(){

	/* Başlangıçta hiç kelime olmadığı için numberWords 0'a eşitleniyor. */
	numberWords=0;

	/* *wordsArray boyutlandırılıyor. */
 //	wordsArray = (searchedWord*) malloc( sizeof(searchedWord) * 1);
	wordsArray = new searchedWord[1]; 

	FILE *dgReadWords;

	dgReadWords = fopen("searchedwords.txt","r");
	if(dgReadWords==NULL)
	{
		cout << "searchedwords.txt okunamadı"<<endl;
		return EXIT_FAILURE;
	}

	for (; !feof(dgReadWords); numberWords++)
	{
		/* wordsArray->word boyutlandırılıyor. */
	 //	wordsArray[numberWords].word = (char*) malloc (sizeof(char) * 15);
		(wordsArray+numberWords)->word = new char[15];

		/* *wordsArray başlangıçta sınırlı sayıda boyutlanmıştı,
		 * eğer daha fazla kelime olursa boyut genişletiliyor.
		 */
		if (numberWords%10==0)
		{
			wordsArray = (searchedWord*) realloc( wordsArray, sizeof(searchedWord) * (numberWords + 11));
		}

		/* Kelimeler searchedwords.txt dosyasından *wordsArray'a okunuyor. */
		fscanf(dgReadWords, "%d %s", &(wordsArray+numberWords)->id, (wordsArray+numberWords)->word);
		
		/* This loop calculates word length */
		for (int j = 0; ; ++j)
		{
			if ((wordsArray+numberWords)->word[j] == '\0')	{(wordsArray+numberWords)->wordLength = j; break;}
		}
	}

	fclose(dgReadWords);
	return EXIT_SUCCESS;
}

/* Okunan kelimeler öncelik sırasına göre sıralanıp ardından arama yapılmıştır. */
void sort_words(){

	for (int i = 0; i < numberWords ; ++i)
	{
		for (int j = 0; j < numberWords-1 ; ++j)
		{
			if((wordsArray+j)->id > (wordsArray+j+1)->id)
			{
				searchedWord temp;
				//temp.word = (char*) malloc(sizeof(char)*15);
				temp.word = new char[15];

				strcpy(temp.word, (wordsArray+j)->word);
				strcpy((wordsArray+j)->word, (wordsArray+j+1)->word);
				strcpy((wordsArray+j+1)->word, temp.word);

				temp.id = (wordsArray+j)->id;
				(wordsArray+j)->id = (wordsArray+j+1)->id;
				(wordsArray+j+1)->id = temp.id;

				temp.wordLength = (wordsArray+j)->wordLength;
				(wordsArray+j)->wordLength = (wordsArray+j+1)->wordLength;
				(wordsArray+j+1)->wordLength = temp.wordLength;

				//free(temp.word);
				delete [] temp.word;
			}
		}
	}
}

/* puzzle.txt dosyasından okunan veriler, kelimeler
 * bulundukça silinmek amacıyla **finalPuzzleArray'a 
 * eşitlenmiştir.
 */
void sync_array(){

	finalPuzzleArray = new char*[rows];
	for (int i = 0; i < rows; ++i)
	{
		*(finalPuzzleArray+i) = new char[columns];
	}

	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			*(*(finalPuzzleArray+i)+j) = *(*(puzzleArray+i)+j);
		}
	}
 //	finalPuzzleArray = puzzleArray;		//hata veriyor temizlerken
}

bool verticalSearch(char** puzzleArray, searchedWord* word){

  /* These loops and controls(if) find words from left to right. */
	/* This and next loops allows to move at the puzzle locations. */
	for (int j = 0; j < columns; ++j)					
	{	
		/* This and previous loops allows to move at the puzzle locations. */
		for (int i = 0; i < (rows - word->wordLength + 1); ++i)					
		{
			if (*(*(puzzleArray+i)+j) == word->word[0])
			{
				int say=0;
				
				for (int k = 0; k < word->wordLength; ++k)
				{
					/* This function controls whether the word exists in the puzzle;
					 * if word's "k numbered" character is same puzzle's "k numbered"
					 * (after word's first character is same puzzle any character)
					 * character say++, and if say and wordLength same, word exists
					 * in the puzzle
					 */
					if(*(*(puzzleArray+i+k)+j) == word->word[k])				
					{
						say++;
					}
				}

				/* If say and wordLength same, word exists in the puzzle */
				if(say==word->wordLength)
				{	
					/* This line reports in which indexes and direction searched words are found in the puzzle to file. */
				 //	fprintf(stdout, "%s\tVERTICAL\t[%d][%d]-[%d][%d]\n",word->word, i, j, i+word->wordLength-1, j );
					fprint_word('v',word->word, i, j, i+word->wordLength-1, j  );

					/* This loop clears word that is found */
					for (int q = i; q <= i+word->wordLength-1; ++q)
					{
						*(*(finalPuzzleArray+q)+j) = ' ';
					}
					return EXIT_SUCCESS;
				}
			}
		}
	}



  /* These loops and controls find words from right to left. */
	/* This and next loops allows to move at the puzzle locations. */
	for (int j = 0; j < columns; ++j)					
	{	
		/* This and previous loops allows to move at the puzzle locations. */
		for (int i=word->wordLength-1 ; i < rows; ++i)					
		{
			/* These operations control whether the word exists
			 * in the puzzle from down to up
			 */
			if (*(*(puzzleArray+i)+j) == word->word[0])
			{
				int say = 0;
				
				for (int k = 0; k < word->wordLength; ++k)
				{
					/* This function controls whether the word exists in the puzzle;
					 * if word's "k numbered" character is same puzzle's "k numbered"
					 * (after word's first character is same puzzle any character)
					 * character say++, and if say and wordLength same, word exists
					 * in the puzzle
					 */
					if(*(*(puzzleArray+i-k)+j) == word->word[k])				
					{
						say++;
					}
				}

				if(say==word->wordLength)
				{	
					/* This line reports in which indexes and direction searched words are found in the puzzle to file. */
				 //	fprintf(stdout, "%s\tVERTICAL\t[%d][%d]-[%d][%d]\n",word->word, i, j, i-word->wordLength+1, j );
					fprint_word('v',word->word, i, j, i-word->wordLength+1, j );

					/* This loop clears word that is found */
					for (int q = i; q >= i-word->wordLength+1; --q)
					{
						*(*(finalPuzzleArray+q)+j) = ' ';
					}
					return EXIT_SUCCESS;
				}
			}
		}
	}

	return EXIT_FAILURE;
}

bool horizontalSearch(char** puzzleArray, searchedWord* word){

  /* These loops and controls find words from top to bottom. */
	/* This and next loops allows to move at the puzzle locations. */
	for (int i = 0; i < rows; ++i)					
	{	
		/* This and previous loops allows to move at the puzzle locations. */
		for (int j = 0; j < (columns - word->wordLength + 1); ++j)					
		{
			if (*(*(puzzleArray+i)+j) == word->word[0])
			{
				int say=0;
				
				for (int k = 0; k < word->wordLength; ++k)
				{
					/* This function controls whether the word exists in the puzzle;
					 * if word's k. character is same puzzle's k. (after word's first
					 * character is same puzzle any character) character say++, and 
					 * if say and wordLength same, word exists in the puzzle
					 */
					if(*(*(puzzleArray+i)+j+k) == word->word[k])				
					{
						say++;
					}
				}

				/* If say and wordLength same, word exists in the puzzle */
				if(say==word->wordLength)
				{	
					/* This line reports in which indexes and direction searched words are found in the puzzle to file. */
				 //	fprintf(stdout, "%s\tHORIZONTAL\t[%d][%d]-[%d][%d]\n",word->word, i, j, i, j+word->wordLength-1 );
					fprint_word('h', word->word, i, j, i, j+word->wordLength-1 );

					/* This loop clears word that is found */
					for (int q = j; q <= j+word->wordLength-1; ++q)
					{
						*(*(finalPuzzleArray+i)+q) = ' ';
					}
					return EXIT_SUCCESS;
				}
			}
		}
	}



  /* These loops and controls find words from bottom to top. */
	/* This and next loops allows to move at the puzzle locations. */
	for (int i = 0; i < rows; ++i)					
	{	
		/* This and previous loops allows to move at the puzzle locations. */
		for (int j=word->wordLength-1 ; j < columns; ++j)					
		{
			/* These operations control whether the word exists
			 * in the puzzle from down to up
			 */
			if (*(*(puzzleArray+i)+j) == word->word[0])
			{
				int say = 0;
				
				for (int k = 0; k < word->wordLength; ++k)
				{
					/* This function controls whether the word exists in the puzzle;
					 * if word's k. character is same puzzle's k. (after word's first
					 * character is same puzzle any character) character say++, and 
					 * if say and wordLength same, word exists in the puzzle
					 */
					if(*(*(puzzleArray+i)+j-k) == word->word[k])				
					{
						say++;
					}
				}

				if(say==word->wordLength)
				{	
					/* This line reports in which indexes and direction searched words are found in the puzzle to file. */
				 //	fprintf(stdout, "%s\tHORIZONTAL\t[%d][%d]-[%d][%d]\n",word->word, i, j, i, j-word->wordLength+1 );
					fprint_word('h', word->word, i, j, i, j-word->wordLength+1 );

					/* This loop clears word that is found */
					for (int q = j; q >= j-word->wordLength+1; --q)
					{
						*(*(finalPuzzleArray+i)+q) = ' ';
					}	
					return EXIT_SUCCESS;
				}
			}
		}
	}

	return EXIT_FAILURE;
}

bool diagonalSearch(char** puzzleArray, searchedWord* word){

  /* These loops and controls find words from left top to right bottom. */
	/* This and next loops allows to move at the puzzle locations. */
	for (int i = 0 ; i < (rows - word->wordLength + 1); ++i)					
	{	
		/* This and previous loops allows to move at the puzzle locations. */
		for (int j = 0; j < (columns - word->wordLength + 1); ++j)					
		{
			if (*(*(puzzleArray+i)+j) == word->word[0])
			{
				int say=0;
				
				for (int k = 0; k < word->wordLength; ++k)
				{
					/* This function controls whether the word exists in the puzzle;
					 * if word's k. character is same puzzle's k. (after word's first
					 * character is same puzzle any character) character say++, and 
					 * if say and wordLength same, word exists in the puzzle
					 */
					if(*(*(puzzleArray+i+k)+j+k) == word->word[k])				
					{
						say++;
					}
				}

				/* If say and wordLength same, word exists in the puzzle */
				if(say==word->wordLength)
				{	
					/* This line reports in which indexes and direction searched words are found in the puzzle to file. */
				 //	fprintf(stdout, "%s\tDIAGONAL\t[%d][%d]-[%d][%d]\n",word->word, i, j, i+word->wordLength-1, j+word->wordLength-1 );
					fprint_word('d', word->word, i, j, i+word->wordLength-1, j+word->wordLength-1 );

					/* This loop clears word that is found */
					for (int q = j, w=i; q <= j+word->wordLength-1; ++q, ++w)
					{
						*(*(finalPuzzleArray+w)+q) = ' ';
					}
					return EXIT_SUCCESS;
				}
			}
		}
	}



  /* These loops and controls find words from right bottom to left top. */
	/* This and next loops allows to move at the puzzle locations. */
	for (int i=word->wordLength-1 ; i < rows; ++i)					
	{	
		/* This and previous loops allows to move at the puzzle locations. */
		for (int j=word->wordLength-1 ; j < columns; ++j)					
		{
			/* These operations control whether the word exists
			 * in the puzzle from down to up
			 */
			if (*(*(puzzleArray+i)+j) == word->word[0])
			{
				int sayTers = 0;
				
				for (int k = 0; k < word->wordLength; ++k)
				{
					/* This function controls whether the word exists in the puzzle;
					 * if word's k. character is same puzzle's k. (after word's first
					 * character is same puzzle any character) character sayTers++, and 
					 * if sayTers and wordLength same, word exists in the puzzle
					 */
					if(*(*(puzzleArray+i-k)+j-k) == word->word[k])				
					{
						sayTers++;
					}
				}

				if(sayTers==word->wordLength)
				{	
					/* This line reports in which indexes and direction searched words are found in the puzzle to file. */
				 //	fprintf(stdout, "%s\tDIAGONAL\t[%d][%d]-[%d][%d]\n",word->word, i, j, i-word->wordLength+1, j-word->wordLength+1 );
					fprint_word('d', word->word, i, j, i-word->wordLength+1, j-word->wordLength+1 );
					/* This loop clears word that is found */
					for (int q = j, w=i; q >= j-word->wordLength+1; --q, --w)
					{
						*(*(finalPuzzleArray+w)+q) = ' ';
					}
					return EXIT_SUCCESS;
				}
			}
		}
	}


  /* These loops and controls find words from right top to left bottom. */
	/* This and next loops allows to move at the puzzle locations. */
	for (int i = word->wordLength-1 ; i < rows; ++i)					
	{	
		/* This and previous loops allows to move at the puzzle locations. */
		for (int j = 0; j < (columns - word->wordLength + 1); ++j)					
		{
			if (*(*(puzzleArray+i)+j) == word->word[0])
			{
				int say=0;
				
				for (int k = 0; k < word->wordLength; ++k)
				{
					/* This function controls whether the word exists in the puzzle;
					 * if word's k. character is same puzzle's k. (after word's first
					 * character is same puzzle any character) character say++, and 
					 * if say and wordLength same, word exists in the puzzle
					 */
					if(*(*(puzzleArray+i-k)+j+k) == word->word[k])				
					{
						say++;
					}
				}

				/* If say and wordLength same, word exists in the puzzle */
				if(say==word->wordLength)
				{	
					/* This line reports in which indexes and direction searched words are found in the puzzle to file. */
				 //	fprintf(stdout, "%s\tDIAGONAL\t[%d][%d]-[%d][%d]\n",word->word, i, j, i-word->wordLength+1, j+word->wordLength-1 );
					fprint_word('d', word->word, i, j, i-word->wordLength+1, j+word->wordLength-1 );

					/* This loop clears word that is found */
					for (int  w=i, q=j; w >= i-word->wordLength+1; ++q, --w)
					{
						*(*(finalPuzzleArray+w)+q) = ' ';
					}
					return EXIT_SUCCESS;
				}
			}
		}
	}

  /* These loops and controls find words from left bottom to right top. */
	/* This and next loops allows to move at the puzzle locations. */
	for (int i = 0 ; i < (rows - word->wordLength + 1); ++i)				
	{	
		/* This and previous loops allows to move at the puzzle locations. */
		for (int j=word->wordLength-1 ; j < columns; ++j)					
		{
			/* These operations control whether the word exists
			 * in the puzzle from down to up
			 */
			if (*(*(puzzleArray+i)+j) == word->word[0])
			{
				int sayTers = 0;
				
				for (int k = 0; k < word->wordLength; ++k)
				{
					/* This function controls whether the word exists in the puzzle;
					 * if word's k. character is same puzzle's k. (after word's first
					 * character is same puzzle any character) character sayTers++, and 
					 * if sayTers and wordLength same, word exists in the puzzle
					 */
					if(*(*(puzzleArray+i+k)+j-k) == word->word[k])				
					{
						sayTers++;
					}
				}

				if(sayTers==word->wordLength)
				{	
					/* This line reports in which indexes and direction searched words are found in the puzzle to file. */
				 //	fprintf(stdout, "%s\tDIAGONAL\t[%d][%d]-[%d][%d]\n",word->word, i, j, i+word->wordLength-1, j-word->wordLength+1 );
					fprint_word('d', word->word, i, j, i+word->wordLength-1, j-word->wordLength+1 );
					
					/* This loop clears word that is found */
					for (int w=i, q=j; w <= i+word->wordLength-1; --q, ++w)
					{
						*(*(finalPuzzleArray+w)+q) = ' ';
					}
					return EXIT_SUCCESS;
				}
			}
		}
	}

	return EXIT_FAILURE;
}

void copcu(){

	for (int i = 0; i < rows; ++i)
	{
		delete [] puzzleArray[i];
	}
	delete [] puzzleArray;

	for (int i = 0; i < rows; ++i)
	{
		delete [] finalPuzzleArray[i];
	}
	delete [] finalPuzzleArray;

	
	for (int i = 0; i < numberWords ; ++i)
	{
		delete [] wordsArray[i].word;
	}
	delete [] wordsArray;
}

/* puzzle'dan bulunan kelimeler temizlendikten sonra
 * son hali dosyaya yazılır
 */
bool fprint_puzzle(){

	FILE *dgFinalPuzzle;
	dgFinalPuzzle = fopen("lastVersionPuzzle.txt","w");
	if(dgFinalPuzzle == NULL)
	{
		cout << "Dosya oluşturulamadı" << endl;
		return EXIT_FAILURE;
	}

	print_puzzle(finalPuzzleArray, dgFinalPuzzle);

	fclose(dgFinalPuzzle);
	return EXIT_SUCCESS;
}

/* Bulunan kelimeler istenen formatta dosyaya yazılır. */
bool fprint_word(char y, char *word, int a, int b, int c, int d){

	FILE *dgFoundWords = fopen("foundWordsInfo.txt","a");
	if(dgFoundWords == NULL)
	{
		cout << "Dosya oluşturulamadı" << endl;
		return EXIT_FAILURE;
	}

		 if(y=='h')	fprintf(dgFoundWords, "%s\tHORIZONTAL\t[%d][%d]\t- [%d][%d]\n",word, a, b, c, d );
	else if(y=='d')	fprintf(dgFoundWords, "%s\tDIAGONAL\t[%d][%d]\t- [%d][%d]\n",word, a, b, c, d );
	else if(y=='v')	fprintf(dgFoundWords, "%s\tVERTICAL\t[%d][%d]\t- [%d][%d]\n",word, a, b, c, d );
	else {	cout << "Ne taraftan buldun kardeş" << endl;	return EXIT_FAILURE;	}

	fclose(dgFoundWords);
	return EXIT_SUCCESS;
}