/*
 * Muhammed YILMAZ
 * 150150149
 * 23.04.2018
 */

#ifndef OOP_HW2_GRAYLING2_H
#define OOP_HW2_GRAYLING2_H


#include "Grayling.h"

class Grayling2: public Grayling {
private:
    void kill_him();
    short ageOfDied;
private:
    void killOrNot();
    bool mutatedTo();
public:
    Grayling2() : Grayling() {}
    Grayling2(char inGender, std::string inName);
    Grayling2(const Grayling2 &obj, char inGender, std::string inName);
    ~Grayling2();
    void print() override;
    void aging() override;
    int givebirth() override;
};


#endif //OOP_HW2_GRAYLING2_H
