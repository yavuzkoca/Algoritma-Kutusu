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
    printf("B: List All Records Backward\n");
    printf("F: List All Records Forward\n");
    printf("D: Delete A Record\n");
	printf("N: Delete A Number\n");
    printf("S: Search A Record\n");
	printf("U: Update Name\n");
	printf("Y: Update Number\n");
    printf("E: Exit\n\n");
}

void bye(){
    printf("\nThank you for using this application. Bye Bye..\n");
}