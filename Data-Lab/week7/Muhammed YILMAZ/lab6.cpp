#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "lab6.h"

using namespace std;

stack *headStack = NULL;
stack *headOprtr = NULL;
stackI *headOprnd = NULL;
stackI *headCalculate, *tailCalculate;

/*********************FUNC_H*********************/
	int opcmp(char op1, char op2);
	int opPrec(char op);
	void creatPostfix(char *infiX, char *postfiX);
	float calculateResult(char *postfiX);
	void push(char oprtr);
	char pop(char *postfiX, int i);
	void printStack(stack *headS);
	float calculateOp(int a, char op, int b);
/*********************FINISH*********************/

int main(){

	char *infix;
	infix = new char[100];
	cout << "Infix -> ";
	cin >> infix;

	char *postfix;
	postfix = new char[100];
	creatPostfix(infix, postfix);
	cout << "Postfix -> " << postfix << endl;

	int result;
	result = calculateResult(postfix);
	cout << "Result -> " << result << endl;

	delete [] infix;
	delete [] postfix;
}

/*********************FUNC_H*********************/
float calculateOp(float a, char op, float b){

	switch(op)
	{
		case '+':
		return a+b;
		case '-':
		return a-b;
		case '*':
		return a*b;
		case '/':
		return a/b;
		default:
		cout << "invalid operation in \"calculateOp(a,op,b)\"" << endl;
	}
}

void printStack(stack *headS){

	stack *iter = headS;
	cout << "Stack -> ";
	while(iter != NULL)
	{
		cout << iter->oprtr;
		iter = iter->next;
	}
	cout << endl;
}

char pop(char *postfiX, int i){

	postfiX[i] = headStack->oprtr;
	stack *trash;
	trash = headStack;
	headStack = headStack->next;
	delete trash;
	return postfiX[i];
}

void push(char oprtr){

	stack *newOprtr;
	newOprtr = new stack;
	newOprtr->oprtr = oprtr;
	newOprtr->next = headStack;
	headStack = newOprtr;
}

float calculateResult(char *postfiX){
	
	float stack[20];
	int top = -1;
	
	float n1,n2,n3,num;
	while(*postfiX != '\0')
	{
		if(isdigit(*postfiX))
		{
			num = *postfiX - 48;
			stack[++top] = num;
		}
		else
		{
			n1 = stack[top--];
			n2 = stack[top--];
			//cout << n2 << *postfiX << n1 << endl;
			switch(*postfiX)
			{
				case '+':
				{
					n3 = n1 + n2;
					break;
				}
				case '-':
				{
					n3 = n2 - n1;
					break;
				}
				case '*':
				{
					n3 = n1 * n2;
					break;
				}
				case '/':
				{
					n3 = n2 / n1;
					break;
				}
			}
			stack[++top] = n3;
		}
		postfiX++;
	}
	return stack[top--];
}

void creatPostfix(char *infiX, char *postfiX){

	int j = 0;
	for (int i = 0; i < strlen(infiX); ++i)
	{
		if(opPrec(infiX[i]) == 0)
		{
			postfiX[j] = infiX[i];
			j++;
		}
		else
		{
			if(headStack == NULL || opPrec(infiX[i]) == -1)
			{
				push(infiX[i]);
			}
			else if(opPrec(infiX[i]) == -2)
			{
				while(opPrec(pop(postfiX, j)) != -1)
				{
					//pop(postfiX, j);
					j++;
				}
				//j--;
				//postfiX[j] = '\0';

			}
			else if(opPrec(infiX[i]) != -1)
			{//burada
				while(headStack != NULL && (opcmp(infiX[i], headStack->oprtr) < 0 || opcmp(infiX[i], headStack->oprtr) == 0))
				{
					pop(postfiX, j);
					j++;
				}
				push(infiX[i]);
			}
			else
			{
				push(infiX[i]);
			}
		}
	}
	while(headStack!=NULL)
	{
		pop(postfiX, j);
		j++;
	}
}

int opcmp(char op1, char op2){

	if(opPrec(op1) == opPrec(op2))
		return 0;
	else if(opPrec(op1) > opPrec(op2))
		return 1;
	else 
		return -1;
	// return op1 - op2;
}

int opPrec(char op){

	switch(op)
	{
		case '+':
		return 1;
		case '-':
		return 1;
		case '*':
		return 2;
		case '/':
		return 2;
		case '(':
		return -1;
		case ')':
		return -2;
		default:
		return 0;
	}
}
/*********************FINISH*********************/