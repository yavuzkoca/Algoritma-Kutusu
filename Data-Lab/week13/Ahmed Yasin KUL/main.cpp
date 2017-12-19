#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define NAME_LENGTH 30
#define PHONENUM_LENGTH 15
#define TYPE_LENGTH 4

using namespace std;


struct number{
	char *num, *type;
	number *next;
};

struct node{
	char *name;
	number *phonenum;
	node *left, *right;
};

struct tree{
	node *root;
}tree;


number *newNumberNode(char *newNumber, char *newType){
	number *numberNode = new number;
	numberNode->num = new char[PHONENUM_LENGTH];
	numberNode->type = new char[TYPE_LENGTH];
	numberNode->next = NULL;
	strcpy(numberNode->num, newNumber);
	strcpy(numberNode->type, newType);
	return numberNode;
}

node *newContactNode(char *newName){
	node *newNode = new node;
	newNode->name = new char[NAME_LENGTH];
	newNode->left = newNode->right = NULL;
	strcpy(newNode->name, newName);
	return newNode;
}

bool addBinaryTree(node *current, node **newNode){
	if(current == NULL){
		tree.root = *newNode;		//NEDEN CURRENT YAPINCA HATA VERİYOR???
		return true;
	}
	else{
		if(strcmp((*newNode)->name, current->name) < 0){
			if(current->left == NULL){
				current->left = *newNode;
				printf("Contact added...\n");
				return true;
			}
			else{
				addBinaryTree(current->left, newNode);
			}
		}
		if(strcmp((*newNode)->name, current->name) > 0){
			if(current->right == NULL){
				current->right = *newNode;
				printf("Contact added...\n");
				return true;
			}
			else{
				addBinaryTree(current->right, newNode);
			}
		}
		if(strcmp((*newNode)->name, current->name) == 0){
			number *traverse = current->phonenum;
			while(traverse->next != NULL){
				traverse = traverse->next;
			}
			traverse->next = (newNumberNode((*newNode)->phonenum->num, (*newNode)->phonenum->type));
			delete[] (*newNode)->name;
			delete[] newNode;
		}
	}
}

void add(){
	char *newName = new char[NAME_LENGTH], *newNum = new char[PHONENUM_LENGTH], *newType = new char[TYPE_LENGTH];
	cin >> newName;
	cin >> newNum;
	cin >> newType;
	//scanf("Enter the name of the contact:\t%s\nEnter the new number:\t%s\nEnter the type of the number:\t%s", newName, newNum, newType);
	node *newContact = newContactNode(newName);
	newContact->phonenum = newNumberNode(newNum, newType);

	addBinaryTree(tree.root, &newContact);

	delete[] newName;
	delete[] newNum;
	delete[] newType;
}

node *searchContact(node *current, char *searchName){
	if(current == NULL)		return NULL;
	else{
		if(strcmp(searchName, current->name) < 0){
			if(current->left != NULL)	return searchContact(current->left, searchName);
			else		return NULL;
		}
		else if(strcmp(searchName, current->name) > 0){
			if(current->right != NULL)	return searchContact(current->right, searchName);
			else		return NULL;
		}
		else if(strcmp(searchName, current->name) == 0){
			printf("Founded contact: %s\n", current->name);
			number *traverse = current->phonenum;
			if(traverse->next == NULL)		printf("Number:\t%s\nType:\t%s\n", traverse->num, traverse->type);
			while(traverse->next != NULL){
				printf("Number:\t%s\nType:\t%s\n", traverse->num, traverse->type);
				traverse = traverse->next;
			}
			return current;
		}
	}
}

node *search(){
	printf("Enter the name that you want to search/update/delete:\t");
	char *searchWord = new char[NAME_LENGTH];
	cin >> searchWord;
	//scanf("Enter the name of the contact that you want to search:\t%s", searchWord);
	node *result = searchContact(tree.root, searchWord);
	if(result == NULL)		printf("Contact can't be found...\n");
	delete[] searchWord;
	return result;
}

void printContacts(node *p){
	if(p){
		if(p->left)	printContacts(p->left);
		printf("%s\n", p->name);
		number *tempNum = p->phonenum;
		while(tempNum){
			printf("\tNumber:\t%s\n\tType:\t%s\n", tempNum->num, tempNum->type);
			tempNum = tempNum->next;
		}
		if(p->right)	printContacts(p->right);
	}
}



node *remove(node **p, bool mode = true){
	node *r, *q; // used to find place for left subtree
	r = *p;
	if (r == NULL) // attempt to delete nonexistent node
		return NULL;
	else if (r->right == NULL) {
		*p = r->left; // reattach left subtree
		//return r;
	}
	else if (r->left == NULL) {
		*p = r->right; // reattach right subtree
		//return r;
	}
	else { // neither subtree is empty
		for (q = r->right; q->left; q = q->left); // inorder successor
		q->left = r->left; // reattach left subtree
		*p = r->right; // reattach right subtree
		//return r;
	}
	if(mode){
		while(r->phonenum){
			number *traverse = r->phonenum;
			r->phonenum = r->phonenum->next;
			delete[] traverse->num;
			delete[] traverse->type;
			delete traverse;
		}
		delete[] r->name;
		r->left = r->right = NULL;
		delete r;
		return NULL;
	}
	return r;
}

node *rem(char *remove_name, bool mode = true){
	node *traverse = tree.root, *parent = NULL;
	bool found = false;
	char direction = 'k';
	while (traverse && !found){
		int comparison = strcmp(remove_name, traverse->name);
		if (comparison < 0){
			parent = traverse;
			direction = 'l';
			traverse = traverse->left;
		}
		else if (comparison > 0){
			parent = traverse;
			direction = 'r';
			traverse = traverse->right;
		}
		else // found record to remove
			found = true;
	}
	if (found){
		if (direction == 'l')
			return remove(&parent->left, mode);
		else if(direction == 'r')
			return remove(&parent->right, mode);
		else return remove(&tree.root, mode);
	}
	else
		cout << "Could not find record to remove.\n";
		return NULL;
}

void deleteContact(){
	printf("Enter the name that you want to search/update/delete:\t");
	char *deleteWord = new char[NAME_LENGTH];
	cin >> deleteWord;
	rem(deleteWord, true);
	delete[] deleteWord;
}


void update(){
	node *temp = search();
	temp = rem(temp->name, false);
	temp->left = temp->right = NULL;
	node *newNode = new node;
	char *newName = new char[NAME_LENGTH];
	cin >> newName;
	newNode->name = newName;
	newNode->phonenum = temp->phonenum;
	delete[] temp->name;
	delete temp;
	addBinaryTree(tree.root, &newNode);
}

void removeTree(node *nptr){
	if(nptr == NULL)		return;
	removeTree(nptr->left);
	removeTree(nptr->right);
	delete nptr;
}

bool selectMenu(){
	int selection;
	cin >> selection;
	if		(selection == 1)	add();
	else if	(selection == 2)	search();
	else if	(selection == 3)	deleteContact();
	else if	(selection == 4)	update();
	else if	(selection == 5)	printContacts(tree.root);
	else if	(selection == 6)	return false;
	else						selectMenu();
	return true;
}

bool menu(){
	cout << "1) Add contact" << endl;
	cout << "2) Search contact" << endl;
	cout << "3) Delete contact" << endl;
	cout << "4) Update contact" << endl;
	cout << "5) Print contacts" << endl;
	cout << "6) Exit" << endl;
	return selectMenu();
}

int main(){
	tree.root = NULL;
	while(menu());
	removeTree(tree.root);
	return 0;
}