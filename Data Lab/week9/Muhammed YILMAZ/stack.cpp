#include <iostream>
#include <stdio.h>
#include "stack.h"

using namespace std;

void stack::create(){
	tepeEleman = NULL;
}

void stack::push(stackKonum *ekle){

	ekle->prev = tepeEleman;
	tepeEleman = ekle;
}

void stack::pull(){

	if(tepeEleman != NULL)
	{
		stackKonum *trash = tepeEleman;
		tepeEleman = tepeEleman->prev;
		delete trash;
	}
}

stackKonum stack::top(){

	return *tepeEleman;
}

void stack::show(FILE *dg){

	stackKonum *temp = tepeEleman;
	for (int i = 0; temp != NULL; ++i)
	{
		fprintf(dg, "row: %d\tcolumn: %d\n", temp->row, temp->col);
		temp = temp->prev;
	}
}
