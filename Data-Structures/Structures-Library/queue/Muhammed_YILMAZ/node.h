#ifndef NODE_H
#define NODE_H



struct qNode
{
	/*
	 * Node içeriği buraya yazılacak
	char name[NAME_LENGHT];
	int arrival;
	int treatment;
	char complaint[COMP_LENGHT];
	 */
	char name[15];

	qNode *prev;
};

void aktarQNode(qNode *newNode, qNode newData);
void silQNode(qNode* trash);
bool yazdirQNode(qNode *temp);
#endif