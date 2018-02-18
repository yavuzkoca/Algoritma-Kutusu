#ifndef C_C_LIST_H
#define C_C_LIST_H

class List{
private:
    typedef struct node{
        int data;
        node * next;
    }*nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;
public:
    List();
    void addNode(int data);
    void addNodeToBeginning(int data);
    void deleteNode(int data);
    void printList();
};

#endif
