#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "patient_operations.h"

using namespace std;

/*****************************************************************************/

int partition(DataType **arr, int beg, int end){

	srand(time(NULL));

	int pivot_index = beg + rand() % (end - beg);
	DataType pivot = (*arr)[pivot_index];

	int lil, big;
	DataType temp;

	(*arr)[pivot_index] = (*arr)[beg];
	(*arr)[beg] = pivot;

	lil = beg + 1;
	big = end;

	while(lil != big){
		if((*arr)[lil].arriving_time < pivot.arriving_time){
			++lil;
		}
		else{
			temp = (*arr)[lil];
			(*arr)[lil] = (*arr)[big];
			(*arr)[big] = temp;
			--big;
		}
	}
	if((*arr)[lil].arriving_time > pivot.arriving_time){
		--big;
		--lil;
	}
	(*arr)[beg] = (*arr)[lil];
	(*arr)[lil] = pivot;
	return lil;
}

void qckSort(DataType **arr, int beg, int end){
	if(beg < end){
		int pivot_index = partition(arr, beg, end);
		qckSort(arr, beg, pivot_index - 1);
		qckSort(arr, pivot_index + 1, end);
	}
}

/* The quicksort function implemented by me, actually probably the input will be given sorted but for the program
   to run more robustly I am sorting the patients by arriving time and my program structure is based on this fact. */

int string_to_int(const string &toint){
	int number = 0;
	for(int i = 0; toint[i] != '\0'; ++i){ number = number * 10 + toint[i] - '0'; }
	return number;
} // Takes a string and converts it into an integer

ostream& operator<<(ostream& os, const Patient &patient){
	os << patient.id << " " << patient.arriving_time << " " << patient.treatment_time << " " << patient.complaint;
	return os;
} // Printing patients is not necessary for the given homework but for testing I overloaded << operator to print patients

int read_patients(Patient **patient_list, const char *PATH){
	ifstream patient_file;
	istringstream ss;
	string line, temp_patient_name, temp_complaint, token;


	int number_of_lines = 0;
	patient_file.open(PATH);
	if(patient_file.is_open()){
		getline(patient_file, line);
		while(!patient_file.eof()){
			getline(patient_file, line);
			++number_of_lines;
		}
		patient_file.clear();
		patient_file.seekg(0);

		// I first figure how many lines are there to create the patient array in the exact size

		*patient_list = new Patient[number_of_lines];
		getline(patient_file, line);
		for(int i = 0; !patient_file.eof(); ++i){
			getline(patient_file, line);

			ss.str(line);
			ss >> temp_patient_name;
			ss >> (*patient_list)[i].arriving_time;
			ss >> (*patient_list)[i].treatment_time;
			ss >> temp_complaint;
			ss.clear();

			ss.str(temp_patient_name);
			getline(ss, token, 't');
			getline(ss, token, 't');
			getline(ss, token, 't');
			ss.clear();

			(*patient_list)[i].id = string_to_int(token);
			if( temp_complaint.compare("RED") == 0 ) (*patient_list)[i].complaint = RED;
			else if( temp_complaint.compare("YELLOW") == 0 ) (*patient_list)[i].complaint = YELLOW;
			else if( temp_complaint.compare("GREEN") == 0 ) (*patient_list)[i].complaint = GREEN;
		} // This for loop does the actual reading from the file

		patient_file.close();
	}
	return number_of_lines; // Also the number of patients in the text file is returned
}

void print_patients(Patient *patient_list, int number_of_patients){
	for(int i = 0; i < number_of_patients; ++i){
		cout << patient_list[i] << endl;
	}
} // Prints the patiens in the array using overloaded << operator

void run_hospital(Queue &red, Queue &yellow, Queue &green, Patient **patient_list, int number_of_patients){
	int time = 0;
	red.create(); yellow.create(); green.create();
	qckSort(patient_list, 0, number_of_patients - 1); // Sort the patient list by arriving time

	for(int i = 0; i < number_of_patients; ++i){
		if( time == (*patient_list)[i].arriving_time ){
			if( (*patient_list)[i].complaint == RED ) red.enqueue( (*patient_list)[i] );
			else if( (*patient_list)[i].complaint == YELLOW ) yellow.enqueue( (*patient_list)[i] );
			else if( (*patient_list)[i].complaint == RED ) green.enqueue( (*patient_list)[i] );
		}
		else break;
	} // For the time zero, adds the patients to the queues, using the fact that the patients are sorted
	  // we can break the loop after time didn't match with a patient because after that no smaller time will come
	  // in the array.

	Patient temp; // After dequeue we use this to hold a patient
	int minimum_treatment_checker = 0; // This is used to check if the minimum treatment is satisfied

	while( !(red.isEmpty() && yellow.isEmpty() && green.isEmpty() && time > (*patient_list)[number_of_patients - 1].arriving_time) ){

	// This is the loop where the hospital actually runs
	// The while loop's condition is simple, if no one is in any queue and also time past the maximum time when someone will arrive
	// This means the simulation does not need to run anymore so the loop ends

		++time; // Time passes

		if( !red.isEmpty() && minimum_treatment_checker == 0){
		// If there is no one who didn't satisfy the minimum treatment condition and
		// there are people in the red queue then take them to treatment
			temp = red.dequeue(); // Take the waiting patient
			--temp.treatment_time; // Treat for 1 unit time
			if(temp.treatment_time != 0) temp.complaint = YELLOW; // If patient is not completely treated
			else 						 temp.complaint = GRAY; // else GRAY means the patient will be released
			cout << time << ".time slice Patient" << temp.id << endl; // Report the situation
		}

		else if( !yellow.isEmpty() || (temp.complaint == YELLOW && minimum_treatment_checker != 0) ){
			// Else if there is someone in the yellow queue OR there is someone who didn't satisfy the
			// minimum treatment requirement and their complaint is yellow
			if( minimum_treatment_checker == 0 ){ // If we do not do the minimum requirement
				temp = yellow.dequeue(); // Pull someone from the queue
				minimum_treatment_checker = 1; // Update the minimum treatment checker
			}
			else --minimum_treatment_checker; // If we do
			--temp.treatment_time; // For every case temp will be treated 1 unit
			if(temp.treatment_time != 0 && minimum_treatment_checker == 0) temp.complaint = GREEN;
			// If did not treated fully add the patient to the green queue
			else if(temp.treatment_time == 0) temp.complaint = GRAY;
			// Else the patient is treated
			cout << time << ".time slice Patient" << temp.id << endl; // Report the situation
		}

		else if( !green.isEmpty() || (temp.complaint == GREEN && minimum_treatment_checker != 0) ){
			// Similiar to the yellow queue
			if( minimum_treatment_checker == 0 ){
				temp = green.dequeue();
				minimum_treatment_checker = 2;
			}
			else -- minimum_treatment_checker;
			--temp.treatment_time;
			if(temp.treatment_time == 0) temp.complaint = GRAY;
			cout << time << ".time slice Patient" << temp.id << endl;
		}

		for(int i = 0; i < number_of_patients; ++i){
			if( time == (*patient_list)[i].arriving_time ){
				if( (*patient_list)[i].complaint == RED ) red.enqueue( (*patient_list)[i] );
				else if( (*patient_list)[i].complaint == YELLOW ) yellow.enqueue( (*patient_list)[i] );
				else if( (*patient_list)[i].complaint == GREEN ) green.enqueue( (*patient_list)[i] );
			}
			else if( time < (*patient_list)[i].arriving_time ) break;
		} // Add the patients who will come in that time

		if(temp.complaint == YELLOW && minimum_treatment_checker == 0) yellow.enqueue(temp);
		else if(temp.complaint == GREEN && minimum_treatment_checker == 0) green.enqueue(temp);
		// If patient is not gray and there is no one who will take the minimum required treatment
	}

	delete[] *patient_list; // At the end delete the patient_list

}
