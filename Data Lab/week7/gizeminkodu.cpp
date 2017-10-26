#include <iostream>
#include <string>

using namespace std;

const int SIZE = 30;

template <typename T>
struct Stack{
    
    T* op;
    int top;
    void create();
    T pop();
    void push(T);
    bool is_empty();
    
};

template <typename T>
void Stack<T>::create(){
    
    op = new T[SIZE];
    top = 0;
    
}

template <typename T>
T Stack<T>::pop(){
    
    return op[--top];
    
}

template <typename T>
void Stack<T>::push(T o){
    
    if (top < SIZE)
        op[top++] = o;
    
    else cerr << "Error! Stack size is exceeded." << endl;
    
}

template <typename T>
bool Stack<T>::is_empty(){
    
    return (top==0);
    
}

Stack<double>* math_stack = new Stack<double>;


double do_the_math(double x, double y, char o){
    
    if(o=='/')
        return x/y;
    else if(o=='*')
        return x*y;
    else if(o=='+')
        return x+y;
    else if(o=='-')
        return y-x;
    else
        return -1;
}

int precedence(char o){
    
    switch (o){
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default: return 0;
    }
    
}

bool is_higher(char x, char y){

    return (precedence(x)>=precedence(y));
    
}

void do_the_calculation(string pf){
    
    if (pf == "") return;
    
    int i = 0;
    
    while (pf[i] != '+' && pf[i] != '-' && pf[i] != '*' && pf[i] != '/'){
        math_stack->push((double)pf[i]-48.0);
        i++;
    }
    
    if(math_stack->top <= 1) return;
    double result = do_the_math(math_stack->pop(), math_stack->pop(), pf[i]);
    math_stack->push(result);
    //cout << pf << " " << result << endl;
    pf.erase(0,i+1);
    
    do_the_calculation(pf);
    
}

int main(){
    
    Stack<char>* new_stack;
    new_stack = new Stack<char>;
    new_stack->create();
    string postfix;
    string screen;
    
    cout << "Infix: ";
    cin >> screen;
    
    //cout << screen.length() << endl;
    
    for(int i = 0; i<screen.length(); i++){
        
        if(isdigit(screen[i])) postfix += screen[i];
        
        else if (screen[i] == '(') new_stack->push(screen[i]);
        
        else if (screen[i] == '+' || screen[i] == '-' || screen[i] == '*' || screen[i] == '/'){
            
            if(new_stack->is_empty())
                new_stack->push(screen[i]);
            
            else{
            
                while(is_higher(new_stack->op[new_stack->top - 1],screen[i]))
                    postfix += new_stack->pop();
                
            
                if(!(is_higher(new_stack->op[new_stack->top - 1],screen[i])))
                    new_stack->push(screen[i]);
            }
        }
        
        else if(screen[i] == ')'){
            
            char pop = new_stack->pop();
            while(!new_stack->is_empty() && pop != '('){
                
                postfix += pop;
                pop = new_stack->pop();
                
            }
            
        }
        
        else cout << "wrong character or equation form." << endl;
    }
    

    while(!new_stack->is_empty())
        postfix += new_stack->pop();

    
    cout << "Postfix: " << postfix << endl;
    math_stack->create();
    do_the_calculation(postfix);
    cout << "Result: " << math_stack->pop() << endl;
    return 0;
    
}
