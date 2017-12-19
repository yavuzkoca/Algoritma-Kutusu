#ifndef NODE_H
#define NODE_H

#define LENGHT_NAME 20
#define LENGHT_NUMBER 12

struct phoneNode
{
	char *number;
	phoneNode *next;
};

struct node
{
	char *name;
	phoneNode *phone;
	node *left;
	node *right;
};

int comparisonNodes(const node * const, const node * const);
int comparisonValueForNode(const char * const, const node * const);
void ifSameNodeTitleHowAdd(node *, node *, int *);
void showNode(const node * const);
#endif