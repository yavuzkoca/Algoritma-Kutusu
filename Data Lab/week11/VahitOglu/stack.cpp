#include <iostream>
#include "stack.h"

void Stack::push(StackDataType data){
	StackNode *new_node = new StackNode;
	new_node->data = data;
	new_node->next = top;
	top = new_node;
}

StackDataType Stack::pop(){
	StackDataType temp;
	temp = top->data;
	StackNode *temp_node = top;
	top = top->next;
	delete temp_node;
	return temp;
}

void Stack::print(){
	StackNode *traverser = top;
	while( traverser != 0 ){
		std::cout << traverser->data.i << " " << traverser->data.j << std::endl;
		traverser = traverser->next;
	}
}

bool Stack::isEmpty(){ return top == 0 ? true : false; }
void Stack::create(){ top = 0;}
void Stack::close(){ while(!isEmpty()) pop(); }