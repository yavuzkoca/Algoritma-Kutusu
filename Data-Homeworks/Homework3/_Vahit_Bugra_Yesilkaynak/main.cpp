#include <iostream>

#include "patient_operations.h"

int main(){

	Patient *patient_list; // To hold the patients from the text file
	Queue red, yellow, green; // Asked queues
	const char *PATIENT_INFO_PATH = "patientsInfo.txt"; // Path to the patients file

	int number_of_patients = read_patients(&patient_list, PATIENT_INFO_PATH); // Reads from file to create patient_list
	run_hospital(red, yellow, green, &patient_list, number_of_patients); // The main simulation, also deletes patient_list

	return 0;
}