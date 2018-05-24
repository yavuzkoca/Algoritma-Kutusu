#include <iostream>

#include "tree.h"

using namespace std;

int main(){

	Tree t;
	cout << endl << "Original array: ";
	t.createTree(20);
	cout << endl;
	cout << "Inorder: ";
	printInorder(t.root);
	cout << endl << endl;
	cout << "Preorder: ";
	printPreorder(t.root);
	cout << endl << endl;
	cout << "Postorder: ";
	printPostorder(t.root);
	cout << endl;

	cout << endl << "Find Max: " << t.findMax() << endl;
	cout << endl << "Find Min: " << t.findMin() << endl;
	cout << endl << "Num node: " << t.findNumNode() << endl;
	cout << endl << "Num leaf: " << t.findNumLeaf() << endl;
	cout << endl << "Depth: " << t.calculateDepth() << endl;
	cout << endl << "Sum: " << t.calculateSum() << endl;
	cout << endl << "Average: " << t.calculateAverage() << endl;

	removeTree(t.root);

	return 0;
}