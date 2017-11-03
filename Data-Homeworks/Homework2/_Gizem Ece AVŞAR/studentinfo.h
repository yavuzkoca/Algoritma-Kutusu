/* @Author
 * Student Name: Gizem Ece Avsar
 * Student ID : 040140303
 * Date: 30/10/2017
 */

//compilation command: g++ -std=c++11 surname.cpp

#ifndef studentinfo_h
#define studentinfo_h

#include "surnamenode.h"
#include "surnamemap.h"

struct studentInfo{
    
    char* name = new char[80];
    char* surname = new char[80];
    char* email = new char[80];
    studentInfo* next = nullptr;
    studentInfo* prev = nullptr;
    
};

#endif /* studentinfo_h */
