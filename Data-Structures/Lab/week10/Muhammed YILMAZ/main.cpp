#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "car.h"
#include "park.h"
#include "tempArea.h"

using namespace std;

stPark park1;
stPark park2;
stPark park3;
stTempArea tempArea;

void create_areas();
bool pd_operation();
bool park_car(char *tempPlaka);
bool take_car(char *tempPlaka);
bool transport_car_to_other(int area, char *targetPlaka);
void print_all_area();
void exitt();

int main(int argc, char *argv[])
{
	create_areas();
	bool exit = true;
	while(exit == true)
	{
		exit = pd_operation();
		print_all_area();
	}
	exitt();
	return EXIT_SUCCESS;
}

void create_areas(){

	int capacity;
	cout << "Enter capacity of park areas: ";
	cin >> capacity;

	park1.create(capacity);
	park2.create(capacity);
	park3.create(capacity);
	tempArea.create();
}

bool pd_operation(){

	char operation;
	cout << endl << endl
		 << "\tPARKING SYSTEM 3.0" << endl
		 << "1 - Park the car" << endl
		 << "2 - Take the car" << endl
		 << "0 - Exit" << endl << endl
		 << "Enter your operation: ";
	cin >> operation;

	char plaka[20];
	switch (operation)
	{
		case '1':
			cout << "Enter license plate car: ";
			cin >> plaka;
			park_car(plaka);
			break;
		case '2':
			cout << "Enter license plate car: ";
			cin >> plaka;
			take_car(plaka);
			break;
		case '0':
			return false;
		default:
			cout << "Yanlış işlem seçtiniz." << endl;
	}
	return true;
}

bool park_car(char *tempPlaka){

	if(park1.push(tempPlaka) == true)
	{
		cout << "The car was parked in the 1st park area." << endl;
	}
	else if(park2.push(tempPlaka) == true)
	{
		cout << "The car was parked in the 2nd park area." << endl;
	}
	else if(park3.push(tempPlaka) == true)
	{
		cout << "The car was parked in the 3nd park area." << endl;
	}
	else 
	{
		cout << "All park areas are full. "
			 << "The car cannot parked." << endl;
		return false;
	}

	return true;
}

bool take_car(char *tempPlaka){

	if(park1.plaka_control(tempPlaka) == true)
	{
		cout << "The car is in the 1st park area." << endl;
		if(transport_car_to_other(1, tempPlaka) == true)
		{
			park1.pull();
			cout << "The car was taken from the 1st park area."
				 << endl;
		}
	}
	else if(park2.plaka_control(tempPlaka) == true)
	{
		cout << "The car is in the 2nd park area." << endl;
		if(transport_car_to_other(2, tempPlaka) == true)
		{
			park2.pull();
			cout << "The car was taken from the 2nd park area."
				 << endl;
		}
	}
	else if(park3.plaka_control(tempPlaka) == true)
	{
		cout << "The car is in the 3nd park area." << endl;
		if(transport_car_to_other(3, tempPlaka) == true)
		{
			park3.pull();
			cout << "The car was taken from the 3nd park area."
				 << endl;
		}
	}
	else 
	{
		cout << "The car could not found. "
			 << "This car is not here." << endl;
		return false;
	}
	while(tempArea.tepeEleman != NULL)
	{
		if(park_car(tempArea.top().plaka) == true)
		{
			tempArea.pull();
		}
		else
		{
			cout << "All park areas are full." << endl;
			return false;
		}
	}
}


bool transport_car_to_other(int area, char *targetPlaka){

	stPark *nowPark, *otherPark, *otherPark1, *otherPark2;
	if(area == 1)
	{
		nowPark = &park1;
		otherPark1 = &park2;
		otherPark2 = &park3;
	}
	else if(area == 2)
	{
		nowPark = &park2;
		otherPark1 = &park1;
		otherPark2 = &park3;
	}
	else if(area == 3)
	{
		nowPark = &park3;
		otherPark1 = &park1;
		otherPark2 = &park2;
	}
	else
	{
		cout << "There is not this park area." << endl;
		return false;
	}

	otherPark = otherPark1;
	while(strcmp(nowPark->top().plaka, targetPlaka) != 0)
	{
		if(otherPark->push(nowPark->top().plaka) == true)
		{
			nowPark->pull();
		}
		else if (otherPark == otherPark1)
		{
			otherPark = otherPark2;
		}
		else
		{
			while(strcmp(nowPark->top().plaka,
				 targetPlaka) != 0)
			{
				tempArea.push(nowPark->top().plaka);
				nowPark->pull();
			}
		}
	}

	return true;
}

void print_all_area(){

	stCar *temp1 = park1.tepeEleman, *temp2 = park2.tepeEleman, *temp3 = park3.tepeEleman;
	stCar *tempT = tempArea.tepeEleman;

	cout << "Area1\t\tArea2\t\tArea3\t\tTempArea" << endl;
	for (int i = 0;  park1.capacity > i; i++)
	{
		if (temp1 != NULL)
		{
			cout << temp1->plaka;
			temp1 = temp1->prev;
		}
		cout << "\t\t";
		if (temp2 != NULL)
		{
			cout << temp2->plaka;
			temp2 = temp2->prev;
		}
		cout << "\t\t";
		if (temp3 != NULL)
		{
			cout << temp3->plaka;
			temp3 = temp3->prev;
		}
		cout << "\t\t"; 
		if (tempT != NULL)
		{
			cout << tempT->plaka;
			tempT = tempT->prev;
		}
		cout << endl;
	}
}

void exitt(){

	while (park1.pull() == true);
	while (park2.pull() == true);
	while (park3.pull() == true);
	print_all_area();
	getchar();
	getchar();
}