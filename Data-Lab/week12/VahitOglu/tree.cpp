#include "tree.h"

#include <iostream>
#include <random>
#include <cmath>

using namespace std;

template <typename T>
struct QueueNode{
	T data;
	QueueNode<T> *next;
};

template <typename T>
struct Queue{
	QueueNode<T> *front;
	QueueNode<T> *back;
	bool enqueue(T &);
	T dequeue();
	bool isEmpty();
	void create();
	void close();	
};

template <typename T>
bool Queue<T>::enqueue(T &data){
	QueueNode<T> *new_node = new QueueNode<T>;
	new_node->next = 0;
	new_node->data = data;
	if(!isEmpty()) { back->next = new_node; back = new_node; }
	else{ back = new_node; front = new_node; }
	return true;
}

template <typename T>
T Queue<T>::dequeue(){
	T temp;
	temp = front->data;
	QueueNode<T> *temp_node = front;
	front = front->next;
	delete temp_node;
	return temp;
}

template <typename T> bool Queue<T>::isEmpty(){ return front == 0 ? true : false; }
template <typename T> void Queue<T>::create(){ front = 0; back = 0; }
template <typename T> void Queue<T>::close(){ while(!isEmpty()) dequeue(); }

void swap(int &x, int &y){
	int temp;
	temp = x;
	x = y;
	y = temp;
}

int *random_array_generator(int N){

	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(0, N-1);

	int *arr = new int[N];
	for(int i = 1; i <= N; ++i) arr[i-1] = i;

	for(int i = 0; i < N; ++i){
		int loc1 = dist(gen);
		int loc2 = dist(gen);
		swap(arr[loc1], arr[loc2]);
	}

	return arr;
}

void delete_empty(TreeNode **node){
	if((*node)->data == -1){
		delete *node;
		*node = 0;
	}
	else{
		delete_empty(&((*node)->left));
		delete_empty(&((*node)->right));
	}
}

void Tree::createTree(int N){

	root = new TreeNode;

	int *arr = random_array_generator(N);

	for(int i = 0; i < N; ++i) cout << arr[i] << " ";
	cout << endl;

	Queue<TreeNode *> bfs;

	bfs.create();
	bfs.enqueue(root);

	TreeNode *traverser;

	for(int i = 0; i < N; ++i){
		traverser = bfs.dequeue();
		traverser->left = new TreeNode;
		traverser->right = new TreeNode;
		traverser->data = arr[i];
		traverser->left->data = -1;
		traverser->right->data = -1;
		bfs.enqueue(traverser->left);
		bfs.enqueue(traverser->right);
	}

	delete_empty(&root);
	bfs.close();
	delete arr;

}

void removeTree(TreeNode * &node){
	if( node != 0 ){
		removeTree(node->left);
		removeTree(node->right);
		delete node;
		node = 0;
	}
}

void printPreorder(TreeNode *node){

	if( node != 0 ){
		cout << node->data << endl;
		printPreorder(node->left);
		printPreorder(node->right);
	}

}

void printInorder(TreeNode *node){

	if( node != 0 ){
		printPreorder(node->left);
		cout << node->data << endl;
		printPreorder(node->right);
	}

}

void printPostorder(TreeNode *node){

	if( node != 0 ){
		printPreorder(node->left);
		printPreorder(node->right);
		cout << node->data << endl;
	}

}

int Tree::findMax(){
	Queue<TreeNode *> bfs;
	bfs.create();
	TreeNode *traverser;
	bfs.enqueue(root);
	int max = -1;
	while(!bfs.isEmpty()){
		traverser = bfs.dequeue();
		if(traverser->data > max) max = traverser->data;
		if(traverser->left) bfs.enqueue(traverser->left);
		if(traverser->right) bfs.enqueue(traverser->right);
	}
	bfs.close();
	return max;
}

int Tree::findMin(){
	Queue<TreeNode *> bfs;
	bfs.create();
	TreeNode *traverser;
	bfs.enqueue(root);
	int min = 999999;
	while(!bfs.isEmpty()){
		traverser = bfs.dequeue();
		if(traverser->data < min) min = traverser->data;
		if(traverser->left) bfs.enqueue(traverser->left);
		if(traverser->right) bfs.enqueue(traverser->right);
	}
	bfs.close();
	return min;
}

int Tree::findNumNode(){
	Queue<TreeNode *> bfs;
	bfs.create();
	TreeNode *traverser;
	int number_of_nodes = 1;
	bfs.enqueue(root);
	while(!bfs.isEmpty()){
		traverser = bfs.dequeue();
		if(traverser->left) { bfs.enqueue(traverser->left); number_of_nodes++; }
		if(traverser->right) { bfs.enqueue(traverser->right); number_of_nodes++; }
	}
	bfs.close();
	return number_of_nodes;
}

int Tree::findNumLeaf(){
	Queue<TreeNode *> bfs;
	bfs.create();
	TreeNode *traverser;
	int number_of_leaves = 0;
	bfs.enqueue(root);
	while(!bfs.isEmpty()){
		traverser = bfs.dequeue();
		if(traverser->left) bfs.enqueue(traverser->left);
		if(traverser->right) bfs.enqueue(traverser->right);
		if(!(traverser->right || traverser->left)) number_of_leaves++;
	}
	bfs.close();
	return number_of_leaves;
}

int Tree::calculateDepth(){
	return ceil(log2(findNumNode()) + 1e-3);
}

int Tree::calculateSum(){
	Queue<TreeNode *> bfs;
	bfs.create();
	TreeNode *traverser;
	int sum = 0;
	bfs.enqueue(root);
	while(!bfs.isEmpty()){
		traverser = bfs.dequeue();
		sum += traverser->data;
		if(traverser->left) bfs.enqueue(traverser->left);
		if(traverser->right) bfs.enqueue(traverser->right);
	}
	bfs.close();
	return sum;
}

int Tree::calculateAverage(){
	Queue<TreeNode *> bfs;
	bfs.create();
	TreeNode *traverser;
	int sum = 0;
	int number_of_nodes = 1;
	bfs.enqueue(root);
	while(!bfs.isEmpty()){
		traverser = bfs.dequeue();
		sum += traverser->data;
		if(traverser->left) {bfs.enqueue(traverser->left); number_of_nodes++; }
		if(traverser->right) {bfs.enqueue(traverser->right); number_of_nodes++; }
	}
	bfs.close();
	return sum / number_of_nodes;
}
