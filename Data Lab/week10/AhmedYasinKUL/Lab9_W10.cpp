#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3

using namespace std;

typedef char QueueDataType, StackDataType;

bool menu();
void add();
void remove();
void printStack();

struct cars{
	QueueDataType data;
	cars* next;
};

struct Queue{
	cars* front, *back;
	void create();
	void close();
	bool enqueue(QueueDataType);
	QueueDataType dequeue();
	bool isEmpty();
};


void Queue::create(){
	front = NULL; back = NULL;
}

void Queue::close(){
	
	cars *p;

	while (front) {
		p = front;
		front = front->next;
		delete p;
	}
}

bool Queue::enqueue(QueueDataType newdata){
	
	cars* newnode = new cars;
	newnode->data = newdata;
	newnode->next = NULL;
	
	if (isEmpty()) {
		back = newnode;
		front = back;
	}
	else {
		back->next = newnode;
		back = newnode;
	}
	return true;
}

QueueDataType Queue::dequeue() {
	
	cars *topnode;
	QueueDataType temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}

bool Queue::isEmpty() {
	return (front == NULL);
}

struct Stack{

	bool isEmpty();
	bool push(StackDataType);
	StackDataType pop();
	cars* head;
	int count;
	void create();
	bool isFull();
};

void Stack::create(){
	count = 0;
	head = NULL;
}

bool Stack::isEmpty(){
	return (count == 0);
}

bool Stack::isFull(){
	return (count == N);
}

bool Stack::push(StackDataType input){
	
	if(!isFull()){
		cars* newNode = new cars;
		newNode->data = input;
		newNode->next = NULL;
	
		if(head == NULL){
			head = newNode;
		}
		else{
			newNode->next = head;
			head = newNode;
		}

		count++;
		return true;
	}

	else{
		//cout << "This stack is full..." << endl;
		return false;
	}
	
}

StackDataType Stack::pop(){

	cars* ptr = head;
	StackDataType ret = head->data;
	head = head->next;
	delete ptr;
	count--;
	return ret;
}

Stack pL[5];
Queue que; 


int main(){
	while(!menu());
	return EXIT_SUCCESS;
}

bool menu(){
	cout << endl << "1) Add car" << endl;
	cout << 		"2) Depark car" << endl;
	cout << 		"3) Print parking lots" << endl;
	cout << 		"4) Exit\n" << endl;

	char c;
	cin >> c;

	if		(c == '1')	add();
	else if	(c == '2')	remove();
	else if	(c == '3')	printStack();
	else if	(c == '4')	return true;
	else				cout << "You have pressed wrong button. Please try again..." << endl;
	return false;
}

void add(){
	
	StackDataType input;
	cout << "Enter the the new car:" << endl;
	cin >> input;
	if((pL[0].count + pL[1].count + pL[2].count + pL[3].count) == N*4){
		cout << endl << "Our parking lots are full!!!" << endl << endl;
		return;
	}
	else{
		for(int i = 0; i < 4; i++)
			if(pL[i].push(input))		break;
		
		cout << "New car added." << endl;
	}
}

void printStack(){
	
	for(int i = 0; i < 4; i++){
		cout << endl << endl << "Stack " << i+1 << endl << endl;
		while(!pL[i].isEmpty()){
			pL[4].push(pL[i].pop());
			cout << (pL[4].head)->data << endl;
		}
		while(!pL[4].isEmpty()){
			pL[i].push(pL[4].pop());
		}
	}
}

void remove(){

	char plate, temp;
	bool found = false, parked, queBool = false;
	cin >> plate;

	for(int i = 0; i < 4; i++){
		
		while(!pL[i].isEmpty()){
			
			temp = pL[i].pop();
			parked = false;

			if(temp == plate){
				found = true;
				break;
			}

			else{

				for(int j = 0; j < 4; j++){
					if(j == i)	continue;
					if(pL[j].push(temp)){
						parked = true;
						break;
					}
				}

				if(!parked){
					que.enqueue(temp);
					//queBool = true;
				}
			}
		}

		if(!parked){
			while(!que.isEmpty())
				pL[i].push(que.dequeue());
		}

		if(found)	return;
	}
}