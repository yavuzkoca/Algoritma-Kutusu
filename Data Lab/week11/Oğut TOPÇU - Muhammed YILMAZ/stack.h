#ifndef STACK_H
#define STACK_H


struct coordinate
{
	int y;
	int x;
	coordinate *prev;	
};

struct stack
{
	coordinate *tepeEleman;
	void create();
	void push(int y, int x);
	void pull();
	void show();
	coordinate *top();
};
#endif