#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nameHolder{
	char **names;
	int *sizes;
	int size;
	int total_name_size;
	void create(const char *, int);
	void print();
	void empty();
	int getSize(){ return size; }
	char *getConcatenatedName();
	char *getName(int index){ return *(names + index); }
}; // This struct and its functions are currently useless, I will use it if I implement multiple name input before the deadline

struct studentInfo{ // The node holding the student information
	studentInfo *next;
	studentInfo *previous;
	char *name;
	int name_size;
	int number; // This is the number where if there are a lot of same name
				// we put some number at the and of the email
	char *email; // The email adress without the domain part
	int email_size;
};

struct surnameNode{ // The node which holds the surnames and the studentInfo doubly linked lists
	surnameNode *next;
	studentInfo *infoHead;
	studentInfo *infoTail;
	int size;
	char *surname;
	int surname_size;
	void decideEmail(studentInfo *); // This function assigns the emails
};

struct surnameMap{
	int size; 
	surnameNode *head;
	void create(); // Initializes the circuler linked list
	surnameNode * ifSurnameExists(const char *); // Checks if some surname exists
	surnameNode * addSurname(const char *, int); // Adds a surname to the surnameMap alphabetically
	void insertNewRecord(const char *, const char *, int, int); // Inserts a new student, creates new surnameNode if does not exist
	void printSurnames(); // Prints the surnames in the surname map
	void printEmails(); // Prints the surnames and the students and their emails
	void createList(const char *); // Creates the surnameMap with only the surnames from a file
	void insertAll(const char *); // Inserts all the student information from a file
	int deleteStudent(const char *, const char *); // Deletes a student whom his/her name and surname is given
	void deleteSurnameNode(const char *); // Deletes a surnameNode for the given surname
	void updateList(const char *, const char *, const char *, const char *); // Takes student name and surname also news then updates
	void writeToFile(const char *); // Writes the name, surname and emails to a txt file
	void clearAll();
	bool isEmpty(){ return (size == 0) ? true : false; }
};

int strToInt(const char *); // Converts char * to int

char *intToStr(int); // converts int to char *

char * addExtension(studentInfo *); // Add @itu.edu.tr also lowers the cases


