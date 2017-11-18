#include "Tree.h"
#include <iostream>
#include <queue>

using namespace std;

node* Tree::add(node *root, int value)
{
	if (root == NULL)
	{
		root = new node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	if (value <= root->data)
	{
		root->left = add(root->left, value);
		return root;
	}
	else
	{
		root->right = add(root->right, value);
		return root;
	}
}

void Tree::print(node *root)
{
	if (root == NULL) return;
	queue<node*> q;
	q.push(root);
	cout << "Node    L   R  \n";
	while (!q.empty())
	{
		node *current = q.front();
		cout << current->data << "       " << (current->left ? current->left->data : 32 ) << "     " << (current->right ? current->right->data : 99);
		if (current->left != NULL) q.push(current->left);
		if (current->right != NULL) q.push(current->right);
		q.pop();
		cout << endl;
	}
}
