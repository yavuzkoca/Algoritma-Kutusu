#ifndef ALGORITMA_KUTUSU_BST_H
#define ALGORITMA_KUTUSU_BST_H

class BST {
private:
    struct node
    {
        int num;
        node* left;
        node* right;
    };
    node* _root;

    void _addLeaf(int num, node* ptr);
    node* _createLeaf(int num);
    void _printInOrder(node* ptr);
    void _removeNode(int num, node* parent);
    void _removeRootMatch();
    int _findSmallest(node* ptr);
    void _removeMatch(node* parent, node* match, bool left);
public:
    BST();
    void addLeaf(int num);
    void printInOrder();
    void removeNode(int num);

};

#endif
