/*
 * Muhammed YILMAZ
 * 150150149
 * 23.04.2018
 */

#ifndef OOP_HW2_GRAYLING3_H
#define OOP_HW2_GRAYLING3_H

#include "Grayling.h"

class Grayling3: public Grayling {
private:
    void kill_him();
    short ageOfDied;
private:
    void killOrNot();
public:
    Grayling3() : Grayling() {}
    Grayling3(char inGender, std::string inName);
    Grayling3(const Grayling3 &obj, char inGender, std::string inName);
    ~Grayling3();
    void print() override;
    void aging() override;
    int givebirth() override;

};

#endif //OOP_HW2_GRAYLING3_H
