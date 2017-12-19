#include <iostream>
#include "phonetree.h"

using namespace std;

void Tree::create() {
	root = NULL; // create empty tree
	nodecount = 0; // initialize nodecount to 0
}

void Tree::close() {
	emptytree(root);
}

void Tree::emptytree(Phone_node *p) {
	if (p) {
		if (p->left != NULL) {
			emptytree(p->left);
			p->left = NULL;
		}
		if (p->right != NULL) {
			emptytree(p->right);
			p->right = NULL;
		}
		p->numz.close();
		delete p;
	}
}

int Tree::search(char *search_name) {
	Phone_node *traverse;
	traverse = root;
	int countfound = 0;
	bool all = false;
	if (search_name[0] == '*')
		all = true;
	if (all) {
		traverse_inorder(root);
		countfound++;
	}
	else { // single record search
		while (traverse && !countfound) {
			int comparison =
				strcmp(search_name, traverse->name);
			if (comparison < 0)
				traverse = traverse->left;
			else if (comparison > 0)
				traverse = traverse->right;
			else { // if names are equal, record found
				cout << traverse->name << " ";
				traverse->numz.list();
				cout << endl;
				countfound++;
			}
		}
	}
	return countfound;
}

void Tree::traverse_inorder(Phone_node *p) {
	if (p){
		traverse_inorder(p->left);
		cout << p->name << " ";
		p->numz.list();
		cout << endl;
		traverse_inorder(p->right);
	}
}

void Tree::add(Temp_node *toadd) {
	Phone_node *traverse, *newnode;
	traverse = root;
	int comparison;
	bool added = false;
	newnode = new Phone_node;
	strcpy(newnode->name, toadd->name);
	newnode->numz.create();
	newnode->numz.add_num(toadd->phonenum);
	newnode->left = NULL;
	newnode->right = NULL;
	if (root == NULL){
		//first node being added
		root = newnode;
		nodecount++;
		return;
	}
	while ((traverse != NULL) && (!added)){
		comparison = strcmp(newnode->name, traverse->name);
		if (comparison < 0) {
			if (traverse->left != NULL)
				traverse = traverse->left;
			else {
				traverse->left = newnode;
				added = true;
			}
		}
		else if (comparison > 0) {
			if (traverse->right != NULL)
				traverse = traverse->right;
			else {
				traverse->right = newnode;
				added = true;
			}
		}
		else{
			traverse->numz.add_num(toadd->phonenum);
			added = true;
		}
			
	}
	if (added) nodecount++;
}
Phone_node* Tree::rem(char *remove_name){
	Phone_node *traverse, *parent=NULL;
	traverse = root;
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
			return remove(&parent->left);
		else if(direction == 'r')
			return remove(&parent->right);
		else remove(&root);
	}
	else
		cout << "Could not find"
		<< "record toremove.\n";
}

Phone_node* Tree::remove(Phone_node **p){
	Phone_node *r, *q; // used to find place for left subtree
	r = *p;
	if (r == NULL) // attempt to delete nonexistent node
		return NULL;
	else if (r->right == NULL) {
		*p = r->left; // reattach left subtree
		nodecount--;
		return r;
	}
	else if (r->left == NULL) {
		*p = r->right; // reattach right subtree
		nodecount--;
		return r;
	}
	else { // neither subtree is empty
		for (q = r->right; q->left; q = q->left); // inorder successor
		q->left = r->left; // reattach left subtree
		*p = r->right; // reattach right subtree
		nodecount--;
		return r;
	}
}

void num_list::add_num(char toadd[PHONENUM_LENGTH]){
	num_node *p = new num_node;
	strcpy(p->phonenum, toadd);
	p->next = NULL;
	if (isempty())
		head = p;
	else{
		num_node *q = head;
		while (q->next != NULL){
			q = q->next;
		}
		q->next = p;
	}
}

bool num_list::isempty(){
	return head == NULL;
}

void num_list::create(){
	head = NULL;
}

void num_list::close(){
	num_node *p = head;
	num_node *t;
	while (p){
		t = p;
		p = p->next;
		delete t;
	}
}

void num_list::list(){
	num_node *p = head;
	while (p){
		cout << p->phonenum << " ";
		p = p->next;
	}
}

void Tree::update(char old[NAME_LENGTH], char neu[NAME_LENGTH]){
	Phone_node *newnode = rem(old);
	Phone_node *traverse;

	newnode->left = NULL;
	newnode->right = NULL;
	strcpy(newnode->name, neu);

	traverse = root;
	int comparison;
	bool added = false;
	
	if (root == NULL){
		//first node being added
		root = newnode;
		nodecount++;
		return;
	}
	while ((traverse != NULL) && (!added)){
		comparison = strcmp(newnode->name, traverse->name);
		if (comparison < 0) {
			if (traverse->left != NULL)
				traverse = traverse->left;
			else {
				traverse->left = newnode;
				added = true;
			}
		}
		else if (comparison > 0) {
			if (traverse->right != NULL)
				traverse = traverse->right;
			else {
				traverse->right = newnode;
				added = true;
			}
		}
	}
	if (added) nodecount++;
}

void Tree::del(char *remove_name){
	Phone_node *x = rem(remove_name);
	x->numz.close();
	delete x;
}