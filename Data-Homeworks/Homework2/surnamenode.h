/* @Author
 * Student Name: Gizem Ece Avsar
 * Student ID : 040140303
 * Date: 30/10/2017
 */

//compilation command: g++ -std=c++11 surname.cpp

#ifndef surnamenode_h
#define surnamenode_h

#include "studentinfo.h"
#include "surnamemap.h"

struct surnameNode{
    
    char* surname = new char[80];
    studentInfo* student_head = nullptr;
    surnameNode* next = nullptr;
    int student_count = 0;
};


#endif /* surnamenode_h */
