typedef struct coordinate{int i, j;} StackDataType;

struct StackNode{
	StackDataType data;
	StackNode *next;
};

struct Stack{
	StackNode *top;
	void push(StackDataType);
	StackDataType pop();
	void print();
	bool isEmpty();
	void create();
	void close();
};