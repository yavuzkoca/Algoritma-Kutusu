/*
 * Muhammed YILMAZ
 * 150150149
 * 23.04.2018
 */

#ifndef OOP_HW2_GRAYLING_H
#define OOP_HW2_GRAYLING_H

#include <iostream>

using namespace std;

class Grayling {
private:
    void kill_him();
protected:
    short age;
    string name;
    char gender;
    bool isAlive;
    bool isMutant;
    string mutatedToForm;
    double mpi;
    double mp;
    double mutateAt;
    //virtual bool mutatedTo();
    //virtual void killOrNot();
public:
    Grayling();
    Grayling(char inGender, std::string inName) :
            age(0), name(std::move(inName)), gender(inGender),
            isAlive(true), isMutant(false), mutatedToForm(""),
            mpi(0), mp(0), mutateAt(0) {}
    Grayling(const Grayling& obj, char inGender, std::string inName) :
            age(obj.age), name(std::move(inName)), gender(inGender),
            isAlive(obj.isAlive), isMutant(obj.isMutant),
            mutatedToForm(obj.mutatedToForm), mpi(obj.mpi),
            mp(obj.mp), mutateAt(obj.mutateAt) {}
    ~Grayling();
    virtual void print();
    virtual int givebirth();
    virtual void aging();
};

#endif //OOP_HW2_GRAYLİNG_H
