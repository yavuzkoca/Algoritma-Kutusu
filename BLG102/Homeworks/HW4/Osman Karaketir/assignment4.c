#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
struct instruction_s {
	int step;
	int index;
};
/*
 * Get nth word from string
 *
 * @param s given string
 * @param n requested word
 * @return word
 */
char* get_word(char* s, int n)
{
	//printf("test");
	char* word=(char*)malloc(sizeof(char)*50);
	int space=0;
	int it=0;
	for(space=0;space<n-1;it++)
	{
	
		if(s[it]==' ')
		{
			space++;
		}
	}
	sscanf(s+it,"%s",word);
	return word;
}
/*
 * Create string from book and instructions
 *
 * @param lines array of strings that includes book
 * @param instructions array of instructions
 * @param n_instructions number of instructions
 * @param sentence the string that results will write to
 */
void get_sentence(char** lines, struct instruction_s* instructions, int n_instructions, char* sentence)
{
	
	int index=-1;
	int len_sentence=0;
	int step=1;
	for(int i=0;i<n_instructions;i++)
	{
		
		index+=instructions[i].index;
		step=instructions[i].step;
		char* word=get_word(lines[index],step);
		int j;
		for(j=0;word[j]!='\0';j++)
		{
		
			sentence[len_sentence]=word[j];
			len_sentence++;
		}
		sentence[len_sentence]=' ';
		len_sentence++;

		free(word);
	}
	sentence[len_sentence-1]='\0';
}

char* delete(char* line, int n)
{
	char* new_line=(char*)malloc(sizeof(char)*200);
	for(int i=0;i<n;i++)
	{
		new_line[i]=line[i];
	}
	for(int i=n+1;line[i]!='\0';i++)
	{
		new_line[i-1]=line[i];
	}
	free(line);
	return new_line;
}

int main(int argc, char *argv[])
{		
	FILE* file;
	FILE* instruct;
 	file = fopen(argv[1],"r");
	instruct = fopen(argv[2],"r");
	if(file==NULL||instruct==NULL)
 	{
 		return EXIT_FAILURE;
	}
	char** lines=(char**)malloc(sizeof(char*)*10000);
	for(int i=0;i<10000;i++)
	{
		lines[i]=(char*)malloc(sizeof(char)*200);
	}
	int inst_number=1;
	struct instruction_s* instructions=(struct instruction_s*)malloc(sizeof(struct instruction_s)*inst_number);
	fscanf(instruct,"%d",&instructions[0].index);
	fscanf(instruct,"%d",&instructions[0].step);
	int index, step;
	while(fscanf(instruct,"%d",&index)!=EOF)
	{
		fscanf(instruct,"%d",&step);
		inst_number++;
		instructions=(struct instruction_s*)realloc(instructions,sizeof(struct instruction_s)*inst_number);
		instructions[inst_number-1].index=index;
		instructions[inst_number-1].step=step;
	}
	int line_number=0;
	for(line_number=0;fgets(lines[line_number],201,file);line_number++){}
	for(int i=0;i<line_number;i++)
	{
		for(int j=0;lines[i][j]!='\0';j++)
		{
			if(lines[i][j]==' '&&lines[i][j+1]==' ')
			{
				lines[i]=delete(lines[i],j);
				j--;
				continue;
			}
			else if(ispunct(lines[i][j]))
			{
				
				lines[i]=delete(lines[i],j);
				j--;
				continue;
			}
			else if(lines[i][j]>=65&&lines[i][j]<=90)//uppercases to lowercase
			{	
				lines[i][j]+=32;
				continue;
			
			}
		}
	}
	fclose(file);
	fclose(instruct);
	file=NULL;
	instruct=NULL;
	char* sentence;
	sentence=(char*)malloc(sizeof(char)*inst_number*200);
	get_sentence(lines, instructions, inst_number, sentence);
	printf("%s",sentence);
	free(sentence);
	for(int i=0;i<10000;i++)
	{
		free(lines[i]);
	}
	free(lines);
	free(instructions);
	lines=NULL;
	instructions=NULL;
	return EXIT_SUCCESS;
}
