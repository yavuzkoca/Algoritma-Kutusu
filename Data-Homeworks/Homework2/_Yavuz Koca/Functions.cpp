#include "Functions.h"
#include "List.h"
#include <iostream>
#include <cstdio>

void printWelcome(){
    printf("\n!!!Welcome to Email Generator Application!!!\n");
}

void printMenu(){
    printf("\nSelect an operation\n");
    printf("A: Add New Student\n");
    printf("I: Insert All Students From the File\n");
    printf("L: List All Students\n");
    printf("K: List Students with given Surname\n");
    printf("D: Delete Surname Node\n");
    printf("S: Delete Student\n");
    printf("U: Update Student\n");
    printf("W: Write to File\n");
    printf("E: Exit\n\n");
}

void bye(){
    printf("\nThank you for using this application. Bye Bye..\n\n");
}