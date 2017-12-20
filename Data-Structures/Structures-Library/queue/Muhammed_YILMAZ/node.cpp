#include <iostream>
#include <cstring>
#include "node.h"


/******************YARDIMCI_FONKSIYONLAR******************/
/* Queue fonksiyonları sabittir. Node yapisina 
 * gore sadece yardimci fonksiyonlar degistirilir.
 */
void aktarQNode(qNode *newNode, qNode newData){

	/*
	 * İki nodu kopyalama işlemi burada yaoılacak
	strcpy(newNode->name, newData.name);
	newNode->arrival = newData.arrival;
	newNode->treatment = newData.treatment;
	strcpy(newNode->complaint, newData.complaint);
	*/
	strcpy(newNode->name, newData.name);


	newNode->prev = NULL;
}

void silQNode(qNode* trash){
	/* 
	 * node'u silme islemi burada yaoılacak
	 */
	delete trash;
}

bool yazdirQNode(qNode *temp){

	/* 
	 *Node'u yazdirma islemi burada yapilacak
	cout << temp->name << "\t" << temp->arrival << "\t"
		 << temp->treatment << "\t" << temp->complaint << endl;
	*/
	cout << qNode->name << endl;
}