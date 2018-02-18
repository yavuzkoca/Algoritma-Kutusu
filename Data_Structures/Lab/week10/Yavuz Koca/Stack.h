#ifndef STACK_H
#define STACK_H

typedef char StackDataType;
struct Node{
    StackDataType data;
    Node *next;
};

class Stack{
public:
    Stack();
    Node *head;
    void create();
    int max;
    int count;
    void close();
    void push(StackDataType);
    StackDataType pop();
    StackDataType top();
    bool is_empty();
};
#endif