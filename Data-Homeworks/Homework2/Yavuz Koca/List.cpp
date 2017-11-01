#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "List.h"

using namespace std;

List::List(){
    // This parts stands for createList function that you asked in the pdf
    head = NULL;
    curr = NULL;
    temp = NULL;
    _head = NULL;
    _curr = NULL;
    _temp = NULL;
}

void List::addData(char *surName, char *firstName) {
    // This function adds Surname to Circular Linked List
    nodePtr n = new surnameMap;
    n->next = NULL;
    n->studentHead = NULL;
    n->surName = new char[strlen(surName)+1];
    strcpy(n->surName,surName);
    n->surName[strlen(n->surName)] = '\0';
    int cnt = 0;
    if(head != NULL){
        // If new surname is going to be new head
        if(strcmp(n->surName, head->surName) > 0 ) {
            temp = head->next;
            head->next = n;
            n->next = temp;
            head = n;
            addStudent(firstName, n);
            return;
        }

        curr = head;
        // Move in the list for the relevant position
        while(curr->next != head && strcmp((curr->next)->surName, n->surName) < 0)
            curr = curr->next;

        // If this surname not exist in the list, add this surname
        if(strcmp((curr->next)->surName, n->surName) != 0){
            temp = curr->next;
            curr->next = n;
            n->next = temp;
            addStudent(firstName, n);
        }else{
            // If this surname exist in the list, then add student to this surname
            addStudent(firstName, curr->next);
        }

    }else{
        // Add first surname to the list
        head = n;
        n->next = head;
        addStudent(firstName,head);
    }
}

void List::addStudent(char* firstName, surnameMap* node){
    // This function takes firstName and Surname pointer to be added into
    infoPtr n = new studentInfo;
    n->next = NULL;
    n->prev = NULL;

    n->surName = new char[strlen(node->surName)+1];
    strcpy(n->surName, node->surName);
    n->surName[strlen(n->surName)] = '\0';

    n->firstName = new char[strlen(firstName)+1];
    strcpy(n->firstName, firstName);
    n->firstName[strlen(n->firstName)] = '\0';

    // At first, email is equal to surname.
    n->email = new char[strlen(n->surName)+1];
    memset(n->email, 0, sizeof(n->email));
    strcpy(n->email, n->surName);
    n->email[0] = tolower(n->email[0]);
    n->email[strlen(n->email)] = '\0';

    if(node->studentHead != NULL){
        _curr = node->studentHead;
        size_t letter = 1;
        int numb = 2;

        string t(n->email);
        t += tolower(n->firstName[0]);
        n->email = new char(strlen(n->email)+2);
        strcpy(n->email,t.c_str());
        n->email[strlen(n->email)] = '\0';

        // Find proper position for this email to be added
        while(_curr->next != NULL && strcmp(_curr->next->email, n->email) <= 0 ){
            // If this email exist in the list
            if(strcmp(_curr->next->email, n->email) == 0){
                string t(n->email);
                // First, go to else statement of this if statement.
                // If all letters of the first name is added to email, then add number to this email.
                if(letter >= strlen(n->firstName)){
                    // This adding number stuff to email works for one and two digits.
                    // For example you cant see this kind of email: kocayavuz100@itu.edu.tr
                    if(t[t.length()-1] < '9' &&  t[t.length()-1] >= '0'){
                        t[t.length()-1] = numb + '0';
                    }else if(t[t.length()-1] == '9'){
                        if(t[t.length()-2] < '9' && t[t.length()-2] >= '0'){
                            t[t.length()-2] += 1;
                            t[t.length()-1] = '0';
                        }else{
                            t[t.length()-1] = '1';
                            t += '0';
                        }
                    }else{
                        t += numb + '0';
                    }
                    if(numb > 9) numb = 0;
                    numb++;
                }else{
                    // Add first letter of the name to this email and move forward in the list.
                    if(n->firstName[letter] == ' ' || n->firstName[letter] == '\t') letter++;
                    t += tolower(n->firstName[letter]);
                    letter++;
                }
                n->email = new char(strlen(n->email) + letter + numb);
                strcpy(n->email, t.c_str());
                n->email[strlen(n->email)] = '\0';
            }
            _curr = _curr->next;
        }
        n->next = _curr->next;
        if(_curr->next)
            _curr->next->prev = n;
        n->prev = _curr;
        _curr->next = n;

    }else
        node->studentHead = n;
}

void List::printList() {
    curr = head;
    if(curr){
        do{
            cout << curr->next->surName << endl;
            _curr = curr->next->studentHead;
            while(_curr != NULL){
                printf("\t");
                for(int i=0; i<strlen(_curr->firstName); i++){
                    if(_curr->firstName[i] != '\r')
                        printf("%c", _curr->firstName[i]);
                }
                printf(" -> ");
                for(int i=0; i<strlen(_curr->email); i++){
                    if(_curr->email[i] != '\r')
                        printf("%c", _curr->email[i]);
                }
                printf("@itu.edu.tr\n");
                _curr = _curr->next;
            }
            cout << endl;
            curr = curr->next;
        }while(curr->next != head->next);
    }
}

void List::printSurname(char s[]) {
    curr = head;
    if(curr){
        do{
            int size;
            if(strlen(s) > strlen(curr->surName)) size = strlen(s);
            else size = strlen(curr->surName);
            if(strncmp(curr->surName, s, size-1) == 0){
                for(int i=0; i<strlen(curr->surName); i++){
                    if(curr->surName[i] != '\r')
                        printf("%c", curr->surName[i]);
                }
                cout << endl;
                _curr = curr->studentHead;
                while(_curr != NULL){
                    printf("\t");
                    for(int i=0; i<strlen(_curr->firstName); i++){
                        if(_curr->firstName[i] != '\r'){
                            printf("%c", _curr->firstName[i]);
                        }
                    }
                    printf(" -> ");
                    for(int i=0; i<strlen(_curr->email); i++){
                        if(_curr->email[i] != '\r'){
                            printf("%c", _curr->email[i]);
                        }
                    }
                    printf("@itu.edu.tr\n");
                    _curr = _curr->next;
                }
                return;
            }
            curr = curr->next;
        }while(curr != head);
    }
    cout << "\nWe couldn't find this surname. Please make sure you entered first letter as capital!\n";
}

void List::writeToFile(){
    FILE *file;
    file = fopen("emailList.txt","w+");
    curr = head;
    if(curr){
        do{
            _curr = curr->next->studentHead;
            while(_curr != NULL){
                for(int i=0; i<strlen(_curr->surName); i++)
                    if(_curr->surName[i] != '\r')
                        fprintf(file,"%c",_curr->surName[i]);
                fprintf(file," ");
                for(int i=0; i<strlen(_curr->firstName); i++)
                    if(_curr->firstName[i] != '\r')
                        fprintf(file,"%c",_curr->firstName[i]);
                fprintf(file," ");
                for(int i=0; i<strlen(_curr->email); i++)
                    if(_curr->email[i] != '\r')
                        fprintf(file,"%c",_curr->email[i]);

                fprintf(file, "@itu.edu.tr\n");
                _curr = _curr->next;
            }
            curr = curr->next;
        }while(curr->next != head->next);
    }
}

bool List::deleteSurname(char input[]){
    curr = head;
    temp = curr;
    nodePtr delPtr = NULL;
    char *t;
    if(curr) do{
            t = new char[strlen(curr->surName)+1];
            memset(t, 0, sizeof(t));
            strcpy(t, curr->surName);
            t[0] = tolower(t[0]);
            input[0] = tolower(input[0]);
            int size;
            if(strlen(t) > strlen(input)) size = strlen(t);
            else size = strlen(input);

            // If there is this surname
            if(strncmp(t, input, size-1) == 0){
                // Go to students with this surname and delete them
                _curr = curr->studentHead;
                while(_curr != NULL){
                    _temp = _curr;
                    _curr = _curr->next;
                    delete _temp;
                }
                temp->next = curr->next;
                // If this surname is the only one in the circular linked list
                if(head == curr && head->next == head){
                    head = NULL;
                }else if(head == curr){
                    // If this surname is the head, assign new head of this circular linked list.
                    // Go to previous element of this head and make it head. temp2 is the previous node of the head.
                    temp2 = head;
                    while(temp2->next != head)
                        temp2 = temp2->next;
                    temp2->next = head->next;
                    delete head;
                    head = temp2;
                }else{
                    delete curr;
                }
                return 1;
            }else{
                temp = curr;
                curr = curr->next;
            }
            delete[] t;
        }while(curr != head);
    return 0;
}

bool List::deleteStudent(char s[], char email[]) {
    curr = head;
    temp = curr;
    nodePtr delPtr = NULL;
    char *t;
    if(curr) do{
            t = new char[strlen(curr->surName)+1];
            memset(t, 0, sizeof(t));
            strcpy(t, curr->surName);
            t[0] = tolower(t[0]);
            s[0] = tolower(s[0]);

            int size;
            if(strlen(t) > strlen(s)) size = strlen(t);
            else size = strlen(s);

            if(strncmp(t, s, size-1) == 0){
                _curr = curr->studentHead;
                _temp = _curr;
                while(_curr != NULL){
                    if(strcmp(_curr->email, email) == 0){
                        if(_temp == _curr)
                            curr->studentHead = _curr->next;
                        else
                            _temp->next = _curr->next;
                        delete _curr;
                        break;
                    }
                    _temp = _curr;
                    _curr = _curr->next;
                }
                if(curr->studentHead == NULL){ // If we deleted last student of this surname node.
                    // This part almost same as deleting a surname. Necessary explanation
                    if(head == curr && head->next == head){
                        head = NULL;
                    }else if(head == curr){
                        temp2 = head;
                        while(temp2->next != head)
                            temp2 = temp2->next;
                        temp2->next = head->next;
                        delete head;
                        head = temp2;
                    }else{
                        temp->next = curr->next;
                        delete curr;
                    }
                }
                return 1;
            }else{
                temp = curr;
                curr = curr->next;
            }
            delete[] t;
        }while(curr != head);
    return 0;
}

void List::deleteAll() {
    if(head == NULL) return;

    curr = head;
    temp = curr;
    do{
        temp = curr;
        if(temp->studentHead != NULL){
            _curr = temp->studentHead;
            while(_curr != NULL){
                _temp = _curr;
                _curr = _curr->next;
                delete _temp;
            }
            _curr = NULL;
        }

        curr = curr->next;
        delete temp;
    }while(curr != head);
    head = NULL;
}