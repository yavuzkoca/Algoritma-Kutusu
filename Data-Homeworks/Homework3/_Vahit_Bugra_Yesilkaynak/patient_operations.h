#include "patient.h"
#include "queue.h"

int read_patients(Patient **, const char *);
void print_patients(Patient *, int);
void run_hospital(Queue &, Queue &, Queue &, Patient **, int);