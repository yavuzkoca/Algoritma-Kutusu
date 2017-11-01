#ifndef C_C_LIST_H
#define C_C_LIST_H

class List{
private:
    // Double Linked List declaration
    typedef struct studentInfo{
        char *surName;
        char *firstName;
        char *email; // I don't hold @itu.edu.tr part in this email char array
        studentInfo *next;
        studentInfo *prev;
    }*infoPtr;

    typedef struct surnameMap{
        char *surName;
        surnameMap *next;
        studentInfo *studentHead;
    }*nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;
    nodePtr temp2;

    infoPtr _head;
    infoPtr _curr;
    infoPtr _temp;
public:
    List();
    void addData(char*, char*);
    void addStudent(char*, surnameMap*);
    void printList();
    void printSurname(char*);
    bool deleteSurname(char*);
    bool deleteStudent(char*, char*);
    void writeToFile();
    void deleteAll();
};

#endif
