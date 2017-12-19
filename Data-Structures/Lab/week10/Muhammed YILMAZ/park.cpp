#include <iostream>
#include <string.h>
#include "park.h"

using namespace std;

void stPark::create(int tempCapacity){

	tepeEleman = NULL;
	capacity = tempCapacity;
	nowCarNumber = 0;
}

bool stPark::push(char *tempPlaka){

	if(nowCarNumber < capacity)
	{	
		stCar *ekle = new stCar;
		ekle->plaka = new char[20];
		strcpy(ekle->plaka, tempPlaka);
		ekle->prev = tepeEleman;

		tepeEleman = ekle;
		nowCarNumber++;
		return true;
	}
	else
	{
		return false;
	}
}

bool stPark::pull(){

	if(tepeEleman != NULL)
	{
		stCar *trash = tepeEleman;
		tepeEleman = tepeEleman->prev;
		delete [] trash->plaka;
		delete trash;
		nowCarNumber--;
		return true;
	}
	else
	{
		cout << "There is no car in this park area " << endl;
		return false;
	}
}

void stPark::show(){

	stCar *temp = tepeEleman;
	while(temp != NULL)
	{
		cout << temp->plaka << endl;
		temp = temp->prev;
	}
}

stCar stPark::top(){

	return *tepeEleman;
}

bool stPark::plaka_control(char *controlPlaka){

	stCar *temp = tepeEleman;
	while(temp != NULL)
	{
		if(strcmp(controlPlaka, temp->plaka) == 0)
		{
			return true;
		}
		temp = temp->prev;
	}
	return false;
}