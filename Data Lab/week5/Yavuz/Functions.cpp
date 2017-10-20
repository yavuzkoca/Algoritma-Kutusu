#include "Functions.h"
#include "List.h"
#include <iostream>
#include <cstdio>

void printWelcome(){
    printf("\n!!!Welcome to Phone Book Application!!!\n");
}

void printMenu(){

    printf("Select an operation\n");
    printf("A: Add New Record\n");
    printf("L: List All Records\n");
    printf("D: Delete A Record\n");
    printf("S: Search A Record\n");
    printf("E: Exit\n\n");
}

void bye(){
    printf("\nThank you for using this application. Bye Bye..\n");
}