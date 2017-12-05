#include "patient.h"

typedef Patient DataType;

struct QueueNode{
	DataType data;
	QueueNode *next;
};

struct Queue{
	QueueNode *front;
	QueueNode *back;
	bool enqueue(DataType &);
	DataType dequeue();
	bool isEmpty();
	void create();
	void close();	
};