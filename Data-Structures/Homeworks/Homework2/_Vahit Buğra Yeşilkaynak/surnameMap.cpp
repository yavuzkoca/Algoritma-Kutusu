#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "surnameMap.h"


#define MAX_BUFFER_SIZE 80

const char *extension = "@itu.edu.tr";
const int extension_size = 11;

int strToInt(const char *number){
	int sum = 0;
	for(int i = 0; *(number + i) != '\0'; ++i)
		sum = sum * 10 + *(number + i) - '0';
	return sum;
}

char *intToStr(int number){
	char *temp = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
	int size;
	for(size = 0; number != 0; ++size){
		*(temp + size) = number % 10 + '0';
		number /= 10;
	}
	char *num = (char *)malloc(sizeof(char) * (size + 1));
	for(int i = 0; i < size; ++i)
		*(num + i) = *(temp + size - 1 - i);
	*(num + size) = '\0';
	free(temp);
	return num;
}

char * addExtension(studentInfo *info){
	char *email = (char *)malloc(sizeof(char) * (info->email_size + extension_size));
	for(int i = 0; i < info->email_size - 1; ++i)
		*(email + i) = *(info->email + i) <= 'Z' && *(info->email + i) >= 'A' ? *(info->email + i) + 'a' - 'A' : *(info->email + i);
	for(int i = 0; i < extension_size; ++i)
		*(email + info->email_size + i - 1) = *(extension + i);
	*(email + info->email_size + extension_size - 1) = '\0';
	return email;
}
/*
void nameHolder::create(const char* name_input, int input_size){
	size = 0;
	total_name_size = 0;
	for(int i = 0; i < input_size; ++i){
		if(*(name_input + i) == ' ') ++size;
	}
	++size;
	sizes = (int *)malloc(sizeof(int) * size);
	names = (char **)malloc(sizeof(char *) * size);
	int size_count = 0;
	int name_count = 0;
	char *temp = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
	for(int i = 0; i < input_size; ++i){
		if(*(name_input + i) == ' '){
			++size_count;
			*(names + name_count) = (char *)malloc(sizeof(char) * size_count);
			*(sizes + name_count) = size_count;
			total_name_size += size_count - 1;
			strcpy(*(names + name_count), temp);
			size_count = 0;
			++name_count;
			temp = (char *)realloc(temp, sizeof(char) * MAX_BUFFER_SIZE);
		}
		else{
			*(temp + size_count) = *(name_input + i);
			++size_count;
		}
	}
	*(names + name_count) = (char *)malloc(sizeof(char) * size_count);
	*(sizes + name_count) = size_count;
	total_name_size += size_count;
	strcpy(*(names + name_count), temp);
	free(temp);
}

void nameHolder::print(){
	for(int i = 0; i < size; ++i)
		printf("%s - %d\n", *(names + i), *(sizes + i));
	printf("%d\n", total_name_size);
}

void nameHolder::empty(){
	for(int i = 0; i < size; ++i)
		free(*(names + i));
	free(names);
}

char *nameHolder::getConcatenatedName(){
	if(size == 1)
		return *names; // Eğer tek isimli ise deleteStudenttan sonra names boş olacak çünkü isim bunu point edecek
	char *total = (char *)malloc(sizeof(char) * (total_name_size + 1));
	int count = 0;
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < *(sizes + i) - 1; ++j){
			*(total + count) = *(*(names + i) + j);
			++count;
		}
	}
	*(total + total_name_size) = '\0';
	return total;
}*/

void surnameNode::decideEmail(studentInfo *info){
	if(this->size == 0){ // If no student in the surnameNode, email is directly the surname
		info->email = this->surname;
		info->email_size = this->surname_size;
		info->number = 0;
	}
	else{
		studentInfo *traverser = this->infoHead;
		int max_match = -1; // Counter for the maximum character match
		studentInfo *max_node = NULL; // Max matched ndde
		for(int i = 0; i < this->size; ++i){ // For every student in the node
			int count = 0;
			for(int i = 0; i < info->name_size - 1 && *(traverser->email + this->surname_size - 1 + i) == *(info->name + count); ++i)
				++count; // Increment until mismatch
			if(count > max_match){ // If current node better then max
				max_match = count;
				max_node = traverser;
			}
			else if(count == max_match && max_node->name_size == traverser->name_size){
				if(traverser->number > max_node->number) // if there is a number at the end we want the biggest
					max_node = traverser; 
			}
			traverser = traverser->next;
		}
		if(max_match == 0){ // If no match add only the first letter
			char *temp = (char *)malloc(sizeof(char) * (this->surname_size + 1));
			strcpy(temp, this->surname);
			*(temp + this->surname_size - 1) = *(info->name);
			*(temp + this->surname_size) = '\0';
			info->email = temp;
			info->email_size = this->surname_size + 1;
		}
		else if(max_match == info->name_size - 1){ // If full match if the max has no number put 2 else increment the max
			char *temp = (char *)malloc(sizeof(char) * (this->surname_size + info->name_size));
			strcpy(temp, this->surname);
			strcpy(temp + this->surname_size - 1, info->name);
			if(max_node->number == 0)
				info->number = 2;
			else
				info->number = max_node->number + 1;
			*(temp + this->surname_size + info->name_size - 2) = info->number + '0';
			*(temp + this->surname_size + info->name_size - 1) = '\0';
			info->email = temp;
			info->email_size = this->surname_size + info->name_size;
		}
		else{ // Put as many characters as needed to avoid having the same email
			char *temp = (char *)malloc(sizeof(char) * (this->surname_size + max_match + 1));
			strcpy(temp, this->surname);
			for(int i = 0; i < max_match + 1; ++i)
				*(temp + this->surname_size - 1 + i) = *(info->name + i);
			*(temp + this->surname_size + max_match) = '\0';
			info->email = temp;
			info->email_size = this->surname_size + max_match + 1;
		}
	}
}

void surnameMap::create(){ // Initialize the circular linked list
	size = 0;
	head = NULL;
}

surnameNode * surnameMap::ifSurnameExists(const char *surname){ // returns the surnameNode if exists, else NULL
	if(size == 0) return NULL;
	else{
		surnameNode *traverser = head;
		for(int i = 0; i < size; ++i){
			if(strcmp(traverser->surname, surname) == 0)
				return traverser;
			traverser = traverser->next;
		}
	}
	return NULL;
}

surnameNode * surnameMap::addSurname(const char *surname, int surname_size){
	surnameNode *check = this->ifSurnameExists(surname); // check if there is such a surname, if there is return it
	if( check ) return check;
	surnameNode *temp = (surnameNode *)malloc(sizeof(surnameNode)); // else create it then return it
	temp->surname = (char *)malloc(sizeof(char) * surname_size);
	strcpy(temp->surname, surname);
	temp->infoHead = NULL;
	temp->size = 0;
	temp->surname_size = surname_size;
	if(size == 0){ // If it is the first element added to surnameMap
		head = temp;
		temp->next = temp;
		++size;
		return temp;
	}
	else if(size == 1){ // If it is the second
		head->next = temp;
		temp->next = head;
		if(strcmp(temp->surname, head->surname) < 0)
			head = temp;
		++size;
		return temp;
	}
	else{ // Else
		surnameNode *traverser = head;
		if(strcmp(head->surname, surname) >= 0){
			temp->next = head;
			for(int i = 0; i < size - 1; ++i)
				traverser = traverser->next;
			traverser->next = temp;
			head = temp;
			++size;
			return temp;
		}
		for(int i = 0; i < size - 2; ++i){
			if( strcmp(surname, traverser->next->surname) >= 0){
				traverser = traverser->next;
			}
			else{
				temp->next = traverser->next;
				traverser->next = temp;
				++size;
				return temp;
			}
		}
		traverser = traverser->next;
		temp->next = head;
		traverser->next = temp;
		++size;
		return temp;
	}
}

void surnameMap::insertNewRecord(const char *name, const char *surname, int name_size, int surname_size){
	surnameNode *currentSurname = this->ifSurnameExists(surname); // Find the surname node
	studentInfo *temp = (studentInfo *)malloc(sizeof(studentInfo)); // Create student node
	temp->next = NULL; // This is the only node so both previous and next is NULL
	temp->previous = NULL;

	temp->name = (char *)malloc(sizeof(char) * name_size); // Allocate memory for the name
	strcpy(temp->name, name); // Copy the name to the student node
	temp->name_size = name_size; // Set name_size to the student node
	if(!currentSurname){ // If there is no such surname
		currentSurname = this->addSurname(surname, surname_size);
		currentSurname->decideEmail(temp); // Set email
		currentSurname->infoHead = temp; // Set head for surname node
		currentSurname->infoTail = temp; // Set tail for surname node
		++(currentSurname->size); // Increment the size of surname node doubly linked list
	}
	else{
		currentSurname->decideEmail(temp); // Set email
		if(currentSurname->size == 0){ // If the surnameNode is empty
			currentSurname->infoHead = temp;
			currentSurname->infoTail = temp;
		}
		else if(currentSurname->size == 1){ // If only one element
			if(strcmp(currentSurname->infoHead->email, temp->email) > 0){
				temp->next = currentSurname->infoHead;
				currentSurname->infoHead->previous = temp;
				currentSurname->infoHead->next = NULL;
				currentSurname->infoTail = currentSurname->infoHead;
				currentSurname->infoHead = temp;
			}
			else{
				currentSurname->infoHead->next = temp;
				temp->previous = currentSurname->infoHead;
				currentSurname->infoTail = temp;
			}
		}
		else{ // Else
			if(strcmp(currentSurname->infoHead->email, temp->email) > 0){
				temp->next = currentSurname->infoHead;
				currentSurname->infoHead->previous = temp;
				currentSurname->infoHead = temp;
			}
			studentInfo *traverser = currentSurname->infoHead;
			int i;
			for(i = 0; i < currentSurname->size - 1; ++i)
				if(strcmp(temp->email, traverser->email) > 0)
					traverser = traverser->next;
				else
					break;
			if(i != currentSurname->size - 1){
				temp->next = traverser;
				temp->previous = traverser->previous;
				traverser->previous = temp;
				temp->previous->next = temp;
			}
			else{
				temp->previous = currentSurname->infoTail;
				currentSurname->infoTail->next = temp;
				currentSurname->infoTail = temp;
			}
		}
		++(currentSurname->size);
	}
	printf("\n1 record has been added which is \"%s %s\".\n", temp->name, currentSurname->surname);
	char *temp_email = addExtension(temp);
	printf("Program assigns %s address for the given request.\n", temp_email);
	printf("\n");
	free(temp_email);
}

void surnameMap::printSurnames(){
	surnameNode *traverser = head;
	for(int i = 0; i < size; ++i){
		printf("%d. %s\n", i + 1, traverser->surname);
		traverser = traverser->next;
	}
}

void surnameMap::printEmails(){
	surnameNode *traverser = head;
	for(int i = 0; i < size; ++i){
		printf("%d. %s\n", i + 1, traverser->surname);
		studentInfo *lilTraverser = traverser->infoHead;
		for(int j = 0; j < traverser->size; ++j){
			char *email = addExtension(lilTraverser);
			printf("\t%s-> %s\n", lilTraverser->name, email);
			free(email);
			lilTraverser = lilTraverser->next;
		}
		traverser = traverser->next;
	}
}

void surnameMap::createList(const char *PATH){ // Reads surnames from tab to end and adds them to surnameMap
	// No student info added here, only the surnames
	FILE *listPtr = fopen(PATH, "r");
	char *temp = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
	char *surname;
	int surname_size;
	bool flag;
	int counter;
	while( !feof(listPtr) ){
		surname_size = 0;
		flag = false;
		fgets(temp, MAX_BUFFER_SIZE, listPtr);
		for(int i = 0; *(temp + i) != '\n'; ++i){
			if(*(temp + i) == '\t')
				flag = true;
			else if(flag){
				++surname_size;
			}
		}
		surname = (char *)malloc(sizeof(char) * surname_size);
		flag = false;
		counter = 0;
		for(int i = 0; *(temp + i) != '\n'; ++i){
			if(*(temp + i) == '\t')
				flag = true;
			else if(flag){
				*(surname + counter) = *(temp + i);
				++counter;
			}
		}
		*(surname + counter - 1) = '\0';
		this->addSurname(surname, surname_size);
		free(surname);
	}
	free(temp);
	fclose(listPtr);
}

void surnameMap::insertAll(const char *PATH){ // Reads from the file and adds student informations also decides emails
	FILE *listPtr = fopen(PATH, "r");
	char *temp = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
	char *surname;
	int surname_size;
	char *name;
	int name_size;
	bool flag;
	int counter1, counter2;
	while( !feof(listPtr) ){
		surname_size = 0;
		name_size = 0;
		flag = false;
		fgets(temp, MAX_BUFFER_SIZE, listPtr);
		for(int i = 0; *(temp + i) != '\n'; ++i){
			if(*(temp + i) == '\t')
				flag = true;
			else if(flag){
				++surname_size;
			}
			else if(!flag){
				++name_size;
			}
		}
		++name_size;
		surname = (char *)malloc(sizeof(char) * surname_size);
		name = (char *)malloc(sizeof(char) * name_size);
		flag = false;
		counter1 = 0;
		counter2 = 0;
		for(int i = 0; *(temp + i) != '\n'; ++i){
			if(*(temp + i) == '\t')
				flag = true;
			else if(flag){
				*(surname + counter1) = *(temp + i);
				++counter1;
			}
			else if(!flag){
				*(name + counter2) = *(temp + i);
				++counter2;
			}
		}
		*(surname + counter1 - 1) = '\0';
		*(name + counter2) = '\0';
		this->insertNewRecord(name, surname, name_size, surname_size);
		free(name);
		free(surname);
	}
	free(temp);
	fclose(listPtr);	
}

int surnameMap::deleteStudent(const char *name, const char *surname){ // Deletes a student
	int name_size, surname_size;
	for(name_size = 0; *(name + name_size) != '\0'; ++name_size);
	for(surname_size = 0; *(surname + surname_size) != '\0'; ++surname_size);
	surnameNode *traverser = this->head;
	surnameNode *follower = this->head;
	bool found = false;
	for(int i = 0; i < this->size; ++i){
		if(strcmp(traverser->surname, surname) == 0){
			found = true;
			break;
		}
		follower = traverser;
		traverser = traverser->next;
	}
	if(!found)
		printf("Couldn't find a surname match.\n");
	else{
		studentInfo *lilTraverser = traverser->infoHead;
		bool found = false;
		for(int i = 0; i < traverser->size; ++i){
			if(strcmp(lilTraverser->name, name) == 0){
				found = true;
				break;
			}
			lilTraverser = lilTraverser->next;
		}
		if(!found)
			printf("Couldn't find a name match.\n");
		else{
			if(traverser->size == 1){
				traverser->infoHead = NULL;
				traverser->infoTail = NULL;
				free(lilTraverser->name);
				free(lilTraverser);
				if(this->size == 1){
					head = NULL;
				}
				else{
					if(traverser == head){
						follower = head;
						traverser = traverser->next;
						while(traverser != head){
							follower = traverser;
							traverser = traverser->next;
						}
						follower->next = head->next;
						head = follower; 
					}
					else{
						follower->next = traverser->next;
					}
				}
				free(traverser->surname);
				free(traverser);
				--(this->size);
				return 0;
			}
			else{
				if(lilTraverser->previous != NULL)
					lilTraverser->previous->next = lilTraverser->next;
				else{
					traverser->infoHead = lilTraverser->next;
				}
				if(lilTraverser->next != NULL)
					lilTraverser->next->previous = lilTraverser->previous;
				else
					traverser->infoTail = lilTraverser->previous;
				free(lilTraverser->name);
				if(lilTraverser->email != traverser->surname) // If it is the first added then email == surname so we should keep it
					free(lilTraverser->email);
				free(lilTraverser);
				--(traverser->size);
				return 1;
			}
		}
	}
	return -1;
}

void surnameMap::deleteSurnameNode(const char *surname){
	int surname_size;
	for(surname_size = 0; *(surname + surname_size) != '\0'; ++surname_size);
	surnameNode *traverser = this->head;
	surnameNode *follower = this->head;
	bool found = false;
	for(int i = 0; i < this->size; ++i){
		if(strcmp(traverser->surname, surname) == 0){
			found = true;
			break;
		}
		follower = traverser;
		traverser = traverser->next;
	}
	if(!found) printf("Couldn't find a surname match.\n");
	else{ while(deleteStudent(traverser->infoHead->name, traverser->surname) != 0); }
}

void surnameMap::updateList(const char *old_name, const char *old_surname, const char *new_name, const char *new_surname){
	if(deleteStudent(old_name, old_surname) == -1){
		printf("Update wasn't successful.\n");
	}
	else{
		int new_name_size, new_surname_size;
		for(new_name_size = 0; *(new_name + new_name_size) != '\0'; ++new_name_size);
		for(new_surname_size = 0; *(new_surname + new_surname_size) != '\0'; ++new_surname_size);
		insertNewRecord(new_name, new_surname, new_name_size, new_surname_size);
	}
}

void surnameMap::writeToFile(const char *PATH){
	FILE *listPtr = fopen(PATH, "w");
	surnameNode *traverser = head;
	for(int i = 0; i < size; ++i){
		studentInfo *lilTraverser = traverser->infoHead;
		for(int j = 0; j < traverser->size; ++j){
			char *temp = addExtension(lilTraverser); // This is the email adress with the domain
			fprintf(listPtr, "%-15s%-15s%-15s\n", lilTraverser->name, traverser->surname, temp);
			free(temp);
			lilTraverser = lilTraverser->next;
		}
		traverser = traverser->next;
	}
	fclose(listPtr);
}

void surnameMap::clearAll(){
	while(head != NULL){
		this->deleteSurnameNode(head->surname);
	}
}
