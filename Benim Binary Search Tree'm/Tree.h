#ifndef TREE_H
#define TREE_H

#include <queue>

struct node
{
	int data;
	node *left;
	node *right;
};

struct Tree
{
	void remove(int value);
	node* add(node *root, int value);
	void print(node *root);
	bool LevelFirstSearch(int value);
	bool PreorderSearch(int value);
	bool InorderSearch(int value);
	bool PostorderSearch(int value);
};

#endif // !TREE_H


#pragma once
