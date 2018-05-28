#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc
#include <stdbool.h> // type bool
#define MAX 200 // constant holding the maximum size of arrays
#define LINE_MAX 10000 // constant holding the maximum number of lines a book can have

/*
A struct holding two integers, offset of the line
and the index of the word which lays within that lines, respectively
*/
struct instruction_s{
    int step;
    int index;
};

/*
gets the name of the file, returns the number of the lines
@param a string holding the name of the file
@return an integer holding the amount of lines a file has
*/
int get_number_of_lines(char *file){
    FILE *stream = fopen(file, "r");
    int c, result = 0;
    while((c = fgetc(stream)) != EOF){
        if(c == '\n') result++;
    }
    fclose(stream);
    return result;
}

/*
gets a string and returns the nth word, n is 0-based
@param an array of chars
@param an integer holding the index of the word, n is 0-based
@return the asked word
*/
char *get_word(char *s, int n){
    char c;
    char *word = (char *)malloc(sizeof(char) * MAX);
    int counter = 0, word_counter = 0, character_counter = 0;
    int current_max = MAX;
    bool last_was_blank = false; // a bool created to avoid counting spaces as words

    while((c = s[counter++]) != '\0'){
        if(c == ' '){
            if(!last_was_blank) word_counter++;
            last_was_blank = true;
            continue; // continue to avoid starting with a blank character
        }else{
            last_was_blank = false;
        }
        if(n == word_counter){
            word[character_counter++] = c;
            if(character_counter > current_max){
                word = (char *)realloc(word, sizeof(char) * current_max * 2);
                current_max *= 2;
            }
        }else if(word_counter > n) break;
    }
    word[character_counter] = '\0';
    return word;
}

/*
gets the array of lines, iterates over instructions and get each word that is being asked in 
the instructions, save words into the parameter which is string named sentence
@param array of each line, 0-based indexed
@param array holding the pointers pointing to instructions
@param the number of instructions
@param string to store my output sentence
*/
void get_sentence(char **lines, struct instruction_s **instructions, int n_instructions, char *sentence){
    int line_number = 0, index = 0, sentence_n = 0;
    for(int i=0; i<n_instructions; i++){
        line_number += instructions[i]->step; // to avoid offset
        index = instructions[i]->index;
        char *word = get_word(lines[line_number - 1], index - 1);
        while(*(word) != '\0'){
            sentence[sentence_n++] = *(word++);
        }
        sentence[sentence_n++] = ' ';
    }
    sentence[sentence_n] = '\0';
    return;
}

int main(int argc, char **argv){
    FILE *instructions_stream = fopen(argv[2], "r");
    FILE *book_stream = fopen(argv[1], "r");

    if(!instructions_stream || !book_stream){ // check if file exists
    	printf("An error occured while trying to open the file.\n");
    	return 1;
    }

    struct instruction_s **instructions = (struct instruction_s **)malloc(sizeof(struct instruction_s) * MAX); // an array holding pointers pointing to struct instruction_s
    int instructions_size = 0; // integer holding the size of the array instructions
    
    int step, index;
    for(int i=0; i<get_number_of_lines(argv[2]); i++){
        fscanf(instructions_stream, "%d %d", &step, &index);
        struct instruction_s *new_instruction = (struct instruction_s *)malloc(sizeof(struct instruction_s));
        new_instruction->step = step;
        new_instruction->index = index;
        instructions[instructions_size++] = new_instruction;
    }

    fclose(instructions_stream); // close instructions stream

    char **lines = (char **)malloc(sizeof(char) * LINE_MAX);
    int lines_n = 0, c;

    while((c = fgetc(book_stream)) != EOF){
        char *line = (char *)malloc(sizeof(char) * MAX);
        int line_n = 0;
        while(c != '\n'){
            if(c == 32 || (c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
                if(c >= 65 && c <= 90){
                    c += 32;
                }
                line[line_n++] = c;
            }
            c = fgetc(book_stream);
        }        
        lines[lines_n++] = line;
    }
    
    fclose(book_stream); // close book stream

    char *sentence = (char *)malloc(sizeof(char) * MAX);
    get_sentence(lines, instructions, instructions_size, sentence);
    printf("%s\n", sentence);
    
    free(sentence);
    free(instructions);

    return 0;
}
