#ifndef PARK_H
#define PARK_H
#include "car.h"

struct stPark
{
	int capacity;
	int nowCarNumber;
	stCar *tepeEleman;
	void create(int tempCapacity);
	bool push(char *tempPlaka);
	bool pull();
	void show();
	stCar top();
	bool plaka_control(char *tempPlaka);
};

#endif