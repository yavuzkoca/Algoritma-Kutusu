#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

// Stack with linked-list implemantation
// Generic implemantation

template <typename T> 
class stack{
private:
    struct node{
        T data;
        node *next;
        node(T t){ data = t, next=NULL;}
        node(){next=NULL;}
    };
    node *head;
    unsigned int size;
public:
    stack(){ size=0,head = NULL;}
    ~stack(){ 
        auto trv = head;
        while(head!=NULL){
            trv = head->next;
            delete head;
            head = trv;
        }
    }
    void push(T t){
        if(head){
            auto n = new node(t);
            n->next = head;
            head = n;
        }
        else{
            head = new node(t);
        }
        size++;
    }
    T pop(){
        // You can retrun dumy variable instead of throwing exception,
        // Or you can write two seperated methods like top and pop in STL.
        if(head==NULL) {
            throw "Stack empty";
        }
        auto res = head->data;
        auto new_head = head->next;
        delete head;
        head = new_head;
        size--;
        return res;
    }
    bool isEmpty(){ return head==NULL;}
    unsigned int getSize(){return size;} 
};  


#endif 
