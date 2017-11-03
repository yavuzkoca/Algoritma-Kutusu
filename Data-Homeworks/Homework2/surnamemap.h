/* @Author
 * Student Name: Gizem Ece Avsar
 * Student ID : 040140303
 * Date: 30/10/2017
 */

//compilation command: g++ -std=c++11 surname.cpp

#ifndef surnamemap_h
#define surnamemap_h

#include "surnamenode.h"
#include "studentinfo.h"

struct surnameMap{
    
    surnameNode* head = nullptr;
    int surname_count = 0;
    bool is_created_before = false;
    void create_list();
    void add_surname(studentInfo*);
    void add_student(char*, char*);
    char* email_generator(char*, char*);
    void read_file();
    void list_map_to_screen();
    void list_map_to_file();
    void delete_surname(char*);
    void delete_student(char*, char*);
    void delete_on_screen(int);
    void update_student(char*, char*);
    void dummy_create();
    void update_on_screen();
    void add_from_screen();
    void delete_everything();
    
};


#endif /* surnamemap_h */
