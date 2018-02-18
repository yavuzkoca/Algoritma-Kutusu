#include <iostream>
#include "queue.h"
#include "node.h"

using namespace std;

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

	qNode *temp = front;

	while(temp)
	{
		yazdirQNode(temp);
		temp = temp->prev;
	}
	cout << endl;
}