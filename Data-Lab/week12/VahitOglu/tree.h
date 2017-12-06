struct TreeNode{
	TreeNode *left;
	TreeNode *right;
	int data;
};

struct Tree{
	TreeNode *root;

	void createTree(int);
	int findMax();
	int findMin();
	int findNumNode();
	int findNumLeaf();
	int calculateDepth();
	int calculateSum();
	int calculateAverage();
};

void treeCreator(TreeNode * &, int *, int &, const int &);
void removeTree(TreeNode * &);
void printPreorder(TreeNode *);
void printInorder(TreeNode *);
void printPostorder(TreeNode *);