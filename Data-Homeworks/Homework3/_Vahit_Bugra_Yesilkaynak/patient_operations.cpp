#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "patient_operations.h"

using namespace std;

#include <iostream>
#include <random>

using namespace std;

int partition(DataType **arr, int beg, int end){

	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(beg, end);

	int pivot_index = dist(gen);
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

int string_to_int(const string &toint){
	int number = 0;
	for(int i = 0; toint[i] != '\0'; ++i){ number = number * 10 + toint[i] - '0'; }
	return number;
}

ostream& operator<<(ostream& os, const Patient &patient){
	os << patient.id << " " << patient.arriving_time << " " << patient.treatment_time << " " << patient.complaint;
	return os;
}

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
		}
		patient_file.close();
	}
	return number_of_lines;
}

void print_patients(Patient *patient_list, int number_of_patients){
	for(int i = 0; i < number_of_patients; ++i){
		cout << patient_list[i] << endl;
	}
}

void run_hospital(Queue &red, Queue &yellow, Queue &green, Patient **patient_list, int number_of_patients){
	int time = 0;
	red.create(); yellow.create(); green.create();
	qckSort(patient_list, 0, number_of_patients - 1);

	for(int i = 0; i < number_of_patients; ++i){
		if( time == (*patient_list)[i].arriving_time ){
			if( (*patient_list)[i].complaint == RED ) red.enqueue( (*patient_list)[i] );
			else if( (*patient_list)[i].complaint == YELLOW ) yellow.enqueue( (*patient_list)[i] );
			else if( (*patient_list)[i].complaint == RED ) green.enqueue( (*patient_list)[i] );
		}
		else break;
	}

	Patient temp;
	int minimum_treatment_checker = 0;

	while(1){

		++time;

		if( !red.isEmpty() && minimum_treatment_checker == 0){
			temp = red.dequeue();
			--temp.treatment_time;
			if(temp.treatment_time != 0) temp.complaint = YELLOW;
			else 						 temp.complaint = GRAY;
			cout << time << ".time slice Patient" << temp.id << endl;
		}

		else if( !yellow.isEmpty() || (temp.complaint == YELLOW && minimum_treatment_checker != 0) ){
			if( minimum_treatment_checker == 0 ){
				temp = yellow.dequeue();
				minimum_treatment_checker = 1;
			}
			else --minimum_treatment_checker;
			--temp.treatment_time;
			if(temp.treatment_time != 0 && minimum_treatment_checker == 0) temp.complaint = GREEN;
			else if(temp.treatment_time == 0) temp.complaint = GRAY;
			cout << time << ".time slice Patient" << temp.id << endl;
		}

		else if( !green.isEmpty() || (temp.complaint == GREEN && minimum_treatment_checker != 0) ){
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
		}

		if(temp.complaint == YELLOW && minimum_treatment_checker == 0) yellow.enqueue(temp);
		else if(temp.complaint == GREEN && minimum_treatment_checker == 0) green.enqueue(temp);

		if( red.isEmpty() && yellow.isEmpty() && green.isEmpty() && time > (*patient_list)[number_of_patients - 1].arriving_time ) break;

	}

	delete[] *patient_list;

}
