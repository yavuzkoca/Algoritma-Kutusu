/*
cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << endl;
*/

#include <iostream>
#include <fstream>
#include "bst.h"
#include "node.h"

bool doOperation();

using namespace std;

bst tree;

int main(){

	
	tree.create();

	bool exit = false;
	while(!exit)
	{
		exit = !doOperation();
	}
	return 0;
}

bool doOperation(){

	char op;
	cout << endl
		 << "BST Phone Book" << endl
		 << "1 - Add Record" << endl
		 << "2 - Remove Record" << endl
		 << "3 - Search Record" << endl
		 << "4 - Update Record" << endl
		 << "5 - Show Phone Book" << endl
		 << "6 - Show Only Name" << endl
		 << "7 - Add Records from File" << endl
		 << "0 - Exit" << endl
		 << endl
		 << "Select the operation: ";
	cin >> op;


	char name[LENGHT_NAME], phoneNumber[LENGHT_NUMBER];
	node *found;
	ifstream dosya;

	switch (op)
	{

		case '1':
			cout << "Enter name: ";	cin >> name;
			cout << "Enter phone number: ";	cin >> phoneNumber;
			tree.add(name, phoneNumber);
			break;
		
		case '2':
			cout << "Enter name for removing: "; cin >> name;
			if(!tree.remove(name))
				cout << "Record could not be found!" << endl;
			break;
		
		case '3':
			cout << "Enter name for searching: "; cin >> name;
			found = tree.search(name, tree.root);
			if(found)
			{
				cout << "Record is found." << endl;
				showNode(found);
			}
			else
			{
				cout << "Record could not found!" << endl;
			}
			break;
		
		case '4':
			cout << "Enter name for updating: "; cin >> name;
			if (!tree.search(name,tree.root))
			{
				cout << "Isim kayitli degil." << endl;
				break;
			}
			if (!tree.update(name))
			{
				cout << "Record could not be found!" << endl;
			}
				

			break;

		case '5':
			cout << endl << "\t~~~~Phone Book~~~~" << endl;
			tree.show(tree.root);
			break;

		case '6':
			cout << endl << "\t~~~~Phone Book~~~~" << endl;
			tree.showName(tree.root);
			break;
		
		case '7':
			dosya.open("phoneBook.txt");
			while(!dosya.eof())
			{
				dosya >> name >> phoneNumber;
				tree.add(name, phoneNumber);
			}
			dosya.close();
			break;

		case '0':
			tree.close(tree.root);
			return false;

		default:
			cout << "Enter a valid operation!" << endl;
	}
	
	//cout << "Press ENTER to continue" << endl;
	//getchar();	getchar();
	cout << endl << "------------------------------------------------------" << endl << endl;
	return true; 
}
