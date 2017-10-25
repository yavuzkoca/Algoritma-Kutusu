#include <iostream>
#include "Stack.h"

void Stack::create(){
    head = NULL;
}


void Stack::close(){
    Node *p;
    while (head){
        p = head;
        head = head->next;
        delete p;
    }
}


void Stack::push(StackDataType newdata){
    Node *newnode = new Node;
    newnode->data = newdata;
    newnode->next = head;
    head = newnode;
}


StackDataType Stack::pop(){
    Node *topnode;
    StackDataType temp;
    topnode = head;
    head = head->next;
    temp = topnode->data;
    delete topnode;
    return temp;
}

StackDataType Stack::top(){
    return head->data;
}


bool Stack::is_empty(){
    return head == NULL;
}
