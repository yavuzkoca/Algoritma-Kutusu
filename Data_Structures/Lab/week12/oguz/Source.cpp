
#include <iostream>
#include "Header.h"

using namespace std;

int main()
{
	int size;
	cin >> size;
	node* root = create_Tree(size);
	cout << "....\npre... ";
	printPreorder(root);
	cout << "....\nin... ";
	printInorder(root);
	cout << "....\npost... ";
	printPostorder(root);
	cout << "....\nmax... ";
	cout << findMax(root, root->data);
	cout << "....\nmin... ";
	cout << findMin(root, root->data);
	cout << "....\nnode... ";
	cout << findNumNode(root);
	cout << "....\nleaf... ";
	cout << findNumLeaf(root);
	cout << "....\ndepth... ";
	cout << calculateDepth(root);
	cout << "....\nsum... ";
	cout << calculateSum(root, root->data);
	cout << "....\navg... ";
	cout << calculateAverage(root, root->data);

	getchar();
	getchar();
	removeTree(root);
	return 0;
}