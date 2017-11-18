#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
	Tree tree;
	node *root = NULL;
	root = tree.add(root, 5);
	tree.add(root, 2);
	tree.add(root, 3);
	tree.add(root, 1);
	tree.add(root, 7);
	tree.add(root, 13);
	tree.add(root, 11);
	tree.add(root, 20);
	tree.add(root, 0);
	tree.add(root, 4);
	tree.print(root);
	getchar();

	return 0;
}