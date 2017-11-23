#include <iostream>
#include <string.h>
#include "tempArea.h"

using namespace std;

void stTempArea::create(){

	tepeEleman = NULL;
	tailEleman = NULL;
}

void stTempArea::push(char *tempPlaka){

	stCar *ekle = new stCar;
	ekle->plaka = new char[20];
	strcpy(ekle->plaka, tempPlaka);
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

bool stTempArea::pull(){

	if(tepeEleman != NULL)
	{
		stCar *trash = tepeEleman;
		tepeEleman = tepeEleman->prev;
		delete [] trash->plaka;
		delete trash;
		return true;
	}
	else
	{
		tailEleman = NULL;
		cout << "There is no car in this park area " << endl;
		return false;
	}
}

void stTempArea::show(){

	stCar *temp = tepeEleman;
	while(temp != NULL)
	{
		cout << temp->plaka << endl;
		temp = temp->prev;
	}
}

stCar stTempArea::top(){

	return *tepeEleman;
}