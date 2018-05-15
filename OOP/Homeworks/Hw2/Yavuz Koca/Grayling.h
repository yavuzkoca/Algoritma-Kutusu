#ifndef HW2_Grayling_H
#define HW2_Grayling_H

#include <iostream>

class Grayling {
protected:
    double _MP;
    double _MPI;
    bool _mutant;
    double _mutate_at;
    std::string _mutated_name;
    const std::string _name;
    const char _gender;
    short int _age;
    bool _alive;
public:
    Grayling(char, std::string);
    Grayling();
    virtual void print() const=0;
    virtual void aging()=0;
    virtual void givebirth()=0;
};


#endif //HW2_Grayling_H
