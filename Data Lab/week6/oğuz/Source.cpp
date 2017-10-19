#include <iostream>

using namespace std;

struct numberNode{
	char type[15];
	char number[15];
	numberNode *next;
};

struct record{
	char name[30];
	record *next;
	record *prev;
	numberNode *head;
};

struct book{
	record *head;
	void addPerson(char name[]);
	void addNumber(char name[], numberNode *toadd);
	void removePerson(char name[]);
	void removeNumber(char name[]);
	void updatePerson(char name[]);
	void updateNumber(char name[]);
	void search(char name[]);
	void list();
	void deleteEverything();
};

void printMenu();
int main(){
	book mybook;
	char tempName[30];
	numberNode *tempnumber;
	tempnumber = new numberNode;
	tempnumber->next = NULL;
	char choice;
	int flag = 1;
	mybook.head = NULL;

	while (flag){
		printMenu();
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 'p': case 'P':
			cout << "enter name: ";
			cin >> tempName;
			mybook.addPerson(tempName);
			break;
		case 'n': case 'N':
			cout << "enter name: ";
			cin >> tempName;
			cout << "enter type: ";
			cin >> tempnumber->type;
			cout << "enter number: ";
			cin >> tempnumber->number;
			mybook.addNumber(tempName, tempnumber);
			break;
		case 'r': case 'R':
			cout << "enter name: ";
			cin >> tempName;
			mybook.removePerson(tempName);
			break;
		case 'd': case 'D':
			cout << "enter name: ";
			cin >> tempName;
			mybook.removeNumber(tempName);
			break;
		case 'u': case 'U':
			cout << "enter name: ";
			cin >> tempName;
			mybook.updatePerson(tempName);
			break;
		case 'k': case 'K':
			cout << "enter name: ";
			cin >> tempName;
			mybook.updateNumber(tempName);
			break;
		case 's': case 'S':
			cout << "enter name: ";
			cin >> tempName;
			mybook.search(tempName);
			break;
		case 'l': case 'L':
			mybook.list();
			break;
		case 'x': case 'X':
			flag = 0;
			break;
		
		default:
			break;
		}
	}
	mybook.deleteEverything();
}

void printMenu(){
	cout << "P: Add Person" << endl
		<< "N: Add Number" << endl
		<< "R: Remove Person" << endl
		<< "D: Remove Number" << endl
		<< "U: Update Person" << endl
		<< "K: Update Number" << endl
		<< "S: Search" << endl
		<< "L: List" << endl
		<< "X: Exit" << endl;
}
void book::addPerson(char name[]){
	record *temp;
	temp = new record;
	temp->head = NULL;
	strcpy(temp->name, name);
	temp->next = NULL;
	temp->prev = NULL;

	if (head == NULL){
		head = temp;
		return;
	}
	if (strcmp(temp->name, head->name) < 0){
		temp->next = head;
		head->prev = temp;
		head = temp;
		return;
	}
	
	record *current = head;

	while (current->next){

		if (strcmp(temp->name, current->name) < 0){
			temp->next = current;
			temp->prev = current->prev;
			current->prev->next = temp;
			current->prev = temp;
			return;
		}

		current = current->next;
	}
	if (current->next == NULL){
		current->next = temp;
		temp->prev = current;
		return;
	}
}

void book::addNumber(char myname[], numberNode *toadd){
	
	numberNode *temp;
	temp = new numberNode;
	strcpy(temp->number, toadd->number);
	strcpy(temp->type, toadd->type);
	temp->next = NULL;
	record *current = head;
	int flag = 0;

	while (current){
		if (strcmp(current->name, myname) == 0){
			if (current->head == NULL){
				current->head = temp;
			}
			else{
				numberNode *traverse = current->head;
				while (traverse->next) {
					traverse = traverse->next;
				}
				traverse->next = temp;
			}
			flag = 1;
		}
		current = current->next;
	}
	if (!(flag)) cout << "Person does not exist.";

}

void book::list(){
	record *traverse=head;
	numberNode *lister;
	while(traverse){
		cout << traverse->name << endl;

		lister = traverse->head;
		while (lister){
			cout << "  " << lister->type << lister->number << endl;
			lister = lister->next;
		}

		traverse = traverse->next;
	}

}

void book::removePerson(char name[]){
	record *current = head;

	while (current){
		if (strcmp(name, current->name) == 0){

			if (current->head){
				numberNode *deleter = current->head;
				numberNode *temp = NULL;
				while (deleter){
					temp = deleter->next;
					delete deleter;
					deleter = temp;
				}
			}

			if(current->prev) current->prev->next = current->next;
			else head = current->next;

			if(current->next) current->next->prev = current->prev;
			delete current;
			return;
		}
		current = current->next;
	}
}

void book::removeNumber(char name[]){
	record *current = head;
	int counter = 0;
	while (current){
		if (strcmp(name, current->name) == 0){
			numberNode *remover = current->head;

			while (remover){
				cout << counter << " " << remover->type << " " << remover->number << endl;
				counter++;
				remover = remover->next;
			}
			cout << "enter the index: ";
			cin >> counter;
			remover = current->head;

			if (counter == 0){
				current->head = remover->next;
				delete remover;
				return;
			}

			for (int i = 0; i < counter-1; i++){
				remover = remover->next;
			}
			numberNode *temp = remover->next;
			remover->next = remover->next->next;
			delete temp;
			return;
		}
		current = current->next;
	}
}

void book::updatePerson(char name[]){
	record *finder = head;
	record *replacer = head;

	while (finder){
		if (strcmp(name, finder->name) == 0){

			if (finder->prev) finder->prev->next = finder->next;
			else head = finder->next;

			if (finder->next) finder->next->prev = finder->prev;

			cout << "enter new name: ";
			cin >> finder->name;

			while (replacer){

				if (strcmp(finder->name, replacer->name) < 0){
					if (replacer->prev == NULL){
						replacer->prev = finder;
						finder->next = replacer;
						head = finder;
						finder->prev = NULL;
						return;
					}
					finder->next = replacer;
					finder->prev = replacer->prev;
					replacer->prev->next = finder;
					replacer->prev = finder;
					return;
				}
				if (replacer->next == NULL){
					replacer->next = finder;
					finder->prev = replacer;
					finder->next = NULL;
					return;
				}
				replacer = replacer->next;
			}
		}
		finder = finder->next;
	}

}

void book::updateNumber(char name[]){

	record *current = head;
	char tempType[15];
	char tempNum[15];

	int counter = 0;
	while (current){
		if (strcmp(name, current->name) == 0){
			numberNode *remover = current->head;

			while (remover){
				cout << counter << " " << remover->type << " " << remover->number << endl;
				counter++;
				remover = remover->next;
			}
			
			remover = current->head;
			
			
			cout << "enter the index: ";
			cin >> counter;
			for (int i = 0; i < counter; i++){
				remover = remover->next;
			}
			
			cout << "new type: ";
			cin >> remover->type;
			cout << "new number: ";
			cin >> remover->number;
			return;
		}
		current = current->next;
	}
}

void book::search(char name[]){

	record *traverse = head;
	numberNode *lister;

	while (traverse && strcmp(traverse->name,name)<= 0){
		
		if (strcmp(traverse->name, name) == 0){
			cout << traverse->name << endl;

			lister = traverse->head;
			while (lister){
				cout << "  " << lister->type << lister->number << endl;
				lister = lister->next;
			}
		}

		traverse = traverse->next;
	}
}

void book::deleteEverything(){
	record *current = head;

	while (current){
		

		if (current->head){
			numberNode *deleter = current->head;
			numberNode *temp = NULL;
			while (deleter){
				temp = deleter->next;
				delete deleter;
				deleter = temp;
			}
		}

		if (current->prev) current->prev->next = current->next;
		else head = current->next;

		if (current->next) current->next->prev = current->prev;
		
		delete current;
		return;
		
		current = current->next;
	}
}