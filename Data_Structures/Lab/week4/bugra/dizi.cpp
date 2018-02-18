#import "dizi.h"
#import "kayit.h"
#import <string.h>
#import <stdio.h>
#import <stdlib.h>

#define DEF_SIZE 2


int lex_cmp(const char *word1, const char *word2){
	if (int(*(word1)) > int(*(word2))){
		return 1;
	}
	else if (int(*(word1)) == int(*(word2))){
		char *temp_word1 = (char *)malloc(sizeof(char)* 80);
		char *temp_word2 = (char *)malloc(sizeof(char)* 80);
		for (int i = 0; *(word1 + i + 1) != '\0'; ++i)
			temp_word1[i] = *(word1 + i + 1);
		for (int i = 0; *(word2 + i + 1) != '\0'; ++i)
			temp_word2[i] = *(word2 + i + 1);
		return lex_cmp(temp_word1, temp_word2);
	}
	else{
		return 0;
	}
}

void List::Create(){
	records = (Record *)malloc(sizeof(Record) * DEF_SIZE);
	current_size = 0;
	max_size = DEF_SIZE;
}

void List::add(Record *yenikayit){
	if(current_size < max_size){

		int char_index_of_search = 0;
		int save_here_index = -1;
		for (int i = 0; i < current_size; ++i){
			if (lex_cmp((records + i)->name, yenikayit->name)){
				save_here_index = i;
				break;
			}
			else{
				continue;
			}
		}

		if (save_here_index != -1){
			for (int i = current_size - 1; i >= save_here_index; --i){
				(records + i + 1)->Create((records + i)->name, (records + i)->no);
			}
		}
		else{
			(records + current_size)->Create(yenikayit->name, yenikayit->no);
		}

		(records + save_here_index)->Create(yenikayit->name, yenikayit->no);
		++current_size;
	}

	else{
		Record *temp = (Record *)malloc(sizeof(Record) * current_size);
		for(int i = 0; i < current_size; ++i){
			(temp + i)->Create( (records + i)->name, (records + i)->no );
		}
		max_size = max_size * 2;
		records = (Record *)realloc(records, sizeof(Record) * max_size);
		for(int i = 0; i < current_size; ++i){
			(records + i)->Create( (temp + i)->name, (temp + i)->no );
		}

		free(temp);

		int char_index_of_search = 0;
		int save_here_index = -1;
		for (int i = 0; i < current_size; ++i){
			if (lex_cmp((records + i)->name, yenikayit->name)){
				save_here_index = i;
				break;
			}
			else{
				continue;
			}
		}

		if (save_here_index != -1){
			for (int i = current_size - 1; i >= save_here_index; --i){
				(records + i + 1)->Create((records + i)->name, (records + i)->no);
			}
		}
		else{
			(records + current_size)->Create(yenikayit->name, yenikayit->no);
		}

		(records + save_here_index)->Create( yenikayit->name, yenikayit->no );
		++current_size;
	}
}

void List::remove(int index){

	(records + index)->Delete();
	--current_size;
	for(int i = index; i < current_size; ++i){
		(records + i)->Create( (records + i + 1)->name, (records + i + 1)->no);
	}

}

void List::list(){
	for(int i = 0; i < current_size; ++i){
		printf("%d. Name: %s - No: %s\n", (i + 1), (records + i)->name, (records + i)->no);
	}
}

void List::search(char *key){ // Bu en son çalışıyordu şimdi bir sebepten çalışmıyor
	int *matches = (int *)malloc(sizeof(int) * current_size);
	for(int i = 0; i < current_size; ++i) *(matches + i) = 1;
	for(int i = 0; *(key + i) != '\0'; ++i){
		for(int j = 0; j < current_size; ++j){
			if(*(matches + j) && *(key + i) != *((records + j)->name + i))
				*(matches + j) = 0;
		}
	}
	for(int i = 0; i < current_size; ++i){
		if(matches[i])
			printf("%d. Name: %s - No: %s\n", (i + 1), (records + i)->name, (records + i)->no);
	}

}

void List::update(int index, char *name, char *no){
	(records + index)->Create(name, no);
	for(int i = 0; i < current_size; ++i){
		for(int j = 0; j < i; ++j){
			if(lex_cmp( (records + j)->name, (records + i)->name ) == 1){
				Record temp;
				temp.Create((records + i)->name, (records + i)->no);
				(records + i)->Create((records + j)->name, (records + j)->no);
				(records + j)->Create(temp.name, temp.no);
			}
		}
	}
}