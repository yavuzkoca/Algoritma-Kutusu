#include "parkingplace.h"
#include <string.h>
#include <iostream>

using namespace std;

typedef char Plate;

void ParkingPlace::create(int capacity){
	area_capacity = capacity;
	for(int i = 0; i < 4; ++i) { area[i].create(); area_counter[i] = 0; };
	temporary_place.create();
	stacks.create();
}

void ParkingPlace::add_car(Plate plate){
	if(area_counter[0] != area_capacity){
		area[0].push(plate);
		++area_counter[0];
	}
	else if(area_counter[1] != area_capacity){
		area[1].push(plate);
		++area_counter[1];
	}
	else if(area_counter[2] != area_capacity){
		area[2].push(plate);
		++area_counter[2];
	}
	else if(area_counter[3] != area_capacity){
		area[3].push(plate);
		++area_counter[3];
	}
	else{
		cout << "Couldn't add the car with the plate " << plate << endl;
		return;
	}
	cout << plate << " added." << endl;
}

void ParkingPlace::print(){
	cout << "####" << endl;
	for(int i = 0; i < 4; ++i) area[i].print();
}

Plate ParkingPlace::give_car(Plate plate){
	Plate temp;
	bool found = false;
	if(area_counter[0] != 0){
		while( !area[0].isEmpty() ){
			temp = area[0].pop();
			--area_counter[0];
			if( temp == plate ){
				found = true;
				break;
			}
			else{
				if(area_counter[1] != area_capacity){
					area[1].push(temp);
					++area_counter[1];
				}
				else if(area_counter[2] != area_capacity){
					area[2].push(temp);
					++area_counter[2];
				}
				else if(area_counter[3] != area_capacity){
					area[3].push(temp);
					++area_counter[3];
				}
				else{
					temporary_place.enqueue(temp);
				}
			}
		}
		while( !temporary_place.isEmpty() ){
			if(area_counter[0] != area_capacity){
				area[0].push(temporary_place.dequeue());
				++area_counter[0];
			}
			else if(area_counter[1] != area_capacity){
				area[1].push(temporary_place.dequeue());
				++area_counter[1];
			}
			else if(area_counter[2] != area_capacity){
				area[2].push(temporary_place.dequeue());
				++area_counter[2];
			}
			else if(area_counter[3] != area_capacity){
				area[3].push(temporary_place.dequeue());
				++area_counter[3];
			}
			else{
				cout << "Olmamasi gereken bir sey oldu." << endl;
			}
		}
		if(found){
			return temp;
		}
	}
	if(area_counter[1] != 0){
		while( !area[1].isEmpty() ){
			temp = area[1].pop();
			--area_counter[1];
			if( temp == plate ){
				found = true;
				break;
			}
			else{
				if(area_counter[0] != area_capacity){
					area[0].push(temp);
					++area_counter[0];
				}
				else if(area_counter[2] != area_capacity){
					area[2].push(temp);
					++area_counter[2];
				}
				else if(area_counter[3] != area_capacity){
					area[3].push(temp);
					++area_counter[3];
				}
				else{
					temporary_place.enqueue(temp);
				}
			}

		}
		while( !temporary_place.isEmpty() ){
			if(area_counter[1] != area_capacity){
				area[1].push(temporary_place.dequeue());
				++area_counter[1];
			}
			else if(area_counter[0] != area_capacity){
				area[0].push(temporary_place.dequeue());
				++area_counter[0];
			}
			else if(area_counter[2] != area_capacity){
				area[2].push(temporary_place.dequeue());
				++area_counter[2];
			}
			else if(area_counter[3] != area_capacity){
				area[3].push(temporary_place.dequeue());
				++area_counter[3];
			}
			else{
				cout << "Olmamasi gereken bir sey oldu." << endl;
			}
		}
		if(found){
			return temp;
		}
	}
	if(area_counter[2] != 0){
		while( !area[2].isEmpty() ){
			temp = area[2].pop();
			--area_counter[2];
			if( temp == plate ){
				found = true;
				break;
			}
			else{
				if(area_counter[0] != area_capacity){
					area[0].push(temp);
					++area_counter[0];
				}
				else if(area_counter[1] != area_capacity){
					area[1].push(temp);
					++area_counter[1];
				}
				else if(area_counter[3] != area_capacity){
					area[3].push(temp);
					++area_counter[3];
				}
				else{
					temporary_place.enqueue(temp);
				}
			}

		}
		while( !temporary_place.isEmpty() ){
			if(area_counter[2] != area_capacity){
				area[2].push(temporary_place.dequeue());
				++area_counter[2];
			}
			else if(area_counter[1] != area_capacity){
				area[1].push(temporary_place.dequeue());
				++area_counter[1];
			}
			else if(area_counter[0] != area_capacity){
				area[0].push(temporary_place.dequeue());
				++area_counter[0];
			}
			else if(area_counter[3] != area_capacity){
				area[3].push(temporary_place.dequeue());
				++area_counter[3];
			}
			else{
				cout << "Olmamasi gereken bir sey oldu." << endl;
			}
		}
		if(found){
			return temp;
		}
	}
	if(area_counter[3] != 0){
		while( !area[3].isEmpty() ){
			temp = area[3].pop();
			--area_counter[3];
			if( temp == plate ){
				found = true;
				break;
			}
			else{
				if(area_counter[0] != area_capacity){
					area[0].push(temp);
					++area_counter[0];
				}
				else if(area_counter[1] != area_capacity){
					area[1].push(temp);
					++area_counter[1];
				}
				else if(area_counter[2] != area_capacity){
					area[2].push(temp);
					++area_counter[2];
				}
				else{
					temporary_place.enqueue(temp);
				}
			}

		}
		while( !temporary_place.isEmpty() ){
			if(area_counter[3] != area_capacity){
				area[3].push(temporary_place.dequeue());
				++area_counter[3];
			}
			else if(area_counter[1] != area_capacity){
				area[1].push(temporary_place.dequeue());
				++area_counter[1];
			}
			else if(area_counter[2] != area_capacity){
				area[2].push(temporary_place.dequeue());
				++area_counter[2];
			}
			else if(area_counter[0] != area_capacity){
				area[0].push(temporary_place.dequeue());
				++area_counter[0];
			}
			else{
				cout << "Olmamasi gereken bir sey oldu." << endl;
			}
		}
		if(found){
			return temp;
		}
	}
	cout << "There is no cars in the park." << endl;
	return 0;
}

void ParkingPlace::close(){
	for(int i = 0; i < 4; ++i) area[i].close();
	temporary_place.close();
	stacks.close();
}