#include "stack.h"
#include "queue.h"

typedef char Plate;

struct ParkingPlace{
	Stack area[4];
	Queue temporary_place;
	Queue stacks;
	int area_capacity;
	int area_counter[4];

	void create(int);
	void add_car(Plate);
	void print();
	Plate give_car(Plate);
	void close();
};