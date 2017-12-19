#include "stack.h"
#include <iostream>

using namespace std;

void Stack::push(StackDataType data){
	StackNode *new_node = new StackNode;
	new_node->data = data;
	new_node->next = top;
	top = new_node;
}

StackDataType Stack::pop(){
	if(isEmpty()) return 0;
	StackDataType temp;
	temp = top->data;
	StackNode *temp_node = top;
	top = top->next;
	delete temp_node;
	return temp;
}

void Stack::print(){
	StackNode *traverser = top;
	cout << "***" << endl;
	if(traverser == NULL) cout << '-' << endl;
	while( traverser != NULL ){
		cout << traverser->data << endl;
		traverser = traverser->next;
	}
	cout << "***" << endl << endl;
}

bool Stack::isEmpty(){ return top == 0 ? true : false; }
void Stack::create(){ top = 0; }
void Stack::close(){ while(!isEmpty()) pop(); }