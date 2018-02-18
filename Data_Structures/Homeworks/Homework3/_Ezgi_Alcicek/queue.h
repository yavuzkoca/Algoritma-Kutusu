#include <iostream>
#include "patient.h"

struct list{
	int size;
	patient *head = NULL;
	patient *last = NULL;
	bool enqueue(patient*);
	patient* dequeue();
	bool isEmpty();
	void create();
};

