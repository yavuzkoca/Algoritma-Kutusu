#include <iostream>
#include "phonetree.h"

using namespace std;

void print_menu();

int main(){
	Tree mine;
	mine.create();
	bool loop = 1;
	char choice;
	Temp_node *x = new Temp_node;

	while (loop){
		print_menu();
		cin >> choice;
		system("cls");
		switch (choice)
		{
			case '1':
				cout << "name:";
				cin >> x->name;
				cout << "num:";
				cin >> x->phonenum;
				mine.add(x);
				break;
			case '2':
				mine.traverse_inorder(mine.root);
				break;
			case '3':
				char s[NAME_LENGTH+1];
				cout << "enter key";
				cin >> s;
				mine.search(s);
				break;
			case '4':
				char old[NAME_LENGTH + 1];
				char neu[NAME_LENGTH + 1];
				cout << "old";
				cin >> old;
				cout << "new";
				cin >> neu;
				mine.update(old, neu);
				break;
			case '5':
				char dell[NAME_LENGTH + 1];
				cin >> dell;
				mine.del(dell);
				break;
			case '6':
				loop = 0;
				break;
			default:
				break;
		}
	}
	mine.close();
	getchar();
}

void print_menu(){
	cout << "1:add" << endl
		<< "2:list" << endl
		<< "3:search" << endl
		<< "4:update" << endl
		<< "5:del" << endl
		<<"6:exit"<<endl;
}

