/*
cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << endl;
*/

#include <iostream>
#include <string.h>
#include "node.h"

using namespace std;

int comparisonNodes(const node * const node1, const node * const node2){

	return strcmp(node1->name, node2->name);
}

int comparisonValueForNode(const char * const deger1, const node * const node2){

	return strcmp(deger1, node2->name);
}

void ifSameNodeTitleHowAdd(node * toAdd, node * toNode, int * count){

	phoneNode *traverse = toNode->phone;
	bool added = false;
	while(!added)
	{
		if(traverse->next)
		{
			traverse = traverse->next;
		}
		else
		{
			traverse->next = toAdd->phone;
			added = true;
		}
	}

	//traverse = toAdd->phone;

	count++;
}

void showNode(const node * const nodeS){

	phoneNode *traverse = nodeS->phone;

	cout << nodeS->name << endl;
	while(traverse)
	{
		cout << "\t" << traverse->number << endl;
		traverse = traverse->next;
	}
}