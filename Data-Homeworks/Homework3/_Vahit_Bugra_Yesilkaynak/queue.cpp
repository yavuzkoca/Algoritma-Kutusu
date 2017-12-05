#include "queue.h"

bool Queue::enqueue(DataType &data){
	QueueNode *new_node = new QueueNode;
	new_node->next = 0;
	new_node->data = data;
	if(!isEmpty()) { back->next = new_node; back = new_node; }
	else{ back = new_node; front = new_node; }
	return true;
}

DataType Queue::dequeue(){
	DataType temp;
	temp = front->data;
	QueueNode *temp_node = front;
	front = front->next;
	delete temp_node;
	return temp;
}

bool Queue::isEmpty(){ return front == 0 ? true : false; }
void Queue::create(){ front = 0; back = 0; }
void Queue::close(){ while(!isEmpty()) dequeue(); }