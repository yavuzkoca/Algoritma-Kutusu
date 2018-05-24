#include <cstdlib>
#include <iostream>
#include "List.h"

using namespace std;

int main(){
    List list;
    list.addNode(5);
    list.addNode(1);
    list.printList();
    list.addNode(2);
    list.printList();
    list.addNode(9);
    list.deleteNode(1);
    list.printList();
    list.deleteNode(10);

    return 0;
}