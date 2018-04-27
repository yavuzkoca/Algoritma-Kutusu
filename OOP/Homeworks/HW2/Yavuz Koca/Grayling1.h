#ifndef HW2_Grayling1_H
#define HW2_Grayling1_H

#include <iostream>
#include "Grayling.h"

class Grayling1 : public Grayling{
    short int _dying_age;
public:
    Grayling1(char, std::string);
    Grayling1(const Grayling1&, char, std::string);
    void print() const override;
    void aging() override;
    void givebirth() override;
};


#endif //HW2_Grayling1_H
