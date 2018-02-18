#include "yapilar.h"
#include <iostream>
#include <string.h>

using namespace std;

typedef tagPerson tgPerson;
typedef tagPhone tgPhone;

/*************FUNC_H***********/
	void list();
	tgPerson *addPerson(char *name);
	bool addPhone(char *name, char *type, char *phone);
	bool removePerson(char *name);
	bool removePhone(char *name);
	void list_ters();
	bool updatePerson(char *name);
	bool removeJustPerson(char *name);
	bool updatePhone(char *name);
	bool search(char *name);
	void printMenu();
	bool doOperation(char op);
/*************FINISH***********/

tgPerson *head;
tgPerson *tail;

int main(int argc, char *argv[])
{
	int exit = 0;
	char operation;
	while (!exit)
	{
		printMenu();
		cout << "Enter operation: ";
		cin >> operation;
		doOperation(operation);
	}

	/*
	char name[15], type[10], phone[12];
	for (int i = 0; i < 2; ++i)
	{
		
		
		for(int i=0; i<10; i++)
		{
			cout << "Enter name of new record: ";
			cin >> name;
			addPerson(name);
		}

		list();
		cout << endl << endl;
		cout << "Search name: ";
		cin >> name;
		search(name);
		for (int i = 0; i < 4; ++i)
		{
			cout << "Numara ekle: ";
			cin >> name >> type >> phone;
			addPhone(name, type, phone);
			list();
			cout << endl << endl;
		}
		cout << "Search name: ";
		cin >> name;
		search(name);

		list();
		cout << endl << endl;
	}
	*/
	return EXIT_SUCCESS;
}




/*************FUNC_H***********/
bool doOperation(char op){
	char name[15], type[10], phone[12];

	switch (op)
	{
	case '1':
		cout << "Enter a name of new record: ";
		cin >> name;
		addPerson(name);
		break;
	case '2':
		cout << "Enter a name of new phone number: ";
		cin >> name;
		cout << "Enter type of phone number: ";
		cin >> type;
		cout << "Enter phone number: ";
		cin >> phone;
		addPhone(name, type, phone);
		break;
	case '3':
		cout << "Enter a name of will removed person: ";
		cin >> name;
		removePerson(name);
		break;
	case '4':
		cout << "Enter a name of will removed phone: ";
		cin >> name;
		removePhone(name);
		break;
	case '5':
		cout << "Enter a name of will updated person: ";
		cin >> name;
		updatePerson(name);
		break;
	case '6':
		cout << "Enter a name of will updated phone: ";
		cin >> name;
		updatePhone(name);
		break;
	case '7':
		cout << "Enter part of name: ";
		cin >> name;
		search(name);
		break;
	case '8':
		list();
		break;
	case '9':
		list_ters();
		break;
	case '0':
		return EXIT_FAILURE;
	default:
		cout << "Enter a valid operations!" << endl;
		break;
	}
	return EXIT_SUCCESS;
}

void printMenu(){

	cout << endl << endl;
	cout << "PHONE BOOK PROGRAM 6.0" << endl;
	cout << "1 - Add Person Record" << endl;
	cout << "2 - Add Phone Number" << endl;
	cout << "3 - Remove Person" << endl;
	cout << "4 - Remove Phone Number" << endl;
	cout << "5 - Update Person" << endl;
	cout << "6 - Update Phone Number" << endl;
	cout << "7 - Search " << endl;
	cout << "8 - List" << endl;
	cout << "9 - List from tail " << endl;
	cout << "0 - EXIT " << endl;
	cout << endl;
}

bool search(char *name){

	cout << "SEARCH" << endl;
	tagPerson *iterPerson = head;
	tgPhone *iterPhone;

	bool kontrol = 0;
	for (int i = 1; iterPerson != NULL; i++)
	{
		if(strncmp(iterPerson->name, name, strlen(name)) == 0)
		{
			cout << i << " - " << iterPerson->name << endl;

			iterPhone = iterPerson->phones;
			for(int j= 0; iterPhone!=NULL; j++)
			{
				cout << "\t" << iterPhone->type << "\t" << iterPhone->phone << endl;
				iterPhone = iterPhone->next;
			}
			kontrol++;
		}
		if(strncmp(iterPerson->name, name, strlen(name)) > 0)
		{
			break;
		}
		iterPerson = iterPerson->next;
	}

	if(kontrol == 0)
	{
		cout << endl << "Record cannot found: err8" << endl;	
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;	
}

bool updatePhone(char *name){

	tagPerson *iterPerson = head;
	tgPhone *iterPhone;

	for (int i = 1; iterPerson != NULL; i++)
	{
		if(strcmp(iterPerson->name, name) == 0)
		{
			cout << iterPerson->name << endl;
			if (iterPerson->phones == NULL)
			{
				cout << "Kiside kayitli telefon numarasi yok." << endl;
				return EXIT_FAILURE;
			}
			iterPhone = iterPerson->phones;
			for(int j= 1; iterPhone!=NULL; j++)
			{
				cout << "\t" << j << " - " << iterPhone->type << "\t" << iterPhone->phone << endl;
				iterPhone = iterPhone->next;
			}

			int guncelle;
			cout << "Güncellenecek telefon numarasının id'sini seçiniz: ";
			cin >> guncelle;

			
			if (guncelle <= 0 )
			{
				cout << endl << "Record cannot found: err5" << endl;
				return EXIT_FAILURE;
			}
			else
			{	
				iterPhone = iterPerson->phones;
				for (int i = 1; i < guncelle; ++i)
				{
					if(iterPhone->next == NULL)
					{
						cout << endl << "Record cannot found: err6" << endl;
						return EXIT_FAILURE;
					}
					iterPhone = iterPhone->next;
				}
				cout << "Enter new phone number: ";
				cin >> iterPhone->phone;

			}

			return EXIT_SUCCESS;
		}
		
		iterPerson = iterPerson->next;
	}
	cout << endl << "Record cannot found: err7" << endl;
	return EXIT_FAILURE;
}

bool updatePerson(char *name){

	cout << "updatePerson - " << name << endl;
	if(head==NULL)
	{
		cout << "Rehberde hiç kayıt yok" << endl;
		return EXIT_FAILURE;
	}
	tgPerson *iterPerson, *trashPerson;
	iterPerson = head;

	while(iterPerson != NULL)
	{
		if(strcmp(iterPerson->name, name) == 0)
		{
			trashPerson = iterPerson;
			cout << "Kayıt \"" << iterPerson->name << "\" bulundu" << endl;
			char name[25];
			cout << "Enter new name: ";
			cin >> name;
			tgPerson *newPerson;
			newPerson = addPerson(name);
			newPerson->phones = iterPerson->phones;
			removeJustPerson(iterPerson->name);
			return EXIT_SUCCESS;
		}
		iterPerson = iterPerson->next;
	}
	cout << "Record cannot found: err4" << endl;
	return EXIT_FAILURE;
}

bool removePhone(char *name){

	tagPerson *iterPerson = head;
	tgPhone *iterPhone, *trashPhone;

	for (int i = 1; iterPerson != NULL; i++)
	{
		if(strcmp(iterPerson->name, name) == 0)
		{
			cout << iterPerson->name << endl;
			iterPhone = iterPerson->phones;
			for(int j= 1; iterPhone!=NULL; j++)
			{
				cout << "\t" << j << " - " << iterPhone->type << "\t" << iterPhone->phone << endl;
				iterPhone = iterPhone->next;
			}

			int sil;
			cout << "Silinecek telefon numaranın id'sini seçiniz: ";
			cin >> sil;

			
			if (sil <= 0 )
			{
				cout << "Record cannot found: err3" << endl;
				return EXIT_FAILURE;
			}
			else if(sil == 1)
			{
				trashPhone = iterPerson->phones;
				iterPerson->phones = iterPerson->phones->next;
				delete trashPhone;
			}
			else
			{	
				//iterPhone = iterPerson->phones;
				trashPhone = iterPerson->phones;
				for (int i = 1; i < sil; ++i)
				{
					if(trashPhone->next == NULL)
					{
						cout << "Record cannot found: err2" << endl;
						return EXIT_FAILURE;
					}
					iterPhone = trashPhone;
					trashPhone = trashPhone->next;
				}
				iterPhone->next = trashPhone->next;
				delete trashPhone;

			}

			return EXIT_SUCCESS;
		}
		
		iterPerson = iterPerson->next;
	}
	cout << "Record cannot found: err1" << endl;
	return EXIT_FAILURE;
}

bool removePerson(char *name){

	cout << "removePerson - " << name << endl;
	if(head==NULL)
	{
		cout << "Rehberde hiç kayıt yok" << endl;
		return EXIT_FAILURE;
	}

	tgPerson *iterPerson;
	iterPerson = head;
	tgPhone *iterPhone, *trashPhone;

	while(iterPerson != NULL)
	{
		if(strcmp(iterPerson->name, name) == 0)
		{
			cout << "Kayıt \"" << iterPerson->name << "\" bulundu" << endl;

			iterPhone = iterPerson->phones;			//telefon numaraları siliniyor
			while(iterPhone != NULL)
			{
				cout << "\t\t" << iterPerson->name << "\t" << iterPhone->type << "\t" << iterPhone->phone << "\tsiliniyor." << endl;
				trashPhone = iterPhone;
				iterPhone = iterPhone->next;
				delete trashPhone;

			}

			if(iterPerson->prev != NULL)	iterPerson->prev->next = iterPerson->next;
			else 							head = iterPerson->next;
			if(iterPerson->next != NULL)	iterPerson->next->prev = iterPerson->prev;
			else							tail = iterPerson->prev;
			cout << "\t" << iterPerson->name << "\tsiliniyor." << endl;
			delete iterPerson;
			return EXIT_SUCCESS;
		}


				
		iterPerson = iterPerson->next;
	}
}

bool removeJustPerson(char *name){

	cout << "removeJustPerson - " << name << endl;
	if(head==NULL)
	{
		cout << "Rehberde hiç kayıt yok" << endl;
		return EXIT_FAILURE;
	}

	tgPerson *iterPerson;
	iterPerson = head;
	tgPhone *iterPhone, *trashPhone;

	while(iterPerson != NULL)
	{
		if(strcmp(iterPerson->name, name) == 0)
		{
			cout << "Kayıt \"" << iterPerson->name << "\" bulundu" << endl;

			if(iterPerson->prev != NULL)	iterPerson->prev->next = iterPerson->next;
			else 							head = iterPerson->next;
			if(iterPerson->next != NULL)	iterPerson->next->prev = iterPerson->prev;
			else							tail = iterPerson->prev;
			cout << "\t" << iterPerson->name << "\tsiliniyor." << endl;
			delete iterPerson;
			return EXIT_SUCCESS;
		}


				
		iterPerson = iterPerson->next;
	}
}

tgPerson *addPerson(char *name){

	tgPerson *newPerson = new tgPerson;

	strcpy(newPerson->name, name);
	newPerson->phones = NULL;
	newPerson->next = NULL;
	newPerson->prev = NULL;


	if(head==NULL)			//head oluştur
	{
		head = newPerson;
		tail = newPerson;
	}
	else 
	{	
		tagPerson *iter;
		iter = head;
		if(strcmp(iter->name, newPerson->name) > 0)	//ilk sıraya yaz
		{
			newPerson->next = iter;
			iter->prev = newPerson;
			head = newPerson;
		}
		else
		{
			while(iter->next != NULL)
			{
				if(strcmp(iter->next->name, newPerson->name) > 0)	//ortaya yaz
				{
					newPerson->next = iter->next;
					newPerson->next->prev = newPerson;
					newPerson->prev = iter;
					iter->next = newPerson;
					return newPerson;
					//break;
				}
				iter = iter->next;
			}
			if(iter->next == NULL)								//sona yaz
			{
				newPerson->next = NULL;
				newPerson->prev = iter;
				iter->next = newPerson;
				tail = newPerson;
			}
		}
	}
	return newPerson;
}

bool addPhone(char *name, char *type, char *phone){

	tgPhone *newPhone = new tgPhone;
	strcpy(newPhone->type, type);
	strcpy(newPhone->phone, phone);
	newPhone->next = NULL;

	tgPerson *iterPerson;
	iterPerson = head;
	tgPhone *iterPhone;

	while(iterPerson != NULL)
	{
		if(strcmp(iterPerson->name, name) == 0)
		{

			if(iterPerson->phones == NULL)		//tel yoksa
			{
				iterPerson->phones = newPhone;
			}
			else								//tel varsa sona ekle
			{
				iterPhone = iterPerson->phones;
				while(iterPhone->next != NULL)
				{
					iterPhone = iterPhone->next;
				}
				iterPhone->next = newPhone;
			}

			return EXIT_SUCCESS;
		}
		iterPerson = iterPerson->next;
	}
	cout << "Record did not found" << endl;
	return EXIT_FAILURE;
}

void list(){

	cout << "LİSTELE" << endl;
	tagPerson *iterPerson = head;
	tgPhone *iterPhone;

	for (int i = 1; iterPerson != NULL; i++)
	{
		iterPhone = iterPerson->phones;
		cout << i << " - " << iterPerson->name << endl;
		for(int j= 0; iterPhone!=NULL; j++)
		{
			cout << "\t" << iterPhone->type << "\t" << iterPhone->phone << endl;
			iterPhone = iterPhone->next;
		}
		iterPerson = iterPerson->next;
	}
}

void list_ters(){
	cout << "TERSTEN LİSTELE" << endl;
	tagPerson *iterPerson = tail;
	tgPhone *iterPhone;

	for (int i = 1; iterPerson != NULL; i++)
	{
		iterPhone = iterPerson->phones;
		cout << i << " - " << iterPerson->name << endl;
		for(int j= 0; iterPhone!=NULL; j++)
		{
			cout << "\t" << iterPhone->type << "\t" << iterPhone->phone << endl;
			iterPhone = iterPhone->next;
		}
		iterPerson = iterPerson->prev;
	}

}
/*************FINISH***********/
