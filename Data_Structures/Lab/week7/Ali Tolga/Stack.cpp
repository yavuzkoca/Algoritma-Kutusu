#include "Stack.h"
#include <iostream>

void stack::create()
{
	top = -1;
}

void stack::push(char c)
{
	if (top == MAXSIZE - 1)
	{
		std::cout << "The stack is full!" << std::endl;
		return;
	}
	top++;
	mystring[top] = c;
}

char stack::pop()
{
	if (top == -1)
	{
		std::cout << "There are no elements to pop!" << std::endl;
	}
	top--;
	return mystring[top + 1];
}

char stack::peek()
{
	return mystring[top];
}

bool stack::isEmpty()
{
	if (top == -1)
	{
		return true;
	}
	return false;
}

bool stack::isFull()
{
	if (top == MAXSIZE - 1)
	{
		return true;
	}
	return false;
}
