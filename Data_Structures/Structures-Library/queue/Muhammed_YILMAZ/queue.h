#ifndef QUEUE_H
#define QUEUE_H

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

#endif