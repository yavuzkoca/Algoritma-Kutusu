/* @Author
* Student Name: <Ahmed Yasin KUL>
* Student ID : <070150136>
* Date: <01.11.2017>
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <string.h>
#include <locale.h>

#define NAME_LENGTH 20
#define SURNAME_LENGTH 15
#define EMAIL_LENGTH 40

using namespace std;

struct studentInfo{
	char* name;
	char* surname;
	char* email;
	studentInfo *next, *previous;
};

struct surnameMap{
	char* surname;
	surnameMap* next;
	studentInfo* headStudent;
};

surnameMap* headSurnameMap = NULL, *tail = NULL;
int surnameCount = 0, lineNumber = 0;
bool create = false, insert = false;
char* itu = new char[12];
FILE* inputFile = fopen("newStudentsList.txt", "r");

bool print_menu();
bool select_option();
void createList();
void insertAll();
void listAll();
void listSurnames();
char* stringMerge(char* first, char* second);
void createNewSurnameNode(char* surname);
void sortMail(studentInfo* newTemp);
char* compareMails(char* name, char* surname);
bool mailCheckTrue(char* surname, char* mail);
surnameMap* checkSurnameNodes(char* isExist);
surnameMap* newSurnameNode(char* newSurname);
void tailAssigner();
studentInfo* newStudent(char* newName, char* newSurname);
void deleteStudentNode(studentInfo* ptr);
void insertNewRecord(bool mode);
void writeToFile();
bool deleteStudent(char* mail);
void deleteStudentMenu();
void updateList();
bool deleteSurnameNode(char* surname);
void deleteSurnameNodeMenu();
void wrong();
inline char* ituMail(char* mail);

void wordNumb();
bool isSecondLonger(char* first, char* second);
char* toLowerWord(char* word);
char* convertToTurkish(char* word);


int main(){

	setlocale(LC_ALL, "tr_TR.UTF-8");
	cout << "Locale is: " << setlocale(LC_ALL, NULL) << endl;
	wordNumb();
	strcpy(itu, "@itu.edu.tr");

	while(!print_menu());
	cout << "\nName:\tAhmed Yasin KUL\nID:\t070150136\n";

	for(; tail != NULL; deleteSurnameNode(tail->surname));
	deleteSurnameNode(headSurnameMap->surname);
	delete[] itu;
	return EXIT_SUCCESS;
}

void createList(){

	if(headSurnameMap == NULL){

		char* surname;
		cout << lineNumber << endl;

		for (int i = 0; i < lineNumber; i++){
			surname = new char[SURNAME_LENGTH];
			fscanf(inputFile, "%*[^\t]\t%[^\r\n]\r\n", surname);
			createNewSurnameNode(surname);
			delete[] surname;
		}
		cout << surnameCount << " surname has been read from the file..." << endl;

		fseek(inputFile, 0, SEEK_SET);
	}
	else cout << "You have already read the surnames from the file before..." << endl;
	return;
}

void insertAll(){

	char* name, *surname;
	fseek(inputFile, 0, SEEK_SET);
	
	for(int i = 0; i < lineNumber; i++){
		name = new char[NAME_LENGTH];
		surname = new char[SURNAME_LENGTH];
		fscanf(inputFile, "%[^\t]\t%[^\r\n]\r\n", name, surname);
		newStudent(name, surname);
		delete[] name;
		delete[] surname;
	}
	fclose(inputFile);
}

studentInfo* newStudent(char* newName, char* newSurname){

	studentInfo* tmp = new studentInfo;

	tmp->surname = new char[strlen(newSurname)+1];
	tmp->name = new char[strlen(newName)+1];

	strcpy(tmp->name, newName);
	strcpy(tmp->surname, newSurname);

	tmp->previous = NULL;
	tmp->next = NULL;

	char* mail = ((checkSurnameNodes(tmp->surname))->headStudent == NULL) ? convertToTurkish(tmp->surname) : compareMails(tmp->name, tmp->surname);
	tmp->email = ituMail(mail);
	delete[] mail;
	sortMail(tmp);
	return tmp;
}

//--------------------------------***MAIL FUNCTIONS***----------------------------------------

char* compareMails(char* name, char* surname){

	char* c, *tmp, *tmpName = convertToTurkish(name), *resultMail = convertToTurkish(surname);
	int cnt = 0, number = 2;

	while(1){
		if(mailCheckTrue(surname, resultMail)){
			delete[] tmpName;
			return resultMail;
		}
		else{
			c = new char[2];
            *(c+0) = *(tmpName+cnt);
			*(c+1) = '\0';
			cnt++;
			strcat(resultMail, c);
			delete[] c;
			if(*(tmpName+cnt) == '\0')		break;
		}
	}

	delete[] tmpName;	
	char* tmpMail = new char[strlen(resultMail)+1];
	strcpy(tmpMail, resultMail);

	while(!mailCheckTrue(surname, resultMail)){
		tmp = new char[3];
		sprintf(tmp, "%d", number);
		delete[] resultMail;
		resultMail = stringMerge(tmpMail, tmp);
		number++;
		delete[] tmp;
	}
	delete[] tmpMail;

	return resultMail;
}

inline char* ituMail(char* mail){
	return stringMerge(mail, itu);
}

bool mailCheckTrue(char* surname, char* mail){

	char* tmpMail = ituMail(mail);

	for(studentInfo* traverse = checkSurnameNodes(surname)->headStudent; traverse != NULL; traverse = traverse->next)
		if(strcoll(traverse->email, tmpMail) == 0){delete[] tmpMail; return false;}
	delete[] tmpMail;
	return true;
}

void sortMail(studentInfo* tempStudent){

	surnameMap* pointer = checkSurnameNodes(tempStudent->surname);

	if(pointer->headStudent == NULL)	pointer->headStudent = tempStudent;

	else if(isSecondLonger(pointer->headStudent->email, tempStudent->email)){
		tempStudent->next = pointer->headStudent;
		pointer->headStudent->previous = tempStudent;
		pointer->headStudent = tempStudent;
	}

	else{
		studentInfo* tmp = pointer->headStudent;

		for(tmp = pointer->headStudent; tmp->next != NULL; tmp = tmp->next)
			if(isSecondLonger(tmp->next->email, tempStudent->email))	break;
		
		tempStudent->next = tmp->next;
		tempStudent->previous = tmp;
		tmp->next = tempStudent;
		if(tempStudent->next != NULL)		tempStudent->next->previous = tempStudent;
	}
}

//--------------------------------***ADDITIONAL FUNCTIONS***----------------------------------

char* stringMerge(char* first, char* second){

	int firstSize = strlen(first);
	int secondSize = strlen(second);
	char* merged = new char[firstSize+secondSize+1];

	for(int i = 0; i < firstSize; i++){
		merged[i] = first[i];
	}

	for(int i = firstSize; i < firstSize+secondSize; i++){
		merged[i] = second[i-firstSize];
	}
	merged[firstSize+secondSize] = '\0';

	return merged;
}

void wordNumb(){

	char c;

	fseek(inputFile, -2, SEEK_END);
	int totalSize = ftell(inputFile);

	fseek(inputFile, 0, SEEK_SET);

	for(int i = 0; i <= totalSize; i++){
		c = fgetc(inputFile);
		if(c == '\t')		lineNumber++;
	}

    fseek(inputFile, 0, SEEK_SET);
}

bool isSecondLonger(char* first, char* second){

	char* firstConv = convertToTurkish(first), *secondConv = convertToTurkish(second);
	int kullanilacak = strlen(secondConv);
	bool kisa = true;
	if(strlen(firstConv) < strlen(secondConv)){
		kullanilacak = strlen(firstConv);
		kisa = false;
	}

	for(int i = 0; i < kullanilacak || *(firstConv+i) == '@' || *(secondConv+i) == '@'; i++){
		if((*(firstConv+i)) < (*(secondConv+i))){kisa = false; break;}
		else if((*(secondConv+i)) < (*(firstConv+i))){kisa = true; break;}
	}
	delete[] firstConv;
	delete[] secondConv;
    return kisa;
}

char* toLowerWord(char* word){

	for(int i = 0; *(word+i) != '\0'; i++)
		(*(word+i) >= 'A' && *(word+i) <= 'Z') ? word[i] = tolower(word[i]) : word[i] = word[i];
	return word;
}

void writeToFile(){

	FILE* lastVersion = fopen("emailList.txt", "w");

	fprintf(lastVersion, "\t%-20s %s-%s\n\n", "e-mail", "Name", "Surname");
	surnameMap* traverse = headSurnameMap;

	for(int i = 0; i < surnameCount; fprintf(lastVersion, "%c", '\n'), traverse = traverse->next, i++){
		fprintf(lastVersion, "%s\n", traverse->surname);
		for(studentInfo* ptr = traverse->headStudent; ptr != NULL; ptr = ptr->next)
			fprintf(lastVersion, "\t%-20s %s %-20s\n", ptr->email, ptr->name, ptr->surname);
	}
	fclose(lastVersion);
	return;
}

char* convertToTurkish(char* word){

	int cnt = 0;	
	char* tmp, *result = new char[EMAIL_LENGTH];

	for(int i = 0; *(word+i) != '\0'; i++){
		if((*(word+i) >= 'a' && *(word+i) <= 'z') || (*(word+i) >= 'A' && *(word+i) < 'I') || (*(word+i) > 'I' && *(word+i) <= 'Z') || (*(word+i) >= '0' && *(word+i) <= '9') || *(word+i) == '@' || *(word+i) == '.')	*(result+cnt) = *(word+i);
		else if(*(word+i) == ' ')	continue;
		else{
			tmp = new char[3];
			*(tmp+0) = *(word+i);
            *(tmp+1) = *(word+i+1);
            *(tmp+2) = '\0';
			if		(strstr(tmp, "ç") || strstr(tmp, "Ç"))	*(result+cnt) = 'c';
			else if	(strstr(tmp, "ğ") || strstr(tmp, "Ğ"))	*(result+cnt) = 'g';
			else if (strstr(tmp, "I")){*(result+cnt) = 'i';	cnt++; delete[] tmp; continue;}
			else if	(strstr(tmp, "ı") || strstr(tmp, "İ"))	*(result+cnt) = 'i';
			else if	(strstr(tmp, "ö") || strstr(tmp, "Ö"))	*(result+cnt) = 'o';
			else if	(strstr(tmp, "ş") || strstr(tmp, "Ş"))	*(result+cnt) = 's';
			else if	(strstr(tmp, "ü") || strstr(tmp, "Ü"))	*(result+cnt) = 'u';
			else	cout << "Character can't be recognized..." << endl;
			i++;
			delete[] tmp;
		}
		cnt++;		
	}
	*(result+cnt) = '\0';
	return toLowerWord(result);
}

void tailAssigner(){

	if(headSurnameMap != NULL && surnameCount > 1){
		surnameMap* traveller = headSurnameMap;

		for(int i = 0; i < surnameCount-1; i++)
			traveller = traveller->next;
		tail = traveller;
		tail->next = headSurnameMap;
	}
	else	tail = NULL;
}

bool print_menu(){
	cout << endl << "\ne-mail Address Program:\nMain Menu:\n\n";
	if(!create)				cout << "1) Create\n";
	if(create && !insert)	cout << "2) Insert All\n";
	if(create && insert){
		cout << "3) Insert New Record\n";
		cout << "4) Delete Student\n";
		cout << "5) Delete Surname Node\n";
		cout << "6) Update\n";
		cout << "7) Write to File\n";
		cout << "L: List All Records\n";
		cout << "E: Press 'e' to exit.\n\n";
	}
	cout << "Please enter your choice:\n";	
	return select_option();
}

bool select_option(){

	char c;
	cin >> c;

	if			(!create && c == '1')	{createList();	create = true;}
	else if		(create){
		if		(!insert && c == '2')	{insertAll();	insert = true;}
		else if	(insert){
			if		(c == '3')	insertNewRecord(false);
			else if (c == '4')	deleteStudentMenu();
			else if (c == '5')	deleteSurnameNodeMenu();
			else if (c == '6')	updateList();
			else if (c == '7')	writeToFile();
			else if (c == 'L' || c == 'l')	listAll();
			else if (c == 'E' || c == 'e'){
				cout << endl << "\nAre you sure want to exit? (Y/N)\n" << endl;
				cin >> c;
				if		(c == 'Y' || c == 'y')		return true;
				else if	(c == 'N' || c == 'n')		cout << "Exit cancelled...";
			}
			else	wrong();
		}
		else	wrong();
	}
	else	wrong();	
	return false;
}

void wrong(){
	cout << endl << "You have selected invalid choice, please make a correct choice:\n";
	select_option();
}

void listAll(){

	surnameMap* traverse = headSurnameMap;

	for(int i = 0; i < surnameCount; traverse = traverse->next, i++){
		cout << traverse->surname << endl;

		for(studentInfo* ptr = traverse->headStudent; ptr != NULL; ptr = ptr->next)
			cout << "\t\t\t" << ptr->email << "\t\t\t" << ptr->name << " " << ptr->surname << endl;
		cout << endl;
	}
	return;
}

void insertNewRecord(bool mode){

	char* name = new char[NAME_LENGTH], *surname = new char[SURNAME_LENGTH];

	cout << "Please enter the name of the student:\t";
	if(!mode)	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGTH, '\n');
	cout << "Please enter the surname of the student:\t";
	cin.getline(surname, SURNAME_LENGTH, '\n');

	createNewSurnameNode(surname);
	newStudent(name, surname);
	delete[] name;
	delete[] surname;

	cout << "Record added/updated..." << endl;
	return;
}

void updateList(){

	char* mail = new char[EMAIL_LENGTH];
	cout << "Please enter the e-mail address of the student that you want to update:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(mail, EMAIL_LENGTH, '\n');
	bool mode = deleteStudent(mail);
	if(mode)	insertNewRecord(true);
	delete[] mail;
}

//--------------------------------------***DELETE FUNCTIONS***-------------------------------

void deleteStudentMenu(){

	char* mail = new char[EMAIL_LENGTH];
	cout << "Please enter the e-mail address of the student that you want to delete:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(mail, EMAIL_LENGTH, '\n');
	bool mode = deleteStudent(mail);
	if(mode)	 cout << endl << "Student with " << mail << " mail deleted successfully..." << endl;
	delete[] mail;
}

void deleteSurnameNodeMenu(){

	char* surname = new char[SURNAME_LENGTH];
	cout << "Please enter the surname that you want to delete:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(surname, SURNAME_LENGTH, '\n');
	bool mode = deleteSurnameNode(surname);
	if(mode)	cout << surname << " surname deleted successfully..." << endl;	
	delete[] surname;
}

bool deleteStudent(char* mail){

	bool endloop = false;

	surnameMap* traverse = headSurnameMap;
	studentInfo* ptr, *tmp;

	for(int i = 0; i < surnameCount; traverse = traverse->next ,i++){
		for(ptr = traverse->headStudent; ptr != NULL; ptr = ptr->next)
			if(strcoll(ptr->email, mail) == 0){
				cout << "Founded: " << ptr->email << "\t\t\t" << ptr->name << " " << ptr->surname << endl;
				endloop = true;
				break;
			}
		if(endloop)		break;
	}

	if(!endloop){
		cout << "Record can not be found..." << endl;
		return false;
	}
	char* tmpSurname = new char[strlen(ptr->surname)+1];	
	strcpy(tmpSurname, ptr->surname);	

	if(ptr == traverse->headStudent)	traverse->headStudent = ptr->next;

	else if(ptr->next != NULL){
		tmp = ptr->previous;
		tmp->next = ptr->next;
		tmp->next->previous = tmp;
	}
	
	else if(ptr->next == NULL){
		cout << ptr->previous->email << endl;
		tmp = ptr->previous;
		tmp->next = NULL;
		cout << tmp->email << endl;		
	}

	deleteStudentNode(ptr);
	if(checkSurnameNodes(tmpSurname)->headStudent == NULL)		deleteSurnameNode(tmpSurname);
	delete[] tmpSurname;
	return true;
}

bool deleteSurnameNode(char* surname){

	surnameMap* traverse, *surnamePtr = checkSurnameNodes(surname);
	if(surnamePtr == NULL){
		cout << "Surname can't found, please write surname with Turkish characters and also it's case sensitive..." << endl;
		return false;
	}
	studentInfo* tmp = surnamePtr->headStudent;

	if(tmp != NULL){
		while(tmp->next != NULL){
			tmp = tmp->next;			
			deleteStudent(tmp->previous->email);
		}
		deleteStudent(tmp->email);
	}
	if(tmp == NULL){
		if(surnamePtr == headSurnameMap)		headSurnameMap = headSurnameMap->next;
		else{
			for(traverse = headSurnameMap; traverse->next != surnamePtr; traverse = traverse->next);
			traverse->next = surnamePtr->next;
		}
		delete[] surnamePtr->surname;
		delete surnamePtr;
		surnameCount--;		
		tailAssigner();
	}
	return true;
}

void deleteStudentNode(studentInfo* ptr){

	delete[] ptr->name;
	delete[] ptr->surname;
	delete[] ptr->email;
	ptr->next = NULL;
	ptr->previous = NULL;
	delete ptr;
}

//---------------------------------------***SURNAME FUNCTIONS***-------------------------------

surnameMap* newSurnameNode(char* newSurname){

	surnameMap* tmp = new surnameMap;
	tmp->surname = new char[strlen(newSurname)+1];
	strcpy(tmp->surname, newSurname);
	tmp->next = NULL;
	tmp->headStudent = NULL;
	return tmp;
}

void createNewSurnameNode(char* surname){

	if(headSurnameMap == NULL){
		headSurnameMap = newSurnameNode(surname);
		surnameCount++;
	}

	else if(!checkSurnameNodes(surname)){
		surnameMap* tmp = newSurnameNode(surname);		
		if(isSecondLonger(headSurnameMap->surname, tmp->surname)){
			tmp->next = headSurnameMap;
			headSurnameMap = tmp;
		}
		else{
			surnameMap* traverse;
			for(traverse = headSurnameMap; traverse->next != headSurnameMap; traverse = traverse->next)
				if(isSecondLonger(traverse->next->surname, tmp->surname)) break;
			tmp->next = traverse->next;
			traverse->next = tmp;
		}
		surnameCount++;
		tailAssigner();
	}
}

surnameMap* checkSurnameNodes(char* isExist){
	
	surnameMap* traverse = headSurnameMap;

	for(int i = 0; i < surnameCount; i++, traverse = traverse->next)
		if(strcoll(traverse->surname, isExist) == 0) return traverse;
	
	return NULL;
}