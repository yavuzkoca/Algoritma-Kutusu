#include <iostream>
#include <time.h>
#include "Header.h"

using namespace std;

node* newNode(int data)
{
	node* new_node = new node;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	return(new_node);
}
node* gen(int index, int size, int* a){
	node *tmp = NULL;
	if (index < size){
		tmp = new node();
		tmp->data = a[index];
		tmp->left = gen(2 * index + 1, size, a);
		tmp->right = gen(2 * index + 2, size, a);
	}
	if (index == 0)
		delete[] a;
	return tmp;
}
node* create_Tree(int num){
	srand(time(NULL));

	int *arr = new int[num];
	for (int i = 0; i < num; i++)
		arr[i] = rand() % num + 1;
	return gen(0, num, arr);
}

void printPostorder(node* node)
{
	if (node == NULL)
		return;

	printPostorder(node->left);
	printPostorder(node->right);

	printf("%d ", node->data);
}

void printInorder(node* node)
{
	if (node == NULL)
		return;

	printInorder(node->left);

	printf("%d ", node->data);

	printInorder(node->right);
}

void printPreorder(node* node)
{
	if (node == NULL)
		return;

	printf("%d ", node->data);

	printPreorder(node->left);
	printPreorder(node->right);
}

int calculateDepth(node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		int lheight = calculateDepth(node->left);
		int rheight = calculateDepth(node->right);
		
		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}

int findMax(node* root, int val){
	
	if (root == NULL)
		return val;

	val = findMax(root->left, val);
	val = findMax(root->right, val);
	
	if (root->data > val)
		return root->data;
	else
		return val;
}

int findMin(node* root, int val){

	if (root == NULL)
		return val;

	val = findMin(root->left, val);
	val = findMin(root->right, val);

	if (root->data < val)
		return root->data;
	else
		return val;
}

int calculateSum(node* root, int val){
	
	return val + (root->left ? calculateSum(root->left, root->left->data) : 0) + 
		(root->right ? calculateSum(root->right, root->right->data) : 0);

}

float calculateAverage(node *root, int val){
	
	return (float)(calculateSum(root, val)) / (float)(findNumNode(root));

}

int findNumNode(node *root){

	return (root ? findNumNode(root->left) + findNumNode(root->right) + 1 : 0);

}

int findNumLeaf(node *root){
	
	return (root->left ? findNumLeaf(root->left) : 0) + (root->right ? findNumLeaf(root->right) : 0) + (!root->left && !root->right);

}

void removeTree(node *root){
	if (root->left)
		removeTree(root->left);
	if (root->right)
		removeTree(root->right);
	delete root;
}