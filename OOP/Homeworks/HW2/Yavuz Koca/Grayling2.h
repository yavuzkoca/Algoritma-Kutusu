#ifndef HW2_Grayling2_H
#define HW2_Grayling2_H

#include <iostream>
#include "Grayling.h"

class Grayling2 : public Grayling{
    short int _dying_age;
protected:

public:
    Grayling2(char, std::string);
    Grayling2(const Grayling2&, char, std::string);
    void print() const override;
    void aging() override;
    void givebirth() override;
};


#endif //HW2_Grayling2_H
