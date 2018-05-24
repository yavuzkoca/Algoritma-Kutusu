/* @Author
 * Student Name: Vahit Buğra Yeşilkaynak
 * Student ID : 150150019
 * Date: 26 October 2017
 */

// To compile the code use  >>> g++ *.cpp
// Then to run the code use >>> ./a.out

// TODO: Boşluklu isim özelliği ekle
// TODO: Türkçe karakter özelliği ekle

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "surnameMap.h"

#define MAX_BUFFER_SIZE 80

using namespace std;

void print_menu();

int main(){
    const char *PATH_FOR_STUDENT_LIST = "newStudentsList.txt";
    const char *PATH_FOR_EMAIL_LIST = "emailList.txt";
    int choice = 0;
    surnameMap map;
    map.create();
    while(choice != 8){
        print_menu();
        cin >> choice; // Users selection from the menu
        if(choice == 1){
            map.createList(PATH_FOR_STUDENT_LIST); // My create also inserts only the surnames thus creates a surname list
            // but I also implemented a normal create function which just initializes things
            // createList also calls this function.
        }
        else if(choice == 2){ // Insert all the names and also assign emails
            map.insertAll(PATH_FOR_STUDENT_LIST);
        }
        else if(choice == 3){ // Take name and surname dynamically then add the student to the surnameMap
            char *temp_name = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            char *temp_surname = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            cout << "Please enter the name: ";
            cin >> temp_name;
            cout << "Please enter the surname: ";
            cin >> temp_surname;
            int name_size, surname_size;
            for(name_size = 0; *(temp_name + name_size) != '\0'; ++name_size);
            for(surname_size = 0; *(temp_surname + surname_size) != '\0'; ++surname_size);
            char *name = (char *)malloc(sizeof(char) * (name_size + 1));
            char *surname = (char *)malloc(sizeof(char) * (surname_size + 1));
            strcpy(name, temp_name);
            strcpy(surname, temp_surname);
            free(temp_name);
            free(temp_surname);
            map.insertNewRecord(name, surname, name_size + 1, surname_size + 1);
            free(name);
            free(surname);
        }
        else if(choice == 4){ // Take name and surname then delete the student
            char *temp_name = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            char *temp_surname = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            cout << "Please enter the name: ";
            cin >> temp_name;
            cout << "Please enter the surname: ";
            cin >> temp_surname;
            int name_size, surname_size;
            for(name_size = 0; *(temp_name + name_size) != '\0'; ++name_size);
            for(surname_size = 0; *(temp_surname + surname_size) != '\0'; ++surname_size);
            char *name = (char *)malloc(sizeof(char) * (name_size + 1));
            char *surname = (char *)malloc(sizeof(char) * (surname_size + 1));
            strcpy(name, temp_name);
            strcpy(surname, temp_surname);
            free(temp_name);
            free(temp_surname);
            map.deleteStudent(name, surname);
            free(name);
            free(surname);
        }
        else if(choice == 5){ // Take surname and then delete that surnameNode
            char *temp_surname = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            cout << "Please enter the surname: ";
            cin >> temp_surname;
            int surname_size;
            for(surname_size = 0; *(temp_surname + surname_size) != '\0'; ++surname_size);
            char *surname = (char *)malloc(sizeof(char) * surname_size);
            strcpy(surname, temp_surname);
            free(temp_surname);
            map.deleteSurnameNode(surname);
            free(surname);
        }
        else if(choice == 6){ // Take name and surname of a student then change it
            char *temp_name_old = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            char *temp_surname_old = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            cout << "Please enter the name of the student you want to update:" << endl;
            cin >> temp_name_old;
            cout << "Please enter the surname of the student you want to update:" << endl;
            cin >> temp_surname_old;
            int name_size_old, surname_size_old;
            for(name_size_old = 0; *(temp_name_old + name_size_old) != '\0'; ++name_size_old);
            for(surname_size_old = 0; *(temp_surname_old + surname_size_old) != '\0'; ++surname_size_old);
            char *name_old = (char *)malloc(sizeof(char) * (name_size_old + 1));
            char *surname_old = (char *)malloc(sizeof(char) * (surname_size_old + 1));
            strcpy(name_old, temp_name_old);
            strcpy(surname_old, temp_surname_old);
            free(temp_name_old);
            free(temp_surname_old);

            char *temp_name_new = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            char *temp_surname_new = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);
            cout << "Please enter the new name: ";
            cin >> temp_name_new;
            cout << "Please enter the new surname: ";
            cin >> temp_surname_new;
            int name_size_new, surname_size_new;
            for(name_size_new = 0; *(temp_name_new + name_size_new) != '\0'; ++name_size_new);
            for(surname_size_new = 0; *(temp_surname_new + surname_size_new) != '\0'; ++surname_size_new);
            char *name_new = (char *)malloc(sizeof(char) * (name_size_new + 1));
            char *surname_new = (char *)malloc(sizeof(char) * (surname_size_new + 1));
            strcpy(name_new, temp_name_new);
            strcpy(surname_new, temp_surname_new);
            free(temp_name_new);
            free(temp_surname_new);
            map.updateList(name_old, surname_old, name_new, surname_new);
            free(name_old);
            free(name_new);
            free(surname_old);
            free(surname_new);
        }
        else if(choice == 7 ){ // Write the name, surname and emails to a txt file
            map.writeToFile(PATH_FOR_EMAIL_LIST);
        }
        else if(choice != 8){ // If input is not valid
            printf("Please enter a valid input.\n");
        }
    }
    map.clearAll(); // Empty before closing
}

void print_menu(){
    cout << endl << "E-mail Adress Program:" << endl;
    cout << "1) Create" << endl;
    cout << "2) Insert All" << endl;
    cout << "3) Insert New Record" << endl;
    cout << "4) Delete Student" << endl;
    cout << "5) Delete Surname Node" << endl;
    cout << "6) Update" << endl;
    cout << "7) Write to File" << endl;
    cout << "8) Exit" << endl << endl;
    cout << "Enter a choice : ";
}
