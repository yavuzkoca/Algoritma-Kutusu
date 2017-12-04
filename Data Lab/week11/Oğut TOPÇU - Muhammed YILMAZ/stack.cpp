#include <iostream>
#include "stack.h"

using namespace std;

void stack::create(){
	tepeEleman = NULL;
}

void stack::push(int y, int x){

	coordinate *ekle = new coordinate;
	ekle->y = y;
	ekle->x = x;
	ekle->prev = tepeEleman;
	tepeEleman = ekle;
}

void stack::pull(){

	if(tepeEleman != NULL)
	{
		coordinate *trash = tepeEleman;
		tepeEleman = tepeEleman->prev;
		delete trash;
	}
}

coordinate *stack::top(){

	return tepeEleman;
}

void stack::show(){

	coordinate *temp = tepeEleman;
	for (int i = 0; temp != NULL; ++i)
	{
		cout << "X -> " << temp->x << "\tY -> " << temp->y << endl;
		temp = temp->prev;
	}
}