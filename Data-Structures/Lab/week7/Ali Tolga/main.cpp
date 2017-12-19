#include <iostream>
#include <cstring>
#include "Stack.h"

using namespace std;

void convertToPostfix();
void evaluatePostfix(char *postfix);
bool isOperator(char c);

int main()
{
	int run = 1;
	while (run)
	{
		convertToPostfix();
		cout << "Do you want to continue? Press 1 to continue, 0 to exit." << endl;
		cin >> run;
	}

	return 0;
}

void convertToPostfix()
{
	cout << "Please enter an infix expression." << endl;
	char *temp = new char[100];
	cin >> temp;
	if (strlen(temp) >= 100)
	{
		cout << "The expression is too long." << endl;
		return;
	}
	temp[strlen(temp)] = '\0';
	char *infix = new char[strlen(temp) + 1];
	strcpy(infix, temp);
	infix[strlen(infix)] = '\0';
	delete temp;
	char *postfix = new char[strlen(infix) + 1];
	cout << "Your infix expression is: " << infix << endl;
	stack mystack;
	mystack.create();
	int index = 0;
	for (unsigned int i = 0; i < strlen(infix); i++)
	{
		if (infix[i] >= '0' && infix[i] <= '9')
		{
			postfix[index] = infix[i];
			index++;
		}
		else if (isOperator(infix[i]))
		{
			if (infix[i] == '(' || mystack.isEmpty())
			{
				mystack.push(infix[i]);
			}
			else if (infix[i] == ')')
			{
				while (mystack.peek() != '(')
				{
					if (mystack.top == -1)
					{
						cout << "No opening paranthesis found. Deleting the infix expression..." << endl;
						return;
					}
					postfix[index] = mystack.pop();
					index++;
				}
				mystack.pop();
			}
			else
			{
				while (mystack.peek() == '*' || mystack.peek() == '/')
				{
					postfix[index] = mystack.pop();
					index++;
				}
				mystack.push(infix[i]);
			}
		}
		else
		{
			cout << "You have entered an invalid infix expression!" << endl;
			return;
		}
	}

	while (!mystack.isEmpty())
	{
		postfix[index] = mystack.pop();
		index++;
	}
	postfix[index] = '\0';
	cout << "Your postfix expression is: " << postfix << '\t';
	evaluatePostfix(postfix);
	
	delete[] infix;
	delete[] postfix;
}

void evaluatePostfix(char *postfix)
{
	int a, b;
	char c;
	stack result;
	result.create();
	for (unsigned int i = 0; i < strlen(postfix); i++)
	{
		if (postfix[i] >= '0' && postfix[i] <= '9')
		{
			result.push(postfix[i]);
		}
		else if (postfix[i] == '+')
		{
			b = result.pop() - '0';
			a = result.pop() - '0';
			a += b;
			c = a + '0';
			result.push(c);
		}
		else if (postfix[i] == '-')
		{
			b = result.pop() - '0';
			a = result.pop() - '0';
			a -= b;
			c = a + '0';
			result.push(c);
		}
		else if (postfix[i] == '*')
		{
			b = result.pop() - '0';
			a = result.pop() - '0';
			a *= b;
			c = a + '0';
			result.push(c);
		}
		else if (postfix[i] == '/')
		{
			b = result.pop() - '0';
			a = result.pop() - '0';
			a /= b;
			c = a + '0';
			result.push(c);
		}
	}
	cout << "Value is: " << result.pop() << endl;

}

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
		return true;
	return false;
}