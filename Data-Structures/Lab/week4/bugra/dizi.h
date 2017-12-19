#ifndef DIZI_H
#define DIZI_H
#import "kayit.h"

struct List
{
	Record *records;
	int current_size;
	int max_size;
	void Create();
	void add(Record *);
	void remove(int);
	void list();
	void search(char *);
	void update(int, char *, char *);
};

#endif