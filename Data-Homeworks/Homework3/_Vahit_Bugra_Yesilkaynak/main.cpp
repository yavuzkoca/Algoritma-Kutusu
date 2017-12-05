#include <iostream>

#include "patient_operations.h"

int main(){

	Patient *patient_list;
	Queue red, yellow, green;
	const char *PATIENT_INFO_PATH = "patientsInfo.txt";

	int number_of_patients = read_patients(&patient_list, PATIENT_INFO_PATH); // Reads from file to create patient_list
	run_hospital(red, yellow, green, &patient_list, number_of_patients); // Also deletes the patient_list

	return 0;
}