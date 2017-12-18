/*
cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << endl;
*/

#include <iostream>
#include <cstring>
#include "bst.h"
#include "node.h"

using namespace std;

void bst::create(){

	root = NULL;
	nodeCount = 0;
}

void bst::add(node *newNode){

	node *traverse = root;
	int comparison;
	bool added = false;

	if(root == NULL)
	{
		root = newNode;
		nodeCount++;
		return;
	}

	comparison = comparisonNodes(newNode, traverse);

	while(traverse && !added)
	{
		comparison = comparisonNodes(newNode, traverse);
		if(comparison < 0)
		{
			if(traverse->left)
			{
				traverse = traverse->left;
			}
			else 
			{
				traverse->left = newNode;
				nodeCount++;
				added = true;
			}
		}
		else if(comparison > 0)
		{
			if(traverse->right)
			{
				traverse = traverse->right;
			}
			else
			{
				traverse->right = newNode;
				nodeCount++;
				added = true;
			}
		}
		else 
		{
			ifSameNodeTitleHowAdd(newNode, traverse, &nodeCount);
			delete newNode;
			added = true;
		}
	}

	return;
}

void bst::add(char *addName, char *addPhoneNumber){

	node *newNode = new node;
	newNode->name = new char [LENGHT_NAME];
	strcpy(newNode->name, addName);
	newNode->phone = new phoneNode;
	newNode->phone->number = new char[LENGHT_NUMBER];
	newNode->phone->next = NULL;
	strcpy(newNode->phone->number, addPhoneNumber);
	newNode->right = NULL;
	newNode->left = NULL;
	
	add(newNode);
	return;
}

node *bst::search(const char * const degerS, node * const nodeS){

	if (!nodeS)
		return NULL;

	int comparison = comparisonValueForNode(degerS, nodeS);

	if(comparison < 0)
		return search(degerS, nodeS->left);
	else if(comparison > 0)
		return search(degerS, nodeS->right);
	else 
		return nodeS;
}

void bst::show(const node * const nodeS){

	if (!nodeS)
		return;

	show(nodeS->left);
	showNode(nodeS);
	show(nodeS->right);
}
void bst::showName(const node * const nodeS){

	if (!nodeS)
		return;

	showName(nodeS->left);
	cout << nodeS->name << endl;
	showName(nodeS->right);
}

bool bst::remove(char *valueS){

	node *traverse = root, *parent = root;
	bool found = false;
	int comparison;
	char direction = 'k';
	while(traverse && !found)
	{
		comparison = comparisonValueForNode(valueS, traverse);
		if(comparison < 0)
		{
			direction = 'l';
			parent = traverse;
			traverse = traverse->left;
		}
		else if(comparison > 0)
		{
			direction = 'r';
			parent = traverse;
			traverse = traverse->right;
		}
		else
		{
			found = true;
		}
	}
	if(found)
	{
		if (direction == 'l')
			remove(&parent->left);
		else if(direction == 'r')
			remove(&parent->right);
		else
			remove(&root);
	}
	else
		return false;

	phoneNode *trash = traverse->phone, *upTrash;
	while(trash)
	{
		upTrash = trash;
		trash = trash->next;
		delete [] upTrash->number;
		delete upTrash;
	}
	delete [] traverse->name;
	delete traverse;
	return true;

}

void bst::remove(node **p){
	node *r, *q; // used to find place for left subtree
	r = *p;
	if (r == NULL) // attempt to delete nonexistent node
		return;
	else if (r->right == NULL)
	{
		*p = r->left; // reattach left subtree
	}
	else if (r->left == NULL)
	{
		*p = r->right; // reattach right subtree
	}
	else 
	{ // neither subtree is empty
		for (q = r->right; q->left; q = q->left); // inorder successor
		q->left = r->left; // reattach left subtree
		*p = r->right;	// reattach right subtree
	}
}

bool bst::update(char *nameS){

	node *newNode = new node;
	copyNode(newNode, search(nameS, root));
	if(!newNode)
	{
		delete newNode;
		return false;
	}

	char newName[LENGHT_NAME];
	cout << "Enter new name: ";	cin >> newName;
	strcpy(newNode->name, newName);

	remove(nameS);
	add(newNode);

	return true;
}

void copyNode(node *toNode, node *fromNode){

	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << endl;
	if(!fromNode)
	{
		toNode = NULL;
		return;
	}

	toNode->name = new char[LENGHT_NAME];
	strcpy(toNode->name, fromNode->name);
	toNode->phone = new phoneNode;
	copyPhoneNumbers(toNode->phone, fromNode->phone);
	toNode->left = NULL;
	toNode->right = NULL;
}

bool copyPhoneNumbers(phoneNode *toPhone, phoneNode *fromPhone){

	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << endl;
	if(!fromPhone)
		return false;

	toPhone->number = new char[LENGHT_NUMBER];
	strcpy(toPhone->number, fromPhone->number);
	toPhone->next = new phoneNode;
	//toPhone->next = NULL;
	if(!copyPhoneNumbers(toPhone->next, fromPhone->next))
	{
		delete toPhone->next; 
		toPhone->next = NULL;
	}
	return true;
}

void bst::close(node *nodeS){

	if (!nodeS)
		return;

	close(nodeS->left);
	cout << nodeS->name << " siliniyor." << endl;
	remove(nodeS->name);
	close(nodeS->right);
}
/*
bool bst::removeDown(node *nodeS){
	
	if (!nodeS)
		return true;

	if(nodeS->left && nodeS->right)
		removeDown(nodeS);
	
	if(nodeS->left)
		remove(nodeS->left);
	if(!nodeS->right)
		remove(nodeS->right);

	if(!nodeS->left && !nodeS->right)
		return remove(nodeS);
}

void bst::close(){

	if (!nodeS)
		return;

	show (nodeS->left);
	showNode (nodeS);
	show (nodeS->right);
}
*/