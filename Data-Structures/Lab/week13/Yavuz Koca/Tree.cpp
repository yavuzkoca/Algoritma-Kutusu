#include <iostream>
#include <cstring>
#include <cmath>
#include "Tree.h"

using namespace std;

Tree::Tree(){
    root = NULL;
}

void Tree::print_in_order(node *nptr){
    if (nptr) {
        print_in_order(nptr->left);
        cout << nptr->name << " ";
        phoneNode *current = nptr->head;
        while(current){
            cout << current->phoneNum << " ";
            current = current->next;
        }
        cout << endl;
        print_in_order(nptr->right);
    }
}

void Tree::add_node(node* nptr, char *name, char *numb) {
    if(root == NULL){
        root = new node;
        root->left = root->right = NULL;
        root->name = new char[strlen(name)+1];
        strcpy(root->name, name);
        root->name[strlen(name)] = '\0';

        root->head = new phoneNode;
        root->head->phoneNum = new char[strlen(numb)+1];
        strcpy(root->head->phoneNum, numb);
        root->head->phoneNum[strlen(numb)] = '\0';
        root->head->next = NULL;
        return;
    }

    node *traverse = root;
    bool added = false;
    while ((traverse != NULL) && (!added)){
        if(strcmp(name, traverse->name) < 0){
            if (traverse->left != NULL)
                traverse = traverse->left;
            else {
                traverse->left = new node;
                traverse->left->left = traverse->left->left = NULL;
                traverse->left->name = new char[strlen(name)+1];
                strcpy(traverse->left->name, name);
                traverse->left->name[strlen(name)] = '\0';

                traverse->left->head = new phoneNode;
                traverse->left->head->phoneNum = new char[strlen(numb)+1];
                strcpy(traverse->left->head->phoneNum, numb);
                traverse->left->head->phoneNum[strlen(numb)] = '\0';
                traverse->left->head->next = NULL;
                added = true;
            }
        } else if (strcmp(name, traverse->name) > 0){
            if (traverse->right != NULL)
                traverse = traverse->right;
            else {
                traverse->right = new node;
                traverse->right->left = traverse->right->left = NULL;
                traverse->right->name = new char[strlen(name)+1];
                strcpy(traverse->right->name, name);
                traverse->right->name[strlen(name)] = '\0';

                traverse->right->head = new phoneNode;
                traverse->right->head->phoneNum = new char[strlen(numb)+1];
                strcpy(traverse->right->head->phoneNum, numb);
                traverse->right->head->phoneNum[strlen(numb)] = '\0';
                traverse->right->head->next = NULL;

                added = true;
            }
        }else{
            phoneNode *current = traverse->head;
            while(current->next != NULL)
                current = current->next;
            current->next = new phoneNode;
            current->next->phoneNum = new char[strlen(numb)+1];
            strcpy(current->next->phoneNum, numb);
            current->next->phoneNum[strlen(numb)] = '\0';
            current->next->next = NULL;
            return;
        }
    }
}

void Tree::remove(char *name) {
    node *current, *parent;
    current = root;
    bool found = false;
    char direction = 'k';
    while(current && !found){
        int comparison = strcmp(name, current->name);
        if (comparison < 0) {
            parent = current;
            direction = 'l';
            current = current->left;
        }
        else if (comparison > 0) {
            parent = current;
            direction = 'r';
            current = current->right;
        }
        else // found record to remove
            found = true;
    }
    if(found){
        if (current->left == NULL && current->right == NULL) {
            switch (direction) {
                case 'l':
                    parent->left = NULL;
                    break;
                case 'r':
                    parent->right = NULL;
                    break;
                default:
                    root = NULL;
                    break;
            }
        }else if (current->right == NULL) {
            switch (direction) {
                case 'l':
                    parent->left = current->left;
                    break;
                case 'r':
                    parent->right = current->left;
                    break;
                default:
                    root = current->left;
                    break;
            }
        } else if (current->left == NULL) {
            switch (direction) {
                case 'l':
                    parent->left = current->right;
                    break;
                case 'r':
                    parent->right = current->right;
                    break;
                default:
                    root = current->right;
                    break;
            }
        }else {
            node *q = current->right;
            while ( q->left )
                q = q->left;
            q->left = current->left;
            switch (direction) {
                case 'l':
                    parent->left = current->right;
                    break;
                case 'r':
                    parent->right = current->right;
                    break;
                default:
                    root = current->right;
                    break;
            }
        }
        phoneNode *cur = current->head;
        while(cur){
            phoneNode *temp = cur;
            cur = cur->next;
            delete temp;
        }
        delete current;
    }else{
        cout << "Could not find the record" << endl;
    }
}

bool Tree::search(node *nptr, char *name) {
    if (nptr && strcmp(nptr->name, name) == 0) {
        return 1;
    }
    else if(nptr){
        search(nptr->left, name);
        search(nptr->right, name);
    }else
        return 0;
}

node* Tree::deleteAll(node *nptr) {
    if(nptr){
        if(nptr->left){
            deleteAll(nptr->left);
            nptr->left = NULL;
        }
        if(nptr->right){
            deleteAll(nptr->right);
            nptr->left = NULL;
        }
        phoneNode *current = nptr->head;
        while(current){
            phoneNode *temp = current;
            current = current->next;
            delete temp;
        }
        delete nptr;
    }
    return NULL;
}

void Tree::update(char *name, char *tar) {
    node *traverse = root;
    while ((traverse != NULL)){
        if(strcmp(name, traverse->name) < 0){
            traverse = traverse->left;
        } else if (strcmp(name, traverse->name) > 0){
            traverse = traverse->right;
        }else{
            phoneNode *current = traverse->head;
            // cout << traverse->name << endl;
            while(current != NULL){
                // cout << tar << endl;
                add_node(root, tar, current->phoneNum);
                current = current->next;
            }
            remove(name);
            return;
        }
    }
}