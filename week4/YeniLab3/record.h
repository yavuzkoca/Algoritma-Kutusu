#ifndef RECORD_H
#define RECORD_H

struct record
{
	char* name;
	char* number;
	void add(record phonebook[], int& size);
};

void remove(record phonebook[], int& size, int index, int max);
void list(record phonebook[], int size);

#endif 

