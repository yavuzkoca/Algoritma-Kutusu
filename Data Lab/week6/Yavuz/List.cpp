#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include "List.h"

using namespace std;

List::List(){
    head = NULL;
    curr = NULL;
    temp = NULL;
}

void List::addRecord(char *name, char* number, char* type) {
    nodePtr n = new node;
    numPtr newNumber = new nodeNumber;

    n->next = NULL;
    n->prev = NULL;
    newNumber->next = NULL;

    n->name = new char[strlen(name)+1];
    newNumber->num = new char[strlen(number)+1];

    strcpy(n->name,name);
    strcpy(newNumber->num,number);
	strcpy(newNumber->type, type);

    if(head != NULL){
        curr = head;
        if(strcmp(n->name, head->name) < 0 ) {
            n->next = head;
            n->phoneNumb = newNumber;
            head = n;
            (n->next)->prev = n;
        }else {
            while (curr->next != NULL && strcmp((curr->next)->name, n->name) < 0){
                curr = curr->next;
            }
            if (curr->next != NULL && strcmp(curr->next->name, n->name) == 0){
                currNumb = curr->next->phoneNumb;
                while(currNumb->next != NULL)
                    currNumb = currNumb->next;
                currNumb->next = newNumber;
            }
            else if(strcmp(curr->name, n->name) == 0){
                currNumb = curr->phoneNumb;
                while(currNumb->next != NULL)
                    currNumb = currNumb->next;
                currNumb->next = newNumber;
            }else{
                temp = curr->next;
                curr->next = n;
                n->next = temp;
                n->prev = curr;
                n->phoneNumb = newNumber;
                if (temp != NULL)
                    temp->prev = n;
                if (n->next == NULL) tail = n;
            }
        }
    }else{
        head = n;
        tail = n;
        n->phoneNumb = newNumber;
    }
}

void List::printListForward() {
    curr = head;
    while(curr != NULL){
        currNumb = curr->phoneNumb;
        cout << curr->name << " ";
        while(currNumb != NULL){
			cout << currNumb->type << " ";
            cout << currNumb->num << " " ;
            currNumb = currNumb->next;
        }
        cout << endl;
        curr = curr->next;
    }
    cout << endl;
}

void List::printListBackward() {
    curr = tail;
    while(curr != NULL){
        currNumb = curr->phoneNumb;
        cout << curr->name << " ";
        while(currNumb != NULL){
            cout << currNumb->num << " ";
            currNumb = currNumb->next;
        }
        cout << endl;
        curr = curr->prev;
    }
    cout << endl;
}

bool List::deleteRecord(char input[]){
    curr = head;
    temp = head;
    nodePtr delPtr = NULL;
    char ch;
	int i = 0;
    while(curr != NULL){
		i++;
        if(strncmp(curr->name,input,strlen(input)) == 0){
            printf("We have found this record:\n");
            printf("%s \n",curr->name);
            printf("Do you really want to delete this (Y/N)? ");
            cin >> ch;
            if(ch == 'Y' || ch == 'y'){
                currNumb = curr->phoneNumb;
                while(currNumb->next != NULL){
                    tempNumb = currNumb;
                    currNumb = currNumb->next;
                    delete tempNumb;
                }

                delPtr = curr;
                curr = curr->next;
                temp->next = curr;
                delete delPtr;
				if (i == 1){
					head = curr;
				}

                return true;
            }else{
                return false;
            }
        }
        temp = curr;
        curr = curr->next;
		
    }
    return false;
}

bool List::deleteNumber(char input[]){
	curr = head;
	temp = head;
	nodePtr delPtr = NULL;
	char ch;
	int i = 0;
	string inn;
	while (curr != NULL){
		i++;
		if (strncmp(curr->name, input, strlen(input)) == 0){
			printf("We have found this record:\n");
			printf("%s \n", curr->name);
			currNumb = curr->phoneNumb;
			while (currNumb != NULL){
				printf("%s ", currNumb->num);
				currNumb = currNumb->next;
			}
			printf("\n");
			printf("Which number you want to delete?: ");
			cin >> inn;
			currNumb = curr->phoneNumb;
			// tempNumb = curr->phoneNumb;
			int j = 0;
			while (currNumb != NULL){
				j++;
				if (strncmp(currNumb->num, inn.c_str(), inn.length()) == 0){
					if (j == 1 && currNumb->next == NULL){
						printf("This record have only one number\n");
						deleteRecord(curr->name);
						return true;
					}
					else{
						delNumb = currNumb;
						currNumb = currNumb->next;
						if (j!=1)
							tempNumb->next = currNumb;
						delete delNumb;
						if (j == 1){
							curr->phoneNumb = currNumb;
						}
						return true;
					}
				}
				tempNumb = currNumb;
				currNumb = currNumb->next;
			}
		}
		temp = curr;
		curr = curr->next;

	}
	return false;
}

bool List::updateNumb(char input[]){
    curr = head;
    temp = head;

    nodePtr delPtr = NULL;
    char ch,name[30];
	string numb;
    while(curr != NULL){
        if(strncmp(curr->name,input,strlen(input)) == 0){
            printf("We have found this record:\n");
            printf("%s\n",curr->name);
            printf("Do you really want to update this record (Y/N)? ");
			currNumb = curr->phoneNumb;
			while (currNumb != NULL){
				printf("%s ", currNumb->num);
				currNumb = currNumb->next;
			}
            cin >> ch;
            if(ch == 'Y' || ch == 'y'){
				printf("Which number you want to update: ");
				cin >> numb;
				currNumb = curr->phoneNumb;
				int j = 0;
				while (currNumb != NULL){
					j++;
					if (strcmp(currNumb->num, numb.c_str()) == 0){
						printf("We have found this record\nEnter new number: ");
						char nn[100];
						cin >> nn;
						if (1){
							delNumb = currNumb;
							tempNumb->next = delNumb->next;
							addRecord(curr->name, nn, currNumb->type);
							return true;
						}
					}
					tempNumb = currNumb;
					currNumb = currNumb->next;
				}
                delPtr = curr;
                curr = curr->next;
                temp->next = curr;
                delete delPtr;
                return true;
            }else{
                return false;
            }
        }
        temp = curr;
        curr = curr->next;
    }
    return false;
}

bool List::updateName(char input[]){
	curr = head;
	temp = head;

	nodePtr delPtr = NULL;
	char ch, name[30];
	char numbers[100][50];
	char types[100][50];
	int i = 0;
	while (curr != NULL){
		i++;
		if (strncmp(curr->name, input, strlen(input)) == 0){
			printf("We have found this record:\n");
			printf("%s\n", curr->name);
			printf("Do you really want to update this record (Y/N)? ");
			cin >> ch;
			if (ch == 'Y' || ch == 'y'){
				printf("Enter the name of the record\n");
				cin >> name;

				currNumb = curr->phoneNumb;
				int j = 0;
				while (currNumb != NULL){
					strcpy(numbers[j], currNumb->num);
					strcpy(types[j], currNumb->type);
					currNumb = currNumb->next;
					j++;
				}
				delPtr = curr;
				curr = curr->next;
				temp->next = curr;
				if (i == 1) head = NULL;
				for (int k = 0; k < j; k++){
					addRecord(name, numbers[k], types[k]);
				}
				delete delPtr;
				return true;
			}
			else{
				return false;
			}
		}
		temp = curr;
		curr = curr->next;
	}
	return false;
}

void List::deleteAll() {
    curr = head;
    temp = head;
    while(curr != NULL){
        currNumb = curr->phoneNumb;
        curr = curr->next;
        while(currNumb->next != NULL){
            tempNumb = currNumb;
            currNumb = currNumb->next;
            delete tempNumb;
        }
        delete temp;
        temp = curr;
    }
}