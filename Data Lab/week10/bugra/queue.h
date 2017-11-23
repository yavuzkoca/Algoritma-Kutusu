typedef char QueueDataType;

struct QueueNode{
	QueueDataType data;
	QueueNode *next;
	int size;
};

struct Queue{
	QueueNode *front;
	QueueNode *back;
	bool enqueue(QueueDataType);
	QueueDataType dequeue();
	bool isEmpty();
	void create();
	void close();	
};