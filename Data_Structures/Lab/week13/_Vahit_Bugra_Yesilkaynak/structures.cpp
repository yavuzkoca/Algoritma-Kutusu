#include <iostream>
#include <queue>
#include <stack>
#include <string>

#include "structures.h"

using namespace std;

listNode *savePhoneNode;

void MasterTree::create(){
	root = 0;
}

void MasterTree::add(string &name, string &phonenum, bool keeper){
	if( root == 0 ){

		root = new treeNode;
		root->left = NULL;
		root->right = NULL;
		root->name = name;
		if( !keeper ){
			root->phonenums = new listNode;
			root->phonenums->next = NULL;
			root->phonenums->phonenum = phonenum;
		}
		else{
			root->phonenums = savePhoneNode;
		}
	}

	else{

		treeNode *traverser = root;

		while( 1 ){

			bool flag = false;

			if( traverser->left != 0 && name.compare( traverser->name ) < 0 ) { traverser = traverser->left; flag = true; }
			if( traverser->right != 0 && name.compare( traverser->name ) > 0 && !flag) { traverser = traverser->right; }


			if( traverser->left == 0 && name.compare( traverser->name ) < 0 ){

				traverser->left = new treeNode;
				traverser = traverser->left;
				traverser->right = NULL;
				traverser->left = NULL;
				traverser->name = name;
				if(!keeper){
					traverser->phonenums = new listNode;
					traverser->phonenums->next = NULL;
					traverser->phonenums->phonenum = phonenum;
				}
				else{
					traverser->phonenums = savePhoneNode;
				}
				break;

			}
			if( traverser->right == 0 && name.compare( traverser->name ) > 0 ){

				traverser->right = new treeNode;
				traverser = traverser->right;
				traverser->right = NULL;
				traverser->left = NULL;
				traverser->name = name;
				if(!keeper){
					traverser->phonenums = new listNode;
					traverser->phonenums->next = NULL;
					traverser->phonenums->phonenum = phonenum;
				}
				else{
					traverser->phonenums = savePhoneNode;
				}
				break;
			}
			if( name.compare( traverser->name ) == 0 ){
				listNode *phoneTraverser = traverser->phonenums;
				while( phoneTraverser->next != NULL ) phoneTraverser = phoneTraverser->next;
				phoneTraverser->next = new listNode;
				phoneTraverser->next->phonenum = phonenum;
				phoneTraverser->next->next = NULL;
				break;
			}
		}
	}
}

void MasterTree::print(treeNode *node){

	if( node != NULL ){
		print(node->left);
		cout << "Name: " << node->name << endl;
		cout << "Phonenum(s): " << endl;
		listNode *traverser = node->phonenums;
		while(traverser != NULL){
			cout << "\t* " << traverser->phonenum << endl;
			traverser = traverser->next;
		}
		cout << endl;
		print(node->right);
	}

}

void MasterTree::search(string &name){

	queue<treeNode *> BFS;
	BFS.push(root);

	treeNode *curr;

	cout << endl;

	while( !BFS.empty() ){

		curr = BFS.front();
		BFS.pop();

		if( (curr->name).find( name ) == 0 ){
			cout << "Name: " << curr->name << endl;
			cout << "Phonenum(s): " << endl;
			listNode *traverser = curr->phonenums;
			while(traverser != NULL){
				cout << "\t* " << traverser->phonenum << endl;
				traverser = traverser->next;
			}
			cout << endl;
		}

		if( curr->left != NULL ) BFS.push(curr->left);
		if( curr->right != NULL ) BFS.push(curr->right);

	}

}

treeNode *leftMost( treeNode *root ){
	treeNode *curr = root;

	while(curr->left != NULL){
		curr = curr->left;
	}

	return curr;
}

void MasterTree::del(string &name, bool keeper){
	treeNode *traverse, *parent;
	traverse = root;
	bool found = false;
	char direction = 'k';
	while(traverse && !found){
		int comparison = name.compare( traverse -> name );
		if(comparison < 0){
			parent = traverse;
			direction = 'l';
			traverse = traverse->left;
		}
		else if(comparison > 0){
			parent = traverse;
			direction = 'r';
			traverse = traverse->right;
		}
		else{
			found = true;
		}
	}
	if(found){

		if(traverse->left == NULL && traverse->right == NULL){

			switch(direction){
				case 'l': parent->left = NULL; break;
				case 'r': parent->right = NULL; break;
				default: root = NULL; break;
			}
		}

		else if(traverse->right == NULL){

			switch(direction){
				case 'l': parent->left = traverse->left; break;
				case 'r': parent->right = traverse->left; break;
				default: root = traverse->left; break;
			}
		}

		else if(traverse->left == NULL){

			switch(direction){
				case 'l': parent->left = traverse->right; break;
				case 'r': parent->right = traverse->right; break;
				default: root = traverse->right; break;
			}
		}

		else{

			treeNode *q = traverse->right;
			while(q->left) q = q->left;
			q->left = traverse->left;
			switch(direction){
				case 'l': parent->left = traverse->right; break;
				case 'r': parent->right = traverse->right; break;
				default: root = traverse->right; break;
			}

		}

		if(!keeper){
			while(traverse->phonenums->next != NULL){
				listNode *temp = traverse->phonenums;
				traverse->phonenums = traverse->phonenums->next;
				delete temp;
			}
		}
		else{
			savePhoneNode = traverse->phonenums;
		}

		delete traverse; traverse = NULL;

	}
	else{
		cout << "Could not find the name to remove" << endl;
	}
}


void MasterTree::update(string &curr_name, string &new_name){
	del(curr_name, true);
	string dummy = "";
	add(new_name, dummy, true);
}

void MasterTree::close(treeNode *node){
	if(node){
		if(node->left != NULL){
			close(node->left);
			node->left = NULL;
		}
		if(node->right != NULL){
			close(node->right);
			node->right = NULL;
		}
		while(node->phonenums->next != 0){
			listNode *temp = node->phonenums;
			node->phonenums = node->phonenums->next;
			delete temp;
		}
		delete node->phonenums;
		node->phonenums = NULL;
		delete node;
	}
}