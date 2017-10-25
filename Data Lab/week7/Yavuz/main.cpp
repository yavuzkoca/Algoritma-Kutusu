#include <iostream>
#include "Stack.h"

using namespace std;

Stack s;

string convertToPostfix(string);
bool is_operand(char);
bool is_operator(char);
int comparePrecedence(char, char);
int weight(char);
float getValue(string);
float calculate(int, int, char);
int atoi(char);
char itoa(int);

int main(){
    s.create();
    string input;
    char c;

    cout << "Enter the input: ";
    getline(cin,input);
    string postfix = convertToPostfix(input);
    cout << "Postfix string is: " << postfix << endl;
    cout << "The value: " << getValue(postfix) << endl;
    s.close();
    return 0;
}


string convertToPostfix(string input){
    string postfix = "";
    for (int i = 0; i < input.length(); ++i) {

        if(input[i] == '('){
            s.push(input[i]);
        }

        else if(input[i] == ')'){
            while(!s.is_empty() && s.top() !=  '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }

        else if(is_operand(input[i])) {
            postfix += input[i];
        }

        else if(is_operator(input[i])){
            while(!s.is_empty() && s.top() != '(' && comparePrecedence(s.top(),input[i])) {
                postfix += s.top();
                s.pop();
            }
            s.push(input[i]);
        }
    }

    while(!s.is_empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

bool is_operand(char c){
    if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;

    return false;
}

bool is_operator(char c) {
    if(c == '+' || c == '-' || c == '*' || c == '/')
        return true;

    return false;
}

int comparePrecedence(char op1, char op2) {
    int w1 = weight(op1);
    int w2 = weight(op2);

    if(w1 == w2) return true;

    return w1 > w2;
}

int weight(char op) {
    int weight = -1;

    if(op == '+' || op == '-') weight = 1;
    else if(op == '*' || op == '/') weight = 2;

    return weight;
}

float getValue(string postfix){
    int x, y;
    float result;
    for(int i = 0; i < postfix.length(); i++){
        if(is_operator(postfix[i])){
            x = atoi(s.top());
            s.pop();
            y = atoi(s.top());
            s.pop();
            result = calculate(x, y, postfix[i]);
            s.push(itoa(result));
        }else{
            s.push(postfix[i]);
        }
    }
    return result;
}

float calculate(int x, int y, char op){
    if(op == '+')
        return x + y;
    if(op == '-')
        return y - x;
    if(op == '*')
        return x * y;
    if(op == '/')
        return y / x;
}

int atoi(char c){
    return c - '0';
}

char itoa(int i){
    return i + '0';
}