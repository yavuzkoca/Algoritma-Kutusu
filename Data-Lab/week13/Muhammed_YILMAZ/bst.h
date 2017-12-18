#ifndef BST_H
#define BST_H
#include "node.h"

struct bst
{
	node *root;
	void create();//
	void add(char *, char *);//
	void add(node *);
	bool remove(char *);
	void remove(node **);
	bool removeDown(node *);//???
	node *search(const char * const, node * const);//
	bool update(char *);
	void show(const node * const);//
	void showName(const node * const);//
	void close(node *);
	int nodeCount;
};

void copyNode(node *, node *);
bool copyPhoneNumbers(phoneNode *, phoneNode *);
#endif