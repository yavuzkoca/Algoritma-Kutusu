#ifndef STACK_H
#define STACK_H

#define MAXSIZE 100

struct stack
{
	void create();
	void push(char c);
	char pop();
	char peek();
	bool isEmpty();
	bool isFull();
	int top;
	char mystring[MAXSIZE];
};

#endif // STACK_H