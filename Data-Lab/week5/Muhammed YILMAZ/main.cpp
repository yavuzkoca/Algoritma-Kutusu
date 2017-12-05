#include "yapilar.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef st_tel_defteri tp_teldefteri;

tp_teldefteri *head;
tp_teldefteri *iter;
tp_teldefteri *headS;
tp_teldefteri *n = new tp_teldefteri;
tp_teldefteri *iterS;

void printMenu();
bool doOperation(char op);
void add(char *name, char *surname, char *phoneNumber);
void remove(int id);
void update(int id);
void list(tp_teldefteri *iterF, tp_teldefteri *headF);
tp_teldefteri *search(char *arama);
void cop(tp_teldefteri *temp);

int main(int argc, char *argv[]){
	char op = 'a';
	while ( op != 'e')
	{
	//	system("clear");
		printMenu();
		cin >> op;
		doOperation(op);
		/*getchar();
		getchar();*/
	}

	getchar();
	return EXIT_SUCCESS;
}

void printMenu(){

	cout << endl << endl;
	cout << "Phone Book Application 4" << endl;
	cout << "A: Add" << endl;
	cout << "R: Remove" << endl;
	cout << "U: Update" << endl;
	cout << "L: List" << endl;
	cout << "S: Search" << endl;
	cout << "E: Exit" << endl << endl;
	cout << "Please enter a operation: ";

}

bool doOperation(char op){
	char nameA[50], surnameA[50], phoneNumberA[12];

/*	char adi[5] = "ahli", soyadi[7] = "kuyucu", tel[12] = "05551236589";
	char adi2[6] = "bhmet", soyadi2[3] = "wa", tel2[12] = "05963698525";
	char adi3[7] = "ceylan", soyadi3[4] = "sac", tel3[12] = "05963214569";
	char adi4[5] = "bhan", soyadi4[7] = "wergsv", tel4[12] = "08963254423";
	char adi5[10] = "suleyman", soyadi5[5] = "lama", tel5[12] = "07896321456";
*/

	int id;
	switch (op)
	{
	case 'a':	case 'A':
		cout << "Enter name: ";
		scanf("%s", nameA);
		
		cout << "Enter surname: ";
		scanf("%s", surnameA);
		cout << "Enter tel: ";
		scanf("%s", phoneNumberA);
		add(nameA, surnameA, phoneNumberA);
		list(iter, head);
		
/*		add(adi2, soyadi2, tel2);
		add(adi3, soyadi3, tel3);
		add(adi4, soyadi4, tel4);
		add(adi5, soyadi5, tel5);
		add(adi, soyadi, tel);
*/		break;
	case 'r':	case 'R':
		list(iter, head);
		cout << "Enter id of record that will deleted: ";
		scanf("%d", &id);
		remove(id);
		break;
	case 'u':	case 'U':
		list(iter, head);
		cout << "Enter id of record that will updated: ";
		scanf("%d", &id);
		remove(id);
		doOperation('a');

		break;
	case 'L':	case 'l':
		list(iter, head);

		break;
	case 's':	case 'S':
		cout << "Aranacak kelimeyi giriniz: ";
		scanf("%s", nameA);
		list(search(nameA), iterS);
		break;
	case 'e':	case 'E':
		return EXIT_FAILURE;
		break;
	default:
		list(headS, iterS);
		break;
	}
	return EXIT_SUCCESS;
}

void add(char *name, char *surname, char *phoneNumber) {
	tp_teldefteri *n = new tp_teldefteri;
	n->next = NULL;

	n->name = new char[1];
	n->surname = new char[1];
	n->phoneNumber = new char[1];

	for (int i = 0; name[i]!='\0'; ++i)
	{
		n->name = (char*) realloc(n->name, sizeof(char)*(i+1));
		n->name[i]=name[i];
	}
	for (int i = 0; surname[i]!='\0'; ++i)
	{
		n->surname = (char*) realloc(n->surname, sizeof(char)*(i+1));
		n->surname[i]=surname[i];
	}
	for (int i = 0; phoneNumber[i]!='\0'; ++i)
	{
		n->phoneNumber = (char*) realloc(n->phoneNumber, sizeof(char)*(i+1));
		n->phoneNumber[i]=phoneNumber[i];
	}

	if(head == NULL)	//ilk elemanı oluştur
	{
		head = n;
	}
	else				//ilk eleman var
	{
		iter = head;	//baştan say
		if(strcmp(head->name , n->name) == 0)		//isimler aynı ise soyisimlere göre sırala
		{
			if(strcmp(head->surname , n->surname) > 0)	//ilk sıraya yaz
			{
				n->next = head;
				head = n;
			}
			else							//ilk sıraya yazma
			{
				while(iter->next != NULL)	//araya yazma
				{
					if(strcmp(iter->next->surname , n->surname) > 0)
					{
						n->next = iter->next;
						iter->next = n;
						break;
					}
					iter = iter->next;
				}
				if(iter->next == NULL)		//sona yazma
				{
					iter->next = n;
				}
			}
		}
		else if(strcmp(head->name , n->name) > 0)	//ilk sıraya yaz
		{
			n->next = head;
			head = n;
		}
		else							//ilk sıraya yazma
		{
			while(iter->next != NULL)	//araya yazma
			{
				if(strcmp(iter->next->name , n->name) > 0)
				{
					n->next = iter->next;
					iter->next = n;
					break;
				}
				iter = iter->next;
			}
			if(iter->next == NULL)		//sona yazma
			{
				iter->next = n;
			}
		}
	}
}

void list(tp_teldefteri *iterF, tp_teldefteri *headF) {
    iterF = headF;
	for (int i = 1; iterF != NULL; i++)
	{
        cout <<i<<" "<< iterF->name << "\t" << iterF->surname << "\t" << iterF->phoneNumber << endl;
        iterF = iterF->next;
    }
    cout << endl;
}

void remove(int id){

	tp_teldefteri *temp;
	temp = head;

	if(id<=0)					//Geçersiz id
	{
		cout << "Please enter a valid record." << endl;
		return;
	}
	else if( id == 1)			//İlk sırayı sil
	{
		head=head->next;
		cop(temp);
		return;
	}
	
	iter = temp;
	if(temp == NULL)
	{
		cout << "Record is not found." << endl;
		return;
	}	

	for (int i = 0; i < id-1; ++i)
	{
		if(temp->next == NULL)
		{
			cout << "Record is not found." << endl;
			return;
		}
		iter = temp;
		temp = temp->next;
	}

	iter->next = temp->next;
	cop(temp);
}

void cop(tp_teldefteri *temp){
	delete [] temp->name;
	delete [] temp->surname;
	delete [] temp->phoneNumber;
	delete [] temp;
}

void update(int id){

	remove(id);
}

tp_teldefteri *search(char *arama){

	/*	cout << arama << endl;
	iterS = head;
	iterS->next = head->next;
*/
	
	//headS = head;

	
	iterS = head;
	for (int j = 1; strcmp(iterS->next->name, arama) > 0;j++)
	{
		for (int i = j; strncmp(arama, iterS->name, strlen(arama)) == 0;i++)
		{
			if (strncmp(arama, iterS->name, strlen(arama)) == 0)
			{
				if (headS == NULL)
				{
					headS = iterS;
					cout << i << " " << headS->name << "\t" << headS->surname << "\t" << headS->phoneNumber << endl;
					iterS = iterS->next;
					headS->next = iterS;
				}
				else
				{
					cout << i << " " << iterS->name << "\t" << iterS->surname << "\t" << iterS->phoneNumber << endl;
					iterS = iterS->next;
					if (strncmp(arama, iterS->name, strlen(arama)) != 0)
					{
						iterS = NULL;
						return headS;
					}
				}
				continue;
				
			}
			
		}
		iterS = iterS->next;
	}
	//iterS = NULL;

	
	return headS;
}