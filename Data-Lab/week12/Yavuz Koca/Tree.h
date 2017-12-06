#ifndef C_C_TREE_H
#define C_C_TREE_H

struct node {
    int number;
    node *left;
    node *right;
};

struct Tree {
    node *root;
    Tree();
    void print_pre_order(node*);
    void print_post_order(node*);
    void print_in_order(node*);
    node* add_node(int[],node*,int,int);
    node* remove(node*);
    int findMax(node*);
    int findMin(node*);
    int findNumNode(node*);
    int findNumLeaf(node*);
    int calculateDepth(node*);
    int calculateSum(node*);
    int calculateAverage(node*,int);
};


#endif //C_C_TREE_H
