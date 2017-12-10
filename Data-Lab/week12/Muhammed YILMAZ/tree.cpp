//cout << "line: " << __LINE__ << endl;	

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "queue.h"
using namespace std;

struct node
{
	int deger;
	node *sag;
	node *sol;
	int depth;
};

queue anaDizi;
queue yaprakDizi;
node *root = NULL;

void createTree();
node *addNode(node *agac, int deger);
void removeTree(node *agac);
void printPreorder(node *agac);
void printInorder(node *agac);
void printPostorder(node *agac);
int findMax(node *agac);
int findMin(node *agac);
int findNumNode(node *agac);
int findNumLeaf(node *agac);
int calculateDepth(node *agac);
int calculateSum(node *agac);
float calculateAverage(node *agac);

void createAnaDizi(int num);
bool yaprakYerlestir(node *agac);
void printTree(node *agac);

int main(int argc, char *argv[])
{
	anaDizi.create();
	yaprakDizi.create();
	srand(time(NULL));
	int maxNumberNode;

	cout << "The maximum number of nodes will be: ";
	cin >> maxNumberNode;
	getchar();
	createAnaDizi(maxNumberNode);
	anaDizi.show();
	createTree();

	return EXIT_SUCCESS;
}
void createAnaDizi(int num){
	for (int i = 0; i < num; ++i)
	{
		anaDizi.push(rand()%num);
	}
}

void createTree(){

	cout << endl;
																						cout << "anaDizi:\t";	anaDizi.show();
	root = addNode(root, anaDizi.top().deger);
																						cout << "printInorder:\t";	printInorder(root);	cout << endl;
	anaDizi.pull();
																						cout << endl;
	for (int tempDerinlik = 0; anaDizi.tepeEleman != NULL; ++tempDerinlik)
	{
																						cout << "anaDizi:\t";	anaDizi.show();
		for (int tempYaprak = 0; anaDizi.tepeEleman != NULL && tempYaprak < pow(2,tempDerinlik+1); ++tempYaprak)
		{
			yaprakDizi.push(anaDizi.top().deger);
			anaDizi.pull();
		}
																						cout << "yaprakDizi:\t";	yaprakDizi.show();
		yaprakYerlestir(root);
																						cout << "printInorder:\t";	printInorder(root);	cout << endl << endl;	
	}
}

bool yaprakYerlestir(node *agac){

	if(agac == NULL || yaprakDizi.tepeEleman == NULL)	
		return false;
	if(agac->sol == NULL)
	{
		agac->sol = addNode(agac->sol, yaprakDizi.top().deger);
		yaprakDizi.pull();
	}
	else
	{	
		yaprakYerlestir(agac->sol);
	}
	if(yaprakDizi.tepeEleman == NULL)
		return false;
	if(agac->sag == NULL)
	{
		agac->sag = addNode(agac->sag, yaprakDizi.top().deger);
		
		yaprakDizi.pull();
		
	}
	else
	{
		yaprakYerlestir(agac->sag);
	}
}

node *addNode(node *agac, int deger){

	if(agac == NULL)
	{
		node *yeni = new node;
		yeni->deger = deger;
		yeni->sol = NULL;
		yeni->sag = NULL;
		return yeni;
	}
	
	return agac;
}

void removeTree(node *agac){

	if(agac == NULL)
	{
		return;
	}
	else if(agac->sol != NULL)
	{
		removeTree(agac->sol);
		delete agac->sol;
	}
	else if(agac->sag != NULL)
	{
		removeTree(agac->sag);
		delete agac->sag;
	}
	delete agac;
	
}


void printPreorder(node *agac){

	if(agac == NULL)	return;
	cout << agac->deger << " - ";
	printPreorder(agac->sol);
	printPreorder(agac->sag);
}

void printInorder(node *agac){

	if(agac == NULL)	return;
	printInorder(agac->sol);
	cout << agac->deger << " - ";
	printInorder(agac->sag);
}

void printPostorder(node *agac){

	if(agac == NULL)	return;
	printInorder(agac->sol);
	printInorder(agac->sag);
	cout << agac->deger << " - ";
}

int findMax(node *agac){
	
	if(agac == NULL)
		return 0;
	int max = agac->deger;
	if(agac->sol != NULL && max < findMin(agac->sol))	max = findMin(agac->sol);
	if(agac->sag != NULL && max < findMin(agac->sag))	max = findMin(agac->sag);
	return max;
}
int findMin(node *agac){

	if(agac == NULL)
		return 0;
	int min = agac->deger;
	if(agac->sol != NULL && min > findMin(agac->sol))	min = findMin(agac->sol);
	if(agac->sag != NULL && min > findMin(agac->sag))	min = findMin(agac->sag);
	return min;
}
int findNumNode(node *agac){
	if(agac == NULL)
		return 0;

	int say = 0;
	say += findNumNode(agac->sol);
	say += 1;
	say += findNumNode(agac->sag);

	return say;
}

int findNumLeaf(node *agac){

	if(agac == NULL)
		return 0;

	int say = 0;
	say += findNumLeaf(agac->sol);
	if(agac->sol == NULL && agac->sag == NULL)	say += 1;
	say += findNumLeaf(agac->sag);

	return say;
}

int calculateDepth(node *agac){

	if(agac==NULL)	return -1;
	node *iter = agac;
	while(iter->sol != NULL)
	{
		iter = iter->sol;
	}
	cout << "depth sol: " << iter->depth << endl;
	return iter->depth;
}

int calculateSum(node *agac){

	if(agac == NULL)
		return 0;

	int sum = 0;
	sum += calculateSum(agac->sol);
	sum += agac->deger;
	sum += calculateSum(agac->sag);

	return sum;
}

float calculateAverage(node *agac){

	return (float)calculateSum(agac) / (float)findNumNode(agac);
}
