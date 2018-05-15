/*
* Copyright (c) 2018 by Uğur Ali Kaplan
* You are free to do anything you want with this code
* provided you give attribute to original author.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARSIZE 10000
#define LEN 200

// Instruction struct
struct instruction_s {
  int step;
  int index;
};

// Function prototypes
char *get_word(char *s, int n);
void get_sentence(char **lines, struct instruction_s *instructions,
                  int n_instructions, char *sentence);

int main(int argc, char *argv[]) {
  FILE *f_book, *f_inst;
  int counter = 0;
  char line[LEN], to_print[LEN];
  int i = 0;
  int ch;
  // Setting up our book array
  char **book_ar = malloc(ARSIZE * sizeof(char *));
  for (; i < ARSIZE; i++) {
    book_ar[i] = malloc(LEN * sizeof(char));
  }
  i = 0;

  // Check if enough arguments provided by the user, if not exit
  if (argc != 3) {
    fprintf(stderr, "Usage: %s book_file_name instruction_file_name\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  // Try to open files, if not exit
  if (((f_book = fopen(argv[1], "r")) == NULL) ||
      (f_inst = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "Error in opening files.\n");
    exit(EXIT_FAILURE);
  }

  // Figuring out how many lines instruction file has
  while ((ch = getc(f_inst)) != EOF) {
    if (ch == '\n')
      counter++;
  }

  // Go back to beginning so we can save the values to structs
  rewind(f_inst);

  // Create an array of structs to hold the instructions
  struct instruction_s inst_st[counter];

  // Every line gets its own struct
  while (fscanf(f_inst, "%d %d", &inst_st[i].step, &inst_st[i].index) == 2) {
    i++;
  }
  i = 0;
  // We are done with instructions file
  fclose(f_inst);

  // Save all lines of the book into an array
  while (fgets(line, LEN - 1, f_book) != NULL) {
    // Destroy "\n" added by fgets
    for (int j = 0; j < strlen(line); j++) {
      if (line[j] == '\n') {
        line[j] = '\0';
      }
    }
    strcpy(book_ar[i], line);
    i++;
  }

  get_sentence(book_ar, inst_st, counter, to_print);
  printf("%s\n", to_print);

  free(book_ar);
  fclose(f_book);

  return 0;
}

/*
*@param s is the line provided by book array
*@param n is the word we want to extract
*@return word is the extracted word
*/
char *get_word(char *s, int n) {
  static char word[LEN];
  for (int i = 0; i < LEN; i++) {
    word[i] = '\0';
  }
  int start = 0;
  int stop = 0;
  int space_count = 0;

  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == ' ' || i == (strlen(s) - 1)) {
      if (s[i - 1] != ' ')
        space_count++;
      if (space_count == (n - 1)) {
        start = i + 1;
      }
      if (space_count == (n)) {
        stop = i;
      }
    }
  }

  for (int i = start; i < stop; i++) {
    if (!ispunct(s[i])) {
      word[i] = tolower(s[i]);
    }
  }

  strncpy(word, &s[start], (size_t)(stop - start));

  for (int i = 0; i < strlen(word); i++) {
    word[i] = tolower(word[i]);
  }

  for (int i = 0; i < strlen(word); i++) {
    if (ispunct(word[i])) {
      word[i] = word[i + 1];
    }
  }

  return word;
}

/*
*@param lines is the book array containing all the lines of the book file
*@param instructions is array of structs containing *surprise* instructions
*@param n_instructions specifies how many instruction structs we have
*@param sentence is sentence to be printed after process is done
*/
void get_sentence(char **lines, struct instruction_s *instructions,
                  int n_instructions, char *sentence) {
  sentence[0] = '\0';
  int book_mark = -1;
  for (int i = 0; i < n_instructions; i++) {
    book_mark += instructions[i].step;
    strcat(sentence, get_word(lines[book_mark], instructions[i].index));
    if (i != (n_instructions - 1)) {
      strcat(sentence, " ");
    }
  }
}
