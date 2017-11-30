#include <iostream>
#include "Queue.h"

Queue::Queue(){
    max = 3;
    count = 0;
}

void Queue::create(){
    front = NULL; back = NULL;
}
void Queue::close(){
    QueueNode *p;
    while (front) {
        p = front;
        front = front->next;
        delete p;
    }
}
void Queue::enqueue(QueueDataType newdata){
    QueueNode *newnode = new QueueNode;
    newnode->data = newdata;
    newnode->next = NULL;
    if ( isempty() ) { // first element?
        back = newnode;
        front = back;
    }
    else {
        back->next = newnode;
        back = newnode;
    }
    count++;
}

QueueDataType Queue::dequeue() {
    QueueNode *topnode;
    QueueDataType temp;
    topnode = front;
    front = front->next;
    temp = topnode->data;
    delete topnode;
    count--;
    return temp;
}
bool Queue::isempty() {
    return front == NULL;
}