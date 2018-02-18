#include <iostream>
#include <cstring>
#include <cstdio>
#include "List.h"

using namespace std;

List::List(){
    head = NULL;
    curr = NULL;
    temp = NULL;
}

void List::addData(char *name, char *number) {
    nodePtr n = new node;
    n->next = NULL;
    n->name = new char[strlen(name)];
    n->number = new char[strlen(number)];
    strcpy(n->name,name);
    strcpy(n->number,number);

    if(head != NULL){
        curr = head;
        while(curr->next != NULL && strcmp((curr->next)->name, n->name) < 0)
            curr = curr->next;

        temp = curr->next;
        curr->next = n;
        n->next = temp;
    }else
        head = n;

}

void List::printList() {
    curr = head;
    while(curr != NULL){
        cout << curr->name << endl;
        curr = curr->next;
    }
    cout << endl;
}

bool List::deleteRecord(char input[]){
    curr = head;
    temp = head;
    nodePtr delPtr = NULL;
    char ch;
    while(curr != NULL){
        if(strncmp(curr->name,input,strlen(input)) == 0){
            printf("We have found this record:\n");
            printf("%s %s\n",curr->name,curr->number);
            printf("Do you really want to delete this (Y/N)? ");
            cin >> ch;
            if(ch == 'Y' || ch == 'y'){
                delPtr = curr;
                curr = curr->next;
                temp->next = curr;
                delete delPtr;
                return true;
            }else{
                return false;
            }
        }
        temp = curr;
        curr = curr->next;
    }
    return false;
}

bool List::updateRecord(char input[]){
    curr = head;
    temp = head;

    nodePtr delPtr = NULL;
    char ch,name[30],number[15];
    while(curr != NULL){
        if(strncmp(curr->name,input,strlen(input)) == 0){
            printf("We have found this record:\n");
            printf("%s %s\n",curr->name,curr->number);
            printf("Do you really want to update this record (Y/N)? ");
            cin >> ch;
            if(ch == 'Y' || ch == 'y'){
                printf("Enter the name of the record\n");
                cin >> name;
                printf("Enter the number");
                cin >> number;
                delPtr = curr;
                curr = curr->next;
                temp->next = curr;
                addData(name,number);
                delete delPtr;
                return true;
            }else{
                return false;
            }
        }
        temp = curr;
        curr = curr->next;
    }
    return false;
}

void List::deleteAll() {
    curr = head;
    temp = head;
    while(curr != NULL){
        curr = curr->next;
        delete temp;
        temp = curr;
    }
}