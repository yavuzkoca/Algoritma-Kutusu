#ifndef phonetree
#define phonetree
#endif

#define NAME_LENGTH 30
#define PHONENUM_LENGTH 15

struct Temp_node{
	char name[NAME_LENGTH];
	char phonenum[PHONENUM_LENGTH];
};

struct num_node{
	char phonenum[PHONENUM_LENGTH];
	num_node *next;
};

struct num_list{
	num_node *head;
	void add_num(char toadd[PHONENUM_LENGTH]);
	void create();
	bool isempty();
	void close();
	void list();
};

struct Phone_node{
	char name[NAME_LENGTH];
	num_list numz;
	Phone_node *left;
	Phone_node *right;
};

struct Tree {
	Phone_node *root;
	int nodecount;
	char *filename;
	FILE *phonebook;
	void create();
	Phone_node* remove(Phone_node **p);
	void Tree::update(char old[NAME_LENGTH], char neu[NAME_LENGTH]);
	void close();
	void emptytree(Phone_node *);
	void add(Temp_node *);
	void traverse_inorder(Phone_node *);
	int search(char *);
	//void update(int recordnum);
	void read_fromfile();
	void write_preorder(Phone_node *);
	void write_tofile();
	Phone_node* Tree::rem(char *remove_name);
	void Tree::del(char *remove_name);
};