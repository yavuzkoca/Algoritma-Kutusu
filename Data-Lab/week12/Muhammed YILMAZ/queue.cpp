#include <iostream>
#include <string.h>
#include "queue.h"

using namespace std;

void queue::create(){

	tepeEleman = NULL;
	tailEleman = NULL;
}

void queue::push(int tempDeger){

	qNode *ekle = new qNode;
	ekle->deger = tempDeger;
	ekle->prev = NULL;
	
	if (tepeEleman == NULL)
	{
		tepeEleman = ekle;
		tailEleman = ekle;
	}
	else
	{
		tailEleman->prev = ekle;
		tailEleman = ekle;
	}
}

bool queue::pull(){

	if(tepeEleman != NULL)
	{
		qNode *trash = tepeEleman;
		tepeEleman = tepeEleman->prev;
		delete trash;
		return true;
	}
	else
	{
		tailEleman = NULL;
		cout << "There is value in this queue " << endl;
		return false;
	}
}

void queue::show(){

	qNode *temp = tepeEleman;
	while(temp != NULL)
	{
		cout << temp->deger << " - ";
		temp = temp->prev;
	}
	cout << endl;
}

qNode queue::top(){

	return *tepeEleman;
}