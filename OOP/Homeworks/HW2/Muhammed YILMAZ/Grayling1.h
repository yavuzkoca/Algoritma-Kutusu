/*
 * Muhammed YILMAZ
 * 150150149
 * 23.04.2018
 */

#ifndef OOP_HW2_GRAYLING1_H
#define OOP_HW2_GRAYLING1_H


#include <iostream>
#include "Grayling.h"

class Grayling1: public Grayling {
private:
    void kill_him();
    short ageOfDied;
private:
    void killOrNot();
    bool mutatedTo();
public:
    Grayling1() : Grayling() {}
    Grayling1(char inGender, std::string inName);
    Grayling1(const Grayling1 &obj, char inGender, std::string inName);
    ~Grayling1();
    void print() override;
    void aging() override;
    int givebirth() override;
};


#endif //OOP_HW2_GRAYLING1_H
