#include <iostream>
#include <cstring>
#include <cmath>
#include "Tree.h"

using namespace std;

Tree::Tree(){
    root = NULL;
}

void Tree::print_pre_order(node *nptr){
    if (nptr) {
        cout << nptr->number << " ";
        print_pre_order(nptr->left);
        print_pre_order(nptr->right);
    }
}

void Tree::print_post_order(node *nptr){
    if (nptr) {
        print_post_order(nptr->left);
        print_post_order(nptr->right);
        cout << nptr->number << " ";
    }
}

void Tree::print_in_order(node *nptr){
    if (nptr) {
        print_in_order(nptr->left);
        cout << nptr->number << " ";
        print_in_order(nptr->right);
    }
}

node* Tree::add_node(int arr[], node* root, int i, int n) {
    if (i < n) {
        node *newnode = new node;
        newnode->number = arr[i];
        newnode->left = newnode->right = NULL;
        root = newnode;
        root->left = add_node(arr, root->left, 2*i + 1, n);
        root->right = add_node(arr, root->right, 2*i + 2, n);
    }
    return root;
}

node* Tree::remove(node *nptr) {
    if(nptr){
        if(nptr->left){
            remove(nptr->left);
            nptr->left = NULL;
        }
        if(nptr->right){
            remove(nptr->right);
            nptr->right = NULL;
        }
        delete nptr;
    }
    return NULL;
}

int Tree::findMax(node *root) {
    if(root){
        int parent = root->number;
        int left_child = findMax(root->left);
        int right_child = findMax(root->right);
        if (left_child > parent)
            parent = left_child;
        if (right_child > parent)
            parent = right_child;
        return parent;
    }
    return -1;
}

int Tree::findMin(node *root) {
    if(root){
        int parent = root->number;
        int left_child = findMin(root->left);
        int right_child = findMin(root->right);
        if (left_child < parent)
            parent = left_child;
        if (right_child < parent)
            parent = right_child;
        return parent;
    }
    return 999999;
}

int Tree::findNumNode(node *nptr) {
    if(nptr)
        return 1 + findNumNode(nptr->left) + findNumNode(nptr->right);
    return 0;
}

int Tree::findNumLeaf(node *nptr) {
    if(nptr){
        if(nptr->left == NULL && nptr->right == NULL) return 1;
        return findNumLeaf(nptr->left) + findNumLeaf(nptr->right);
    }
}

int Tree::calculateDepth(node *nptr) {
    if(nptr)
        return 1 + max(calculateDepth(nptr->left), calculateDepth(nptr->right));
    return 0;
}

int Tree::calculateSum(node *nptr) {
    if(nptr)
        return nptr->number + calculateSum(nptr->left) + calculateSum(nptr->right);
    return 0;
}

int Tree::calculateAverage(node *nptr,int n) {
    return calculateSum(nptr) / n;
}