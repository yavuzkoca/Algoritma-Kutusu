#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Tree.h"

using namespace std;

Tree t;
void print_menu();
bool operation(char);
void add();
void print();
void update();
void del();
void delAll();

int main(){
    bool finish = false;
    char op;
    while (!finish) {
        print_menu();
        cin >> op;
        finish = operation(op);
    }

    // t.add_node(t.root, "ata", "0541");

    // t.remove("ata");
    // t.remove("ali");
    // t.remove("yavuz");
    // t.update("ata", "dilara");
    //t.print_in_order(t.root);

    t.root = t.deleteAll(t.root);

    return 0;
}

void print_menu(){
    cout << endl << endl;
    cout << "Patient Application" << endl;
    cout << "Choose an operation" << endl;
    cout << "A: Add Contact" << endl;
    cout << "L: Print" << endl;
    cout << "U: Update" << endl;
    cout << "D: Delete" << endl;
    cout << "S: Delete All" << endl;
    cout << "E: Exit" << endl;
    cout << endl;
    cout << "Enter an option {A, E, S} : ";
}

bool operation(char c){
    bool finish = false;
    if(c >= 'a' && c <= 'z')
        c = c - 'a' + 'A';
    if(c == 'E')
        finish = true;
    else if(c == 'A')
        add();
    else if(c == 'L')
        print();
    else if(c == 'U')
        update();
    else if(c == 'D')
        del();
    else if(c == 'S')
        delAll();

    return finish;
}

void add(){
    char name[500],number[500];
    cout << "Enter the name of the contact: ";
    cin >> name;
    cout << "Enter the number: ";
    cin >> number;
    t.add_node(t.root, name, number);
}

void print(){
    t.print_in_order(t.root);
}

void update(){
    char name[500], tar[500];
    cout << "Enter the name you want to update: ";
    cin >> name;
    cout << "Enter new name: ";
    cin >> tar;
    t.update(name, tar);
}

void del(){
    char name[500];
    cout << "Enter the name you want to delete: ";
    cin >> name;
    t.remove(name);
}

void delAll(){
    t.deleteAll(t.root);
}