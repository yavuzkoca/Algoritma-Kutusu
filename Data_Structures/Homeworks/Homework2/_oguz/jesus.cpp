/* @Author
* Student Name: Oðuz Topçu
* Student ID : 150150118
* Date: 31/10/2017
*/

//care for the input filename @insertAll function

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

//structs
struct studentInfo
{
	char *name;
	char *surname;
	char *email;
	studentInfo *next, *previous;
};

struct surnameNode
{
	studentInfo *head;
	char *surname;
	surnameNode *next;
};

struct surnameMap
{
	bool list; // 0 if list hasn't been created yet
	surnameNode *head;
	void createList();
	void insertAll();
	void insertNewRecord(studentInfo *newStu);
	void deleteStudent(char *email, char *surname);
	void deleteSurnameNode(char *surname);
	void updateList(char *email, char *surname, studentInfo *newStu);
	void remove();
	void writeToFile();
	void writeToScreen(); //prints to the command line
	void close(); //deallocates memory
	void printMenu();
};

int main()
{

	surnameMap mymap;
	mymap.list = 0;

	//user input variables
	studentInfo *newRec = new studentInfo;
	char *input_name = new char[50];
	char *input_surname = new char[50];
	char *input_email = new char[50];
	char *delete_surname = new char[50];
	char *delete_email = new char[50];

	bool loop = 1;
	char choice;

	while (loop){
		mymap.printMenu();
		cin >> choice;
		system("clear");

		//making sure that user creates the list first
		//if user is going to create a list or exit the program
		//it skips to the switch part
		while (!mymap.list && choice != '1' && choice != '9'){
			system("clear");
			cout << "Please create a list first." << endl;
			mymap.printMenu();
			cin >> choice;
			system("clear");
		}

		switch (choice)
		{
		case '1':
			mymap.createList(); //1
			break;
		case '2':
			mymap.insertAll();  //2
			break;
		case '3':
			cout << "Enter name:";
			cin >> input_name;
			cout << "Enter surname:";
			cin >> input_surname;
			*input_name = toupper(*input_name);
			*input_surname = toupper(*input_surname);
			newRec->name = new char[strlen(input_name) + 1];
			newRec->surname = new char[strlen(input_surname) + 1];
			strcpy(newRec->name, input_name);
			strcpy(newRec->surname, input_surname);
			mymap.insertNewRecord(newRec);//3
			delete[] newRec->name;
			delete[] newRec->surname;
			break;
		case '4':
			cout << "Enter surname: ";
			cin >> delete_surname;
			*delete_surname = toupper(*delete_surname);
			cout << "Enter e-mail: ";
			cin >> delete_email;
			mymap.deleteStudent(delete_email, delete_surname); //4
			break;
		case '5':
			cout << "Enter surname: ";
			cin >> delete_surname;
			*delete_surname = toupper(*delete_surname);
			mymap.deleteSurnameNode(delete_surname); //5
			break;
		case '6':
			cout << "Enter old e-mail to delete:";
			cin >> delete_email;
			cout << "Enter old surname to delete:";
			cin >> delete_surname;
			cout << "Enter new name:";
			cin >> input_name;
			cout << "Enter new surname:";
			cin >> input_surname;
			*input_name = toupper(*input_name);
			*input_surname = toupper(*input_surname);
			*delete_surname = toupper(*delete_surname);
			newRec->name = new char[strlen(input_name) + 1];
			newRec->surname = new char[strlen(input_surname) + 1];
			strcpy(newRec->name, input_name);
			strcpy(newRec->surname, input_surname);
			mymap.updateList(delete_email, delete_surname, newRec);
			delete[] newRec->name;
			delete[] newRec->surname;
			break;
		case '7':
			mymap.writeToFile();//7
			getchar();
			break;
		case '8':
			mymap.writeToScreen();
			getchar();
			break;
		case '9':
			loop = 0;
			break;
		default:
			cout << "Wrong choice!";
			choice = 0;
			break;
		}
	}

	getchar();

	//deallocating input variables
	delete[] input_name;
	delete[] input_surname;
	delete[] input_email;
	delete[] delete_surname;
	delete[] delete_email;
	delete newRec;

	//if the list exists then deallocates it
	if (mymap.list)	mymap.close();

}
void surnameMap::printMenu(){
	cout << "1: Create" << endl
		<< "2: Insert All" << endl
		<< "3: Insert New Record" << endl
		<< "4: Delete Student" << endl
		<< "5: Delete Surname Node" << endl
		<< "6: Update List" << endl
		<< "7: Write to file" << endl
		<< "8: Write to screen" << endl
		<< "9:Exit" << endl;
}
void surnameMap::createList(){
	head = NULL;
	list = 1;
}
void surnameMap::insertAll(){

	FILE *input;
	if ((input = fopen("dataset_wOutTurkishChars.txt", "r")) == NULL){
		cout << "file not found" << endl;
		return;
	}

	//temp student
	studentInfo *stuTemp;
	stuTemp = new studentInfo;
	stuTemp->next = NULL;
	stuTemp->previous = NULL;

	char name[60], surname[60];
	int i = 0;

	while (!feof(input)){
		fscanf(input, "%s %s", name, surname);
		stuTemp->name = new char[strlen(name) + 1];
		stuTemp->surname = new char[strlen(surname) + 1];
		*name = toupper(*name);
		*surname = toupper(*surname);
		strcpy(stuTemp->name, name);
		strcpy(stuTemp->surname, surname);
		insertNewRecord(stuTemp); //inserts
		delete[] stuTemp->name;
		delete[] stuTemp->surname;
		stuTemp->name = NULL;
		stuTemp->surname = NULL;
	}

	delete stuTemp;
	fclose(input);
}
void surnameMap::insertNewRecord(studentInfo *newStu)
{
	//temp surname
	surnameNode *temp;
	temp = new surnameNode;
	temp->surname = new char[strlen(newStu->surname) + 1];
	temp->head = NULL;
	temp->next = NULL;
	strcpy(temp->surname, newStu->surname);

	surnameNode *position; //this is for keeping the surname location

	//if the list is empty
	if (head == NULL){
		head = temp;
		temp->next = head;
		position = head;
	}

	else{
		//if new student will be the last node
		if (strcmp(temp->surname, head->surname) > 0){
			temp->next = head->next;
			head->next = temp;
			head = temp;
			position = head;
		}

		else{
			surnameNode *traverse = head;
			while (strcmp(temp->surname, traverse->next->surname) > 0){
				traverse = traverse->next;
			}
			if (strcmp(temp->surname, traverse->next->surname) != 0){
				temp->next = traverse->next;
				traverse->next = temp;
				position = traverse->next;
			}
			else{ //if same surname exists
				position = traverse->next;
				delete[] temp->surname;
				delete temp;
			}
		}
	}

	//remember position points to our surname

	studentInfo* record = new studentInfo;
	record->name = new char[strlen(newStu->name) + 1];
	record->surname = new char[strlen(newStu->surname) + 1];
	strcpy(record->name, newStu->name);
	strcpy(record->surname, newStu->surname);
	record->next = NULL;
	record->previous = NULL;

	//tolower
	*(record->name) = tolower(*(record->name));
	*(record->surname) = tolower(*(record->surname));

	char *mailtemp;
	mailtemp = new char[strlen(newStu->surname) + strlen(newStu->name) + 7];
	sprintf(mailtemp, "%s", record->surname);

	//student is the first student in the list
	if (position->head == NULL){
		record->email = new char[strlen(mailtemp) + 1];
		strcpy(record->email, mailtemp);
		position->head = record;
		*(record->name) = toupper(*(record->name));
		*(record->surname) = toupper(*(record->surname));
		delete[] mailtemp;
		return;
	}

	studentInfo *current = position->head;
	int letter = 0;
	int number = 2;

	while (strcmp(current->email, mailtemp) <= 0){
		//same mail exists
		if (strcmp(current->email, mailtemp) == 0){
			//use name letters
			if (strlen(mailtemp) < strlen(record->name) + strlen(record->surname)){
				sprintf(mailtemp, "%s%c", mailtemp, *(record->name + letter)); //asteriks?
				letter++;
			}
			//no name letters left
			else{
				sprintf(mailtemp, "%s%s%d", record->surname, record->name, number);
				number++;
			}
		}
		//end of the list
		if (current->next == NULL){
			record->email = new char[strlen(mailtemp) + 1];
			strcpy(record->email, mailtemp);
			current->next = record;
			record->previous = current;
			*(record->name) = toupper(*(record->name));
			*(record->surname) = toupper(*(record->surname));
			delete[] mailtemp;
			return;
		}
		current = current->next;
	}
	//insert between
	record->email = new char[strlen(mailtemp) + 1];
	strcpy(record->email, mailtemp);
	current->previous->next = record;
	record->previous = current->previous;
	current->previous = record;
	record->next = current;
	*(record->name) = toupper(*(record->name));
	*(record->surname) = toupper(*(record->surname));
	delete[] mailtemp;
	return;

}
void surnameMap::deleteStudent(char *email, char *surname){

	if (head == NULL){
		cout << "nothing to delete!";
		return;
	}
	surnameNode *sur = head->next;
	surnameNode *tail = head;

	//scans the list for surname match
	while (sur != head && strcmp(sur->surname, surname) != 0){
		tail = sur;
		sur = sur->next;
	}

	//if while stopped because it came to head again
	if (strcmp(sur->surname, surname) != 0){
		cout << "Surname not found.";
		return;
	}

	//otherwise surname has been found

	studentInfo *rec = sur->head;

	while (rec && strcmp(rec->email, email) != 0){
		rec = rec->next;
	}
	//same goes for here
	if (strcmp(rec->email, email) != 0){
		cout << "Student not found.";
		return;
	}
	//links the adjacent nodes
	if (rec->previous)	rec->previous->next = rec->next;
	if (rec->next)	rec->next->previous = rec->previous;

	//if the deleted node was head
	if (rec == sur->head)	sur->head = rec->next;

	delete[] rec->name;
	delete[] rec->surname;
	delete[] rec->email;
	delete rec;

	//if it was the last node
	if (sur->head == NULL){
		tail->next = sur->next;
		if (sur == head){
			if (head == head->next) head = NULL;
			else head = tail;
		}
		delete[] sur->surname;
		delete sur;
	}

}
void surnameMap::deleteSurnameNode(char *surname){

	if (head == NULL){
		cout << "nothing to delete!";
		return;
	}

	surnameNode *sur = head->next;
	surnameNode *tail = head;

	while (sur != head && strcmp(sur->surname, surname) != 0){
		tail = sur;
		sur = sur->next;
	}
	if (strcmp(sur->surname, surname) != 0){
		cout << "Surname not found.";
		return;
	}

	//since we deleted the surname node while deleting the last student it has
	//this if is not necessary
	if (sur->head){
		studentInfo *d, *t;
		t = sur->head;
		while (t){
			d = t;
			t = t->next;
			delete[] d->email;
			delete[] d->name;
			delete[] d->surname;
			delete d;
		}
	}

	tail->next = sur->next;

	if (sur == head){
		//if it was the last surnamenode
		if (head == head->next) head = NULL;

		//otherwise
		else head = tail;
	}
	delete[] sur->surname;
	delete sur;
}
void surnameMap::updateList(char *email, char *surname, studentInfo *newStu){
	//shortcut
	deleteStudent(email, surname);
	insertNewRecord(newStu);
}
void surnameMap::writeToScreen(){
	if (head == NULL){
		cout << "List is empty.";
		return;
	}
	surnameNode *sur = head->next;
	studentInfo *stu;

	while (sur != head){
		cout << "surname: " << sur->surname << endl;
		stu = sur->head;
		while (stu){
			cout << "\t email:" << stu->email << "\tName: " << stu->name << endl;
			stu = stu->next;
		}
		sur = sur->next;
	}
	cout << "surname: " << sur->surname << endl;
	stu = sur->head;
	while (stu){
		cout << "\t email:" << stu->email << "\tName: " << stu->name << endl;
		stu = stu->next;
	}

}
void surnameMap::writeToFile(){
	if (head == NULL){
		cout << "Nothing to write.!" << endl;
		return;
	}
	surnameNode *sur = head->next;
	studentInfo *stu;
	FILE *wr;
	wr = fopen("emailList.txt", "w+");

	while (sur != head){
		stu = sur->head;
		while (stu){
			fprintf(wr, "%s@itu.edu.tr\t%s\t%s\n", stu->email, stu->name, stu->surname);
			stu = stu->next;
		}
		sur = sur->next;
	}
	stu = sur->head;
	while (stu){
		fprintf(wr, "%s@itu.edu.tr\t%s\t%s\n", stu->email, stu->name, stu->surname);
		stu = stu->next;
	}
	cout << "Successful!" << endl;
	fclose(wr);
}
void surnameMap::close(){
	// I know the variable names aren't clear to read or to understand
	// yet p becomes d , d goes forward , p deallocates. 1 is for studentinfo
	// 2 is for surnamenode.

	if (head){
		studentInfo *d1;
		surnameNode *d2;
		studentInfo *p1;
		surnameNode *p2;

		d2 = head->next;

		while (d2 != head){
			p2 = d2;
			d1 = d2->head;
			while (d1){
				p1 = d1;
				d1 = d1->next;
				delete[] p1->email;
				delete[] p1->name;
				delete[] p1->surname;
				delete p1;
			}
			d2 = d2->next;
			delete[] p2->surname;
			delete p2;
		}

		p2 = d2;
		d1 = d2->head;
		while (d1){
			p1 = d1;
			d1 = d1->next;
			delete[] p1->email;
			delete[] p1->name;
			delete[] p1->surname;
			delete p1;
		}
		delete[] p2->surname;
		delete p2;
	}
}
