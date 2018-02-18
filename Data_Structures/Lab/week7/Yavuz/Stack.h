#ifndef STACK_H
#define STACK_H

typedef char StackDataType;
struct Node{
    StackDataType data;
    Node *next;
};

struct Stack{
    Node *head;

    void create();
    void close();
    void push(StackDataType);
    StackDataType pop();
    StackDataType top();
    bool is_empty();
};
#endif