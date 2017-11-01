#ifndef LIST_H
#define LIST_H

/* id'ler ayni isimdeki kisileri mail adresleri disinda baska
 * bir yöntem ile ayirmak icin olusturulmustur. 
 */


struct insertList
{
	char *name;
	char *surname;
	int id;
	insertList *next;
};

struct studentInfo
{
	char *name;
	char *surname;
	char *mail;
	int id;
	studentInfo *next;
	studentInfo *prev;
};

struct surnameMap
{
	char *surname;
	studentInfo *mailHead;
	surnameMap *next;
};

#endif