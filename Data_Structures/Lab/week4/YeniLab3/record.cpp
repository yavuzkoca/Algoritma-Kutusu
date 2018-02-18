#include "record.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

void record::add(record phonebook[], int &size)
{
	int index = 0, i = 0, flag = 0;
	while (phonebook[index].name != NULL && strcmp(name, phonebook[index].name) > 0)
	{
		index++;
	}
	
	for (int i = size; i > index; i--)
	{
		phonebook[i] = phonebook[i - 1];
	}

	phonebook[index].name = name;
	phonebook[index].number = number;
	size++;
}

void list(record phonebook[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << i << ". " << (phonebook + i)->name << " " << (phonebook + i)->number << endl;
	}
}

void remove(record phonebook[], int& size, int index, int max)
{
	int i = 0, j = 0;
	record* temp;
	temp = (record*)calloc(size, sizeof(record));
	while (i < size)
	{
		if (i == index)
		{
			i++;
			continue;
		}
		temp[j] = phonebook[i];
		i++;
		j++;
	}
	
	size--;
	free(phonebook);
	phonebook = (record*) calloc(max, sizeof(record));
	for (int i = 0; i < size; i++)
	{
		phonebook[i] = temp[i];
	}
	
	free(temp);

}