#include "patient.h"
#include "queue.h"

int read_patients(Patient **, const char *);
// Reads patients from a text file whose path is given as a parameter,
// then writes it to a patient array also given as an argument
void print_patients(Patient *, int);
// Prints the patients in a given patient array
void run_hospital(Queue &, Queue &, Queue &, Patient **, int);
// This functions runs the whole simulation and prints the asked output
