#import "dizi.h"
#import "kayit.h"
#import <string.h>
#import <stdio.h>
#import <stdlib.h>
#import <iostream>

#define MAX_SIZE 80

using namespace std;

typedef List Book;
typedef Record Rec;

void menu(){
	char entry;
	char *name;
	char *no;
	char *key;
	int index;

	Rec record;

	Book book;
	book.Create();
	while(1){
		cout << "*	Ekleme yapmak icin 'E'" << endl;
		cout << "*	silme yapmak icin 'S'," << endl;
		cout << "*	listelemek icin 'L'," << endl;
		cout << "*	arama yapmak icin 'A'," << endl;
		cout << "*	guncelleme yapmak icin 'G' harfini giriniz." << endl;
		cin >> entry;
		printf("\n");

		switch(entry){

			case 'E': case 'e':
				cout << "Isim ve numarayi arada bosluk birakarak giriniz: ";
				name = (char *)malloc(sizeof(char) * MAX_SIZE);
				no = (char *)malloc(sizeof(char) * MAX_SIZE);
				cin >> name >> no;
				record.Create(name, no);
				book.add(&record);
				break;
			case 'S': case 's':
				printf("Silmek istediğiniz insanin indisini giriniz: ");
				cin >> index;
				book.remove(index);
				break;
			case 'L': case 'l':
				book.list();
				break;
			case 'A': case 'a':
				printf("Aramak istediginiz anahtari giriniz: ");
				break;
			case 'G': case 'g':
				cout << "Lutfen guncellemek istediginiz indisi giriniz: ";
				cin >> index;
				cout << "Isim ve numarayi arada bosluk birakarak giriniz: ";
				cin >> name >> no;
				record.Create(name, no);
				book.update(index, name, no);
				break;
			default:
				cout << "Lutfen gecerli bir girdi giriniz." << endl;
				key = (char *)malloc(sizeof(char) * MAX_SIZE);
				cin >> key;
				book.search(key);
				break;
		}

		printf("\n");
	}
}

int main(){

	menu();

	/*
	Rec record;

	record.Create("Memos", "123");
	book.add(&record);

	record.Create("Taylan", "123");
	book.add(&record);

	record.Create("Ahmet", "123");
	book.add(&record);

	record.Create("Babakok", "123");
	book.add(&record);

	record.Create("Aleyna", "123");
	book.add(&record);

	record.Create("Tilki", "123");
	book.add(&record);

	record.Create("Umut", "123");
	book.add(&record);

	book.list();
	book.remove(4);
	printf("\n");
	book.list();
	book.remove(4);
	printf("\n");
	book.list();
	book.remove(4);
	printf("\n");
	book.list(); */



	return 0;
}