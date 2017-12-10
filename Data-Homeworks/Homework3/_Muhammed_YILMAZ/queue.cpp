#include <iostream>
#include <cstring>
#include "queue.h"

using namespace std;



/******************YARDIMCI_FONKSIYONLAR******************/
/* Queue fonksiyonları sabittir. Node yapisina 
 * gore sadece yardimci fonksiyonlar degistirilir.
 */
void aktarQNode(qNode *newNode, qNode newData){

	//newNode->name = new char[NAME_LENGHT];
	strcpy(newNode->name, newData.name);
	newNode->arrival = newData.arrival;
	newNode->treatment = newData.treatment;
	strcpy(newNode->complaint, newData.complaint);
	newNode->prev = NULL;
}

void silQNode(qNode* trash){

	//delete [] trash->name;
	delete trash;
}

bool yazdirQNode(qNode *temp){

	cout << temp->name << "\t" << temp->arrival << "\t"
		 << temp->treatment << "\t" << temp->complaint << endl;
}



/*******************QUEUE_FONKSIYONLARI*******************/
void qQueue::create(){

	front = NULL;
	back = NULL;
}

// Liste temizlenir.
void qQueue::close(){

	qNode *trash;
	while(front)
	{
		trash = front;
		front = front->prev;
		silQNode(trash);
	}
}

// Listeye yeni eleman (sona) eklenir.
bool qQueue::enqueue(qNode newData){

	qNode *newNode = new qNode;
	aktarQNode(newNode, newData);

	if( isEmpty() )
	{
		back = newNode;
		front = newNode;
	}
	else
	{
		back->prev = newNode;
		back = newNode;
	}
}

// Listenin basindaki eleman silinir.
qNode qQueue::dequeue(){
	

	if(!isEmpty())
	{
		// Geri döndürülecek veri hazırlanır.
		qNode temp;
		aktarQNode(&temp, *front);

		// Silme işlemi gerçekleştirilir.
		qNode *trash = front;
		front = front->prev;
		silQNode(trash);

		// Son silme işlemi ile liste boşaldıysa back'de NULL'a eşitlenir.
		if(isEmpty())
			back = NULL;

		return temp;
	}
	cout << "List is empty, cannot be dequeued!" << endl;
}

bool qQueue::isEmpty(){

	return front == NULL;
}

// Liste ekrana yazdirilir.
void qQueue::show(){

	if(isEmpty())
	{
		cout << "List is empty, cannot be showed!" << endl;
		cout << endl;
		return;
	}

	cout << "Name\t\tArriv.\tTreat.\tComplaint" << endl;
	qNode *temp = front;

	while(temp)
	{
		yazdirQNode(temp);
		temp = temp->prev;
	}
	cout << endl;
}