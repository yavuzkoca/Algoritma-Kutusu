#ifndef C_C_TREE_H
#define C_C_TREE_H

struct phoneNode{
    char *phoneNum;
    phoneNode *next;
};

struct node {
    char *name;
    int data;
    phoneNode *head;
    node *left;
    node *right;
};

struct Tree {
    node *root;
    Tree();
    void print_in_order(node*);
    bool search(node*, char*);
    void add_node(node*,char*, char*);
    // node* add(node*, node*);
    void remove(char*);
    void update(char*, char*);
    node* newNode(node*);
    node* deleteAll(node*);
};


#endif //C_C_TREE_H
