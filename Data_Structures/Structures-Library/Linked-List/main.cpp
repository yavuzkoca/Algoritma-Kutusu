#include <cstdlib>
#include <iostream>
#include "List.h"

using namespace std;

int main(){
    List list;
    list.addNodeToBeginning(2);
    list.addNode(5);
    list.addNodeToBeginning(7);
    list.addNode(1);
    list.printList();


    return 0;
}