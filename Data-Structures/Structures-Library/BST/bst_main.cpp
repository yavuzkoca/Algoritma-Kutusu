#include <iostream>
#include "BST.h"
#define endl std::cout << endl;

using namespace std;

int main(){
    BST bst;
    bst.addLeaf(5);
    bst.addLeaf(10);
    bst.addLeaf(9);
    bst.addLeaf(1);
    bst.addLeaf(3);
    bst.printInOrder();endl
    bst.removeNode(5);
    bst.printInOrder();endl
    bst.removeNode(1);
    bst.printInOrder();endl
    return 0;
}
