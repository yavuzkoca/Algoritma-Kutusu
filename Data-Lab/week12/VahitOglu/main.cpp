#include <iostream>

#include "tree.h"

using namespace std;

int main(){

	Tree t;
	t.createTree(10);
	printInorder(t.root);
	cout << endl;
	printPreorder(t.root);
	cout << endl;
	printPostorder(t.root);

	cout << endl << t.calculateSum() << endl;
	cout << endl << t.calculateAverage() << endl;

	removeTree(t.root);

	return 0;
}