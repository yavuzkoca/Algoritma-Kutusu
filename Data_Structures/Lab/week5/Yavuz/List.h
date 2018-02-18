#ifndef C_C_LIST_H
#define C_C_LIST_H

class List{
private:
    typedef struct node{
        char *name;
        char *number;
        int data;
        node * next;
    }*nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;
public:
    List();
    void addData(char*, char*);
    void printList();
    bool deleteRecord(char*);
    bool updateRecord(char*);
    void deleteAll();
};

#endif
