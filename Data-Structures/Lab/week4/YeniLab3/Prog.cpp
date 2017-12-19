#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "record.h"

using namespace std;

int main()
{
	char mode = '0';
	record* phonebook;
	int max = 10, i, index;
	int size = 0;
	phonebook = (record*) calloc(max, sizeof(record));
	while (1)
	{
		cout << "Please enter the operation you would like to do" << endl << endl;
		cout << "A: Add record" << endl;
		cout << "R: Remove record" << endl;
		cout << "L: List records" << endl;
		cout << "E: Exit" << endl;
		cin >> mode;
		switch (mode)
		{
			case 'A': case 'a':
				record newrecord; // Creating a new record

				newrecord.name = (char*) malloc(1); // Allocating space for the first letter.
				i = 0;
				cout << "Please enter the name of the record." << endl;
				cout << "Use a slash to mark the end of the name." << endl;
				while (newrecord.name[i-1] != '/')
				{ // While name is not finished, keep allocating space for letters.
					scanf("\n%c", newrecord.name+i);	
					i++;
					newrecord.name = (char*) realloc(newrecord.name, i+1);
				}
				newrecord.name[i - 1] = '\0'; // Finish the name string.
				//cout << endl << newrecord.name;
				
				newrecord.number = (char*)malloc(1); // Allocating space for the first number.
				i = 0;
				cout << "Please enter the number of the record." << endl;
				cout << "Use a slash to mark the end of the number." << endl;
				while (newrecord.number[i - 1] != '/')
				{
					scanf("\n%c", newrecord.number + i);
					i++;
					newrecord.number = (char*) realloc(newrecord.number, i + 1);
				}
				newrecord.number[i - 1] = '\0';
				//cout << endl << newrecord.number;
				newrecord.add(phonebook, size);
				if (size == max)
				{
					max *= 2;
					phonebook = (record*) realloc(phonebook, max*sizeof(record));
				}
				break;

			case 'R': case 'r':
				cout << "Please enter the index of the record you want to delete.";
				cout << endl << endl;
				list(phonebook, size);
				cin >> index;
				remove(phonebook, size, index, max);
				break;
			
			case 'L': case 'l':
				list(phonebook, size);
				break;

			case 'E': case 'e':
				cout << "Program has been terminated." << endl;
				getchar();
				getchar();
				return 0;

		}
	}




	return 0;
}