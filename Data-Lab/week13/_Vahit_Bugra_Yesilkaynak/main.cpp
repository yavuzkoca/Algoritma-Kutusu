#include <iostream>
#include <string>

#include "structures.h"

using namespace std;

typedef MasterTree phonebook;

int main(){


	char input = '0';

	phonebook p;
	p.create();

	string name, number, name2;

	name = "Bugra";
	number = "05313248216";
	p.add(name, number);
	name = "Mehves";
	number = "05555555555";
	p.add(name, number);
	name = "Hakan";
	number = "05444444444";
	p.add(name, number);
	name = "Bugroli";
	number = "123";
	p.add(name, number);
	name = "Bugoli";
	number = "12345";
	p.add(name, number);
	name = "Bugra";
	number = "111111";
	p.add(name, number);

	while(input != 'x'){

		cout << "Welcome to the phonebook. Please choose your operations:" << endl;
		cout << "\t1. Add" << endl;
		cout << "\t2. Print" << endl;
		cout << "\t3. Search" << endl;
		cout << "\t4. Update" << endl;
		cout << "\t5. Delete" << endl;
		cout << "To exit please enter -> x" << endl;

		cout << endl << "Your choice: ";
		cin >> input;

		switch(input){
			case '1':
				cout << endl;
				cout << "Please enter the name you want to add: ";
				cin >> name;
				cout << "Please enter the phone number: ";
				cin >> number;
				p.add(name, number);
				break;
			case '2':
				cout << endl;
				p.print(p.root);
				break;
			case '3':
				cout << endl;
				cout << "Please enter the name you want to search for: ";
				cin >> name;
				p.search(name);
				break;
			case '4':
				cout << endl;
				cout << "Please enter the name you want to update: ";
				cin >> name;
				cout << "Please enter the new name: ";
				cin >> name2;
				p.update(name, name2);
				break;
			case '5':
				cout << endl;
				cout << "Please enter the name you want to delete: ";
				cin >> name;
				p.del(name);
		}

		cout << endl;

	}

	//p.close(p.root);

	return 0;
}