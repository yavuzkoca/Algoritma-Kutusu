#include <iostream>
#include <cstdio>
#include "Stack.h"
#include "Queue.h"
#include "Functions.h"

#define STACKSIZE 2

using namespace std;

bool operation(char);
bool addCar(char);
void printStackList();
bool removeCar();

Stack s[STACKSIZE];
Stack temp;
Queue q;
int totalCar;

int main(){
    printWelcome();
    bool proceed = true;
    char option;
    while(proceed){
        printMenu();
        cin >> option;
        proceed = operation(option);
    }
    return 0;
}

bool operation(char op){
    if(op >= 'a' && op <= 'z')
        op = op - 'a' + 'A';

    if(op == 'E')
        return false;
    else if(op == 'A'){
        char name;
        printf("\nEnter the name of the car\n\n");
        cin >> name;
        if(addCar(name)){
            printf("\nCar has been parked successfully\n\n");
        }else{
            printf("\nNot enough place to park it\n\n");
        }
    }
    else if(op == 'L')
        printStackList();
    else if(op == 'R')
        removeCar();

    return true;
}

bool addCar(char name){

    for(int i=0; i<STACKSIZE; i++){
        if(s[i].count < s[i].max){
            s[i].push(name);
            totalCar++;
            return 1;
        }
    }

    return 0;
}

void printStackList(){
    for(int i=0; i<STACKSIZE; i++){
        printf("\n------------------\n");
        while(!s[i].is_empty()){
            temp.push(s[i].top());
            printf("| %c",s[i].top());
            s[i].pop();
        }
        printf("\n");
        while(!temp.is_empty()){
            s[i].push(temp.top());
            temp.pop();
        }
    }
}

bool removeCar(){
    printf("\nEnter the character of the car you want to remove\n\n");
    char c;
    cin >> c;
    bool lastCar;
    for(int i=0; i<STACKSIZE; i++){
        lastCar = 1;
        while(!s[i].is_empty() && lastCar){
            if(s[i].top() == c){
                s[i].pop();
                printf("\nCar has been removed!\n\n");
                while(!q.isempty()){
                    addCar(q.dequeue());
                }
                return 1;
            }
            else{
                char currentCar = s[i].top();
                s[i].pop();
                if(s[i].is_empty()){ // Araba son elemansa, diğer stacklere atma
                    s[i].push(currentCar);
                    lastCar = 0;
                }else{
                    s[i].push(currentCar);
                    bool emptySpace = 0;
                    for(int j=0; j<STACKSIZE; j++){ // Stacklerde boş yer ara
                        if(j == i) continue;
                        if(s[j].count < s[j].max){
                            emptySpace = 1;
                            s[j].push(s[i].top());
                            s[i].pop();
                            break;
                        }
                    }
                    if(!emptySpace){
                        q.enqueue(s[i].top());
                        s[i].pop();
                    }
                }
            }
        }
    }
    printf("\nThis car is not in this park\n\n");
    return 0;
}