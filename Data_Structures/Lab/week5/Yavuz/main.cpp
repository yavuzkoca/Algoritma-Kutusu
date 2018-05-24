#include <cstdio>
#include <cstring>
#include <iostream>
#include "List.h"
#include "Functions.h"

using namespace std;

bool operation(char);
void add();
void deleteRecord();
void search();
void update();

List list;

int main(){
    printWelcome();
    bool proceed = true;
    char option;
    while(proceed){
        printMenu();
        cin >> option;
        proceed = operation(option);
    }
    bye();
    list.deleteAll();
    return 0;
}

bool operation(char op){
    if(op >= 'a' && op <= 'z')
        op = op - 'a' + 'A';

    if(op == 'E')
        return false;
    else if(op == 'A')
        add();
    else if(op == 'L')
        list.printList();
    else if(op == 'D')
        deleteRecord();
    else if(op == 'S'){}
        //search();
    else if(op == 'U')
        update();

    return true;
}

void add(){
    char temp[30];
    char *name,*number;
    printf("Enter the name\n");
    cin >> temp;
    name = new char[strlen(temp)];
    strcpy(name,temp);
    printf("Enter the number\n");
    cin >> temp;
    number = new char[strlen(temp)];
    strcpy(number,temp);
    list.addData(name,number);
    printf("\nThis contact has been added\n");
    delete[] name;
    delete[] number;
}

void deleteRecord(){
    char input[30];
    printf("Enter the name of the record you want to delete\n");
    cin >> input;
    if(list.deleteRecord(input))
        printf("\nRecord has been deleted\n");
    else
        printf("\nOops! We couldn't delete this record for some reasons\n");
}

/*void search(){
    char input[30];
    printf("Enter the name of the record you want to search");
}*/

void update(){
    char input[30];
    printf("Enter the name of the record you want to update\n");
    cin >> input;
    if(list.updateRecord(input))
        printf("\nRecord has been updated\n");
    else
        printf("\nOops! We couldn't update this record for some reasons\n");
}
