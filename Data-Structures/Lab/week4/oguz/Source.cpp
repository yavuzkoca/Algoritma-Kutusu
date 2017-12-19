#include <iostream>
#include <new>

using namespace std;

struct Record
{
	char* name;
	char* tel;
};

struct book
{
	Record* myList;
	void add(Record *newrecord);
	void remove(int number);
	void list();
	void extend();
	void update(int number, Record *newrecord);
	void search(char word[]);
	int recordNum;
	int allocated;
};

int main()
{
	book phonebook;
	phonebook.myList = new Record[2];
	phonebook.allocated = 2;
	phonebook.recordNum = 0;
	for (int i = 0; i < phonebook.allocated; i++)
	{
		(phonebook.myList + i)->name = new char[];
		(phonebook.myList + i)->tel = new char[];
	}
	int flag = 1;
	Record *temp;
	temp = new Record;
	temp->name = new char[];
	temp->tel = new char[];
	char choice;
	char* searchword;
	searchword = new char[];
	
	while (flag)
	{
		cin >> choice;
		switch (choice)
		{
		case 'a': case 'A':
			cout << "Name:";
			cin >> temp->name;
			cout << "Number:";
			cin >> temp->tel;
			cout << "before func:" <<phonebook.recordNum;
			cout << " " << phonebook.allocated << endl;
			phonebook.add(temp);
			break;
		case 'e': case 'E':
			flag = 0;
			break;
		case 'l': case 'L':
			phonebook.list();
			break;
		case 'r': case'R':
			int ind;
			cout << "enter the index";
			cin >> ind;
			phonebook.remove(ind);
			break;
		case 's': case'S':
			
			cin >> searchword;
			phonebook.search(searchword);
			break;
		case 'u': case'U':
			int upind;
			cout << "index:";
			cin >> upind;
			cout << "Name:";
			cin >> temp->name;
			cout << "Number:";
			cin >> temp->tel;
			phonebook.update(upind, temp);
			break;

			default:
				break;
		}
	}
	

	delete[] phonebook.myList;
	cin.ignore(1000, '\n');
	getchar();
}

void book::add(Record *newrecord)
{
	Record* slide;
	int place = 0;
	
	if (recordNum == (allocated - 1))
	{
		extend();
	}

	
	slide = myList;

	
	for (int i = 0; i < recordNum; i++)
	{
		if (strcmp(newrecord->name, slide->name)>0)
		{
			place = i + 1;
		}
		slide++;
	}
	for (int i = recordNum; i > place; i--)
	{
		strcpy(slide->name, (slide - 1)->name);
		strcpy(slide->tel, (slide - 1)->tel);
		slide--;
	}
	strcpy(slide->name, newrecord->name);
	strcpy(slide->tel, newrecord->tel);
	recordNum++;
}
void book::remove(int number)
{
	Record *remover;
	remover = myList;
	if (recordNum == 0)
	{
		cout << "nothing to remove";
	}
	if (recordNum == 1) recordNum = 0;
	if (recordNum > 1)
	{
		for (int i = 0; i < recordNum - 1; i++){
			if (i >((number - 1) - 1))
			{
				strcpy(remover->name, (remover + 1)->name);
				strcpy(remover->tel, (remover + 1)->tel);
			}

			remover++;
		}
		recordNum--;
	}
}

void book::list()
{
	Record *lister;
	lister = myList;
	for (int i = 0; i < recordNum && lister; i++)
	{
		cout << "Name: " << lister->name << "Number: " << lister->tel << endl;
		lister++;
	}
}

void book::extend()
{
	allocated *= 2;

	Record* temp;
	temp = new Record[allocated];

	for (int i = 0; i < allocated; i++)
	{
		(temp+i)->name = new char[];
		(temp+i)->tel = new char[];
	}
	for (int i = 0; i < recordNum; i++)
	{
		strcpy((temp + i)->name, (myList + i)->name);
		strcpy((temp + i)->tel, (myList + i)->tel);
	}
	myList = temp;
	
}

void book::update(int number, Record *newrecord)
{
	remove(number);
	add(newrecord);
	
}

void book::search(char word[])
{
	Record *searcher;
	searcher = myList;
	for (int i = 0; i < recordNum; i++)
	{
		if (strcmp(searcher->name, word) == 0)
		{
			cout << i + 1 << ". " << searcher->name << endl;
		}
		searcher++;
	}
}