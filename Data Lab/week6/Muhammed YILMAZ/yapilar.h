#ifndef YAPILAR_H
#define YAPILAR_H

struct tagPhone
{
	char type[10];
	char phone[12];
	tagPhone *next;	
};

struct tagPerson
{
	char name[25];
	tagPhone *phones;
	tagPerson *next;
	tagPerson *prev;
};


#endif