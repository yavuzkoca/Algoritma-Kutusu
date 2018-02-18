#ifndef PATIENT_H
#define PATIENT_H

#define RED 0
#define YELLOW 1
#define GREEN 2
#define GRAY -1

struct Patient{
	int id;
	int arriving_time;
	int treatment_time;
	int complaint;
};

#endif