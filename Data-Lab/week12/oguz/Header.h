#ifndef header
#define header
struct node
{
	int data;
	struct node* left, *right;
};

node* gen(int index, int size, int* a);
node* create_Tree(int num);
int calculateDepth(struct node* node);
struct node* newNode(int data);
int findMax(node* root, int val);
int findMin(node* root, int val);
void printPostorder(struct node* node);
void printInorder(struct node* node);
void printPreorder(struct node* node);
int calculateSum(node* root, int val);
float calculateAverage(node *root, int val);
int findNumNode(node *root);
int findNumLeaf(node *root);
void removeTree(node *root);
#endif