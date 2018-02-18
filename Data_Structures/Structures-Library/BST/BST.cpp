#include <iostream>
#include "BST.h"

using namespace std;

BST::BST(){
    _root = nullptr;
}

BST::node* BST::_createLeaf(int num) {
    auto n = new node;
    n->right = n->left = nullptr;
    n->num = num;
    return n;
}

void BST::addLeaf(int num) {
    _addLeaf(num, _root);
}

void BST::_addLeaf(int num, node *ptr) {
    if(_root == nullptr){
        _root = _createLeaf(num);
    }
    else if(num < ptr->num){
        if(ptr->left != nullptr){
            _addLeaf(num, ptr->left);
        }else{
            ptr->left = _createLeaf(num);
        }
    }else if(num > ptr->num){
        if(ptr->right != nullptr){
            _addLeaf(num, ptr->right);
        }else{
            ptr->right = _createLeaf(num);
        }
    }else{
        cout << "\nThis number has already added!\n";
    }

}

void BST::printInOrder(){
    _printInOrder(_root);
}

void BST::_printInOrder(node *ptr) {
    if(_root != nullptr){
        if(ptr->left != nullptr){
            _printInOrder(ptr->left);
        }
        cout << ptr->num << " " ;
        if(ptr->right != nullptr){
            _printInOrder(ptr->right);
        }
    }else{
        cout << "\nThe tree is empty\n";
    }
}

void BST::removeNode(int num){
    _removeNode(num, _root);
}

void BST::_removeNode(int num, node* parent){
    if(_root != nullptr){
        if(_root->num == num){
            _removeRootMatch();
        }else{
            if(num < parent->num && parent->left != nullptr){
                parent->left->num == num ?
                _removeMatch(parent, parent->left, true) :
                _removeNode(num, parent->left);
            }else if(num > parent->num && parent->right != nullptr){
                parent->right->num == num ?
                _removeMatch(parent, parent->right, false) :
                _removeNode(num, parent->right);
            }else{
                cout << "\nThis number does not exist\n";
            }
        }
    }else{
        cout << "\nTree is empty!\n";
    }
}

void BST::_removeRootMatch(){
    if(_root != nullptr){
        auto delPtr = _root;
        int smallestInRightSubTree;

        if(_root->left == nullptr && _root->right == nullptr){
            _root = nullptr;
            delete delPtr;
        }else if(_root->left == nullptr && _root->right != nullptr){
            _root = _root->right;
            delPtr->right = nullptr;
            delete delPtr;
        }else if(_root->right == nullptr && _root->left != nullptr){
            _root = _root->left;
            delPtr->left = nullptr;
            delete delPtr;
        }else{
            smallestInRightSubTree = _findSmallest(_root->right);
            _removeNode(smallestInRightSubTree, _root);
            _root->num = smallestInRightSubTree;
        }

    }else{
        cout << "\nTree is already empty\n";
    }
}

int BST::_findSmallest(node* ptr){
    if(ptr->left != nullptr){
        _findSmallest(ptr->left);
    }else{
        return ptr->num;
    }
}

void BST::_removeMatch(node* parent, node* match, bool left){
    if(_root != nullptr){
        node* delPtr;
        int matchKey = match->num;
        int smallestInRightSubTree;

        if(match->left == nullptr && match->right == nullptr){
            delPtr = match;
            left ? parent->left = nullptr : parent->right = nullptr;
            delete delPtr;
        }else if(match->left == nullptr && match->right != nullptr){
            left ? parent->left = match->right : parent->right = match->right ;
            match->right = nullptr;
            delPtr = match;
            delete delPtr;
        }else if(match->right == nullptr && match->left != nullptr){
            left ? parent->left = match->left : parent->right = match->left ;
            match->left = nullptr;
            delPtr = match;
            delete delPtr;
        }else{
            smallestInRightSubTree = _findSmallest(match->right);
            _removeNode(smallestInRightSubTree, match);
            match->num = smallestInRightSubTree;
        }

    }else{
        cout << "\nCan not remove match. The tree is empty\n";
    }
}