#ifndef C_C_LIST_H
#define C_C_LIST_H


class List{
private:
    typedef struct nodeNumber {
        char *num;
		char type[15];
        int kind; // 0 for home, 1 for work, 2 for cell Phone
        nodeNumber *next;
    } *numPtr;

    typedef struct node{
        char *name;
        node *next;
        node *prev;
        nodeNumber *phoneNumb;
    }*nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;
    nodePtr tail;
    numPtr headNumb;
    numPtr currNumb;
    numPtr tempNumb;
	numPtr delNumb;

public:
    List();
    void addRecord(char*, char*, char*);
    void printListForward();
    void printListBackward();
    bool deleteRecord(char*);
	bool deleteNumber(char*);
    bool updateNumb(char*);
	bool updateName(char*);
    void deleteAll();
};

#endif
