/* @Author
* Student Name: Yavuz Koca
* Student ID : 150150043
* Date: 31.10.2017
*/
/*
 * I had some trouble with writing char arrays. The problem was the '\r' character. To prevent this issue
 * I printed all string variables in for loop to check the character is \r or not. If it is, don't print it.
 * That's why printing steps 5-10 lines longer.
 *
 */
#include <iostream>
#include <cstring>
#include <string>
#include "List.h"
#include "Functions.h"
#include <cstdlib>
#include <fstream>

using namespace std;

// Function declarations
void insertAll(); // Insert record from file
void insertNewRecord(); // Insert record from terminal/console by manually
void deleteSurnameNode(); // Delete students who has given surname
void deleteStudent(); // Delete a student
void printAllStudents(); // Print all students
void printSurnameStudents(); // Print students who has given surname
void writeToFile();
bool operation(char op); // Performs menu operations
void close();

// Variable declarations
List L;

int main(){
    printWelcome();
    bool proceed = true;
    char option;
    while(proceed){
        printMenu();
        cin >> option;
        proceed = operation(option);
    }
    bye();
    close();
    L.printList();
    return 0;
}

void insertAll(){
    ifstream emailText("newStudentsList.txt");
    if(emailText){
        string s;
        size_t space;
        while (! emailText.eof()){
            getline(emailText, s);
            for(int i=0; i<s.length(); i++){
                if(s[i] == '\n' || s[i] == '\r' || i == s.length()-1){ // If this is end of the line, then add the student
                    // First name is from beginning to last space index
                    string temp(s, 0, space);
                    char *firstName = new char[temp.length()+1];
                    strcpy(firstName, temp.c_str());
                    firstName[strlen(firstName)] = '\0';

                    // Surname is rest of the string
                    string temp2(s, temp.length()+1);
                    char *surName = new char[temp2.length()+1];
                    strcpy(surName, temp2.c_str());
                    surName[strlen(surName)] = '\0';

                    // Add the student
                    L.addData(surName, firstName);
                    break;
                }else if(s[i] == ' ' || s[i] == '\t'){ // If there is space, mark the index.
                    // I did this part to read students with two or more first name
                    space = i;
                }
            }
        }
        emailText.close();
    }else{
        cout << "Couldn't open the file" << endl;
        exit(1);
    }
}

void insertNewRecord(){
    // This parts works almost same as insertAll function. Necessary explanation given in that function
    string s;
    size_t space;
    cout << "Enter the full name of the student: ";
    cin.ignore(1000, '\n');
    getline(cin, s);

    for(int i=0; i<s.length(); i++){
        if(s[i] == '\n' || s[i] == '\r'){
            break;
        }else if(s[i] == ' ' || s[i] == '\t'){
            space = i;
        }
    }

    string temp(s, 0, space);
    char *firstName = new char[temp.length()+1];
    strcpy(firstName, temp.c_str());
    firstName[strlen(firstName)] = '\0';

    string temp2(s, temp.length()+1);
    char *surName = new char[temp2.length()+1];
    strcpy(surName, temp2.c_str());
    surName[strlen(surName)] = '\0';
    L.addData(surName, firstName);
    delete[] firstName;
    delete[] surName;
}

void deleteSurnameNode(){
    cout << "Enter the surname you want to delete: " << endl;
    char input[80];
    scanf("%s", input);
    if(L.deleteSurname(input))
        cout << "\nYou have deleted " << input << " surname successfully." << endl;
    else
        cout << "\nWe couldn't delete this surname for some reasons!" << endl;
}

void deleteStudent(){
    cout << "Enter the surname of the student you want to delete: " << endl;
    char s[80], email[80];
    scanf("%s", s);
    cout << "Enter the email address of the student you want to delete (Don't write @itu.edu.tr): " << endl;
    scanf("%s", email);
    if(L.deleteStudent(s, email))
        cout << "\nYou have deleted this email '" << email << "' successfully." << endl;
    else
        cout << "\nWe couldn't delete this Student for some reasons!" << endl;
}

void updateStudent(){
    cout << "Enter the surname of the student you want to update: " << endl;
    char s[80], email[80];
    scanf("%s", s);
    cout << "Enter the email address of the student you want to update (Don't write @itu.edu.tr): " << endl;
    scanf("%s", email);
    if(L.deleteStudent(s, email)){
        insertNewRecord();
    }else{
        cout << "\nAn error has occurred!" << endl;
    }

}

bool operation(char op){
    if(op >= 'a' && op <= 'z')
        op = op - 'a' + 'A';

    if(op == 'E')
        return false;
    else if(op == 'A')
        insertNewRecord();
    else if (op == 'L')
        printAllStudents();
    else if(op == 'I')
        insertAll(); // Open txt files
    else if(op == 'D')
        deleteSurnameNode();
    else if(op == 'S')
        deleteStudent();
    else if(op == 'U')
        updateStudent();
    else if(op == 'W')
        writeToFile();
    else if(op == 'K')
        printSurnameStudents();

    return true;
}

void printAllStudents(){
    L.printList();
}

void printSurnameStudents(){
    cout << "Enter the surname of the students you want to print:\n";
    char s[80];
    cin >> s;
    L.printSurname(s);
}

void writeToFile(){
    L.writeToFile();
}

void close(){
    L.deleteAll();
}

