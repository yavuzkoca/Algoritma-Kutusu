#include <iostream>
#include <cstdlib>
#include "List.h"

using namespace std;

List::List(){
    head = NULL;
    curr = NULL;
    temp = NULL;
}

void List::addNode(int data) {
    nodePtr n = new node;
    n->next = NULL;
    n->data = data;

    if(head != NULL){
        curr = head;
        while(curr->next != NULL)
            curr = curr->next;

        curr->next = n;
    }else
        head = n;

}

void List::addNodeToBeginning(int data){
    nodePtr n = new node;
    n->data = data;
    n->next = head;
    head = n;
}

void List::deleteNode(int data) {
    nodePtr delPtr = NULL;
    temp = head;
    curr = head;
    while(curr != NULL && curr->data != data){
        temp = curr;
        curr = curr->next;
    }
    if(curr == NULL)
        cout << data << " was not found" << endl;
    else{
        delPtr = curr;
        curr = curr->next;
        temp->next = curr;
        cout << "The value " << data << " has been deleted" << endl;
    }
    delete delPtr;
}

void List::printList() {
    curr = head;
    while(curr != NULL){
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}
