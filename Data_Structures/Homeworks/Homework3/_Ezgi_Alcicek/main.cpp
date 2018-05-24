#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include "queue.h"

/*
BLG233 - Assignment3
Ezgi Alçiçek
150160032
*/

using namespace std;
int time = 0;
struct list red, yellow, green;
int included_patient = 0;

bool readFile() {
	string line;

	ifstream file;
	file.open("patientsInfo.txt");
	if (!file.is_open()) cout << "file cannot open." << endl; 

	for(int i = 0; i<included_patient; i++ )
		getline(file, line); //ignore the head

	if (!getline(file, line).good()) return false;

	while (getline(file, line)) {
		patient *newpatient = new patient;

		stringstream ss(line);
		ss >> newpatient->name >> newpatient->arrive >> newpatient->treatment >> newpatient->code;
		newpatient->arrive = (int)newpatient->arrive; newpatient->treatment = (int)newpatient->treatment;
		
		if (newpatient->arrive <= time) {
			if (strncmp(newpatient->code, "RED", 3) == 0) {
				newpatient->codenumber = 1; 
				red.enqueue(newpatient);
				included_patient++;
			}
			else if (strncmp(newpatient->code, "YELLOW", 6) == 0) {
				newpatient->codenumber = 2;
				yellow.enqueue(newpatient);
				included_patient++;
			}	
			else {
				newpatient->codenumber = 3;
				green.enqueue(newpatient);
				included_patient++;
			}
		}
	}
	file.close();
	return true;
}

patient* sirakimde() {
	if (readFile() || !red.isEmpty() || !yellow.isEmpty() || !green.isEmpty()) {
		if (red.head != NULL && red.head->arrive <= time)
			return red.dequeue();
		else if (yellow.head != NULL && yellow.head->arrive <= time)
			return yellow.dequeue();
		else if (green.head != NULL && green.head->arrive <= time)
			return green.dequeue();
		else {
			time++;
			cout << time << ". time slice There is no patient. " << endl;
			return sirakimde();
		}
	}
	else return NULL;
}

int doctor(patient* curr) {
	if (curr == NULL) return 0;
	int sure = curr->codenumber;
	if(curr->treatment < sure) sure = curr->treatment;
	int e = time + sure - 1;
	for (; time <= e; time++)
		cout << time + 1 << ". time slice " << curr->name << endl;

	curr->treatment -= sure;
	if (curr->codenumber < 3) curr->codenumber++;

	readFile();
	if (curr->codenumber == 1 && curr->treatment > 0) red.enqueue(curr);
	else if (curr->codenumber == 2 && curr->treatment > 0) yellow.enqueue(curr);
	else if (curr->codenumber == 3 && curr->treatment > 0) green.enqueue(curr);

	else delete curr;
	return 1;
}

int main() {
	while (doctor(sirakimde()));
	getchar();
}
