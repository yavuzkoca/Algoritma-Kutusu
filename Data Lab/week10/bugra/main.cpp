#include "parkingplace.h"

#include <iostream>
#include <random>


using namespace std;

int main(){

	const int N = 3;

	ParkingPlace bugras_house;
	bugras_house.create(N);

	bugras_house.add_car('A');
	bugras_house.add_car('B');
	bugras_house.add_car('C');
	bugras_house.add_car('D');
	bugras_house.add_car('E');
	bugras_house.add_car('F');
	bugras_house.add_car('G');
	bugras_house.add_car('H');
	bugras_house.add_car('I');
	bugras_house.add_car('J');
	bugras_house.add_car('K');
	bugras_house.add_car('L');

	char C;
	bugras_house.print();
	while(1){
		cin >> C;
		cout << bugras_house.give_car(C) << endl;
		bugras_house.print();
	}

	bugras_house.close();
}