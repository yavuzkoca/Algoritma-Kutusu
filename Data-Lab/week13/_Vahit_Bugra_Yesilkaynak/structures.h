#include <string>

struct listNode{
	std::string phonenum;
	listNode *next;
};

struct treeNode{
	std::string name;
	listNode *phonenums;
	treeNode *left;
	treeNode *right;
};

struct MasterTree{
	treeNode *root;
	void create();
	void add(std::string &, std::string &, bool keeper=false);
	void print(treeNode *);
	void search(std::string &);
	void update(std::string &, std::string &);
	void del(std::string &, bool keeper=false);
	void close(treeNode *);
};