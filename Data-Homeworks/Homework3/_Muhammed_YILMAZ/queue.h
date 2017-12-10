#ifndef QUEUE_H
#define QUEUE_H

#define COMP_RED 3
#define COMP_GREEN 2
#define COMP_YELLOW 1
#define NAME_LENGHT 20
#define COMP_LENGHT 7

struct qNode
{
	char name[NAME_LENGHT];
	int arrival;
	int treatment;
	char complaint[COMP_LENGHT];
	qNode *prev;
};

struct qQueue
{
	qNode *front;
	qNode *back;
	void create();
	bool isEmpty();
	bool enqueue(qNode);
	qNode dequeue();
	void show();
	void close();
};

bool yazdirQNode(qNode *temp);
#endif