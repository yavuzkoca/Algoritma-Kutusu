#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lex_cmp(const char *word1, const char *word2){
	int char1 = int(*word1) > 96 ? int(*word1) - 32 : int(*word1);
	int char2 = int(*word2) > 96 ? int(*word2) - 32 : int(*word2);
	if( char1 > char2 ) return 1;
	else if (char1 == char2){
		char *temp_word1 = (char *)malloc(sizeof(char)* 80);
		char *temp_word2 = (char *)malloc(sizeof(char)* 80);
		for (int i = 0; *(word1 + i + 1) != '\0'; ++i)
			*(temp_word1 + i) = *(word1 + i + 1);
		for (int i = 0; *(word2 + i + 1) != '\0'; ++i)
			*(temp_word2 + i) = *(word2 + i + 1);
		return lex_cmp(temp_word1, temp_word2);
	}
	else return 0;
}

typedef struct Node{
	Node *next;
	char *name;
	char *no;
}Node;

typedef struct LinkedList{
	Node *head;
	int size;

	void create();
	void add(const char *, const char *);
	void remove(int);
	void update(int);
	void list();
	Node search();	
	void remove();
}LList;

void LinkedList::create(){
	head = NULL;
	size = 0;
}

void LinkedList::add(const char *name, const char *no){
	int str_size;
	if(head == NULL){
		head = (Node *)malloc(sizeof(Node));
		for(str_size = 0; *(name + str_size) != '\0'; ++str_size);
		head->name = (char *)malloc(sizeof(char) * str_size);
		strcpy(head->name, name);
		for(str_size = 0; *(name + str_size) != '\0'; ++str_size);
		head->no = (char *)malloc(sizeof(char) * str_size);
		strcpy(head->no, no);
		head->next = NULL;
		size = 1;
		return;
	}
	else{
		Node *tail = head;
		Node *traverser = head;
		Node *new_node = (Node *)malloc(sizeof(Node));
		for(str_size = 0; *(name + str_size) != '\0'; ++str_size);
		new_node->name = (char *)malloc(sizeof(char) * str_size);
		strcpy(new_node->name, name);
		for(str_size = 0; *(name + str_size) != '\0'; ++str_size);
		new_node->no = (char *)malloc(sizeof(char) * str_size);
		strcpy(new_node->no, no);
		while(traverser != NULL){
			if( lex_cmp(name, traverser->name) ){
				tail = traverser;
				traverser = traverser->next;
			}
			else{
				if(tail == traverser){
					new_node->next = head;
					head = new_node;
					++size;
					return;
				}
				else{
					new_node->next = traverser;
					tail->next = new_node;
					++size;
					return;
				}
			}
		}
		tail->next = new_node;
		new_node->next = NULL;
		this->list();
		return;
	}
}

void LinkedList::list(){
	Node *traverser;
	if(size != 0)
		traverser = head;
	for(int i = 0; i < size; ++i){
		printf("%d. %s %s - Size: %d\n",
			(i + 1),
			traverser->name,
			traverser->no,
			size);
		traverser = traverser->next;
	}
}

void LinkedList::remove(){
	Node *tail = head;
	Node *traverser = head;
	int init_size = size;
	for(int i = 0; i < init_size; ++i){
		free( traverser->name );
		free( traverser->no );
		tail = traverser;
		traverser = traverser->next;
		free( tail );
		--size;
	}
}

int main(){

	LList liste;
	liste.create();

	liste.add("Zahir", "41312");
	liste.add("Bugra", "123");
	liste.add("dilara", "21312");
	liste.add("Ayilkin", "321234");
	liste.add("Yavuz", "3242344");
	liste.add("Ali Tolga", "34352424");
	liste.add("Oguz", "12332424");
	liste.add("yemliha", "32421234");
	liste.list();

	liste.remove();

	liste.list();

	return 0;
}
