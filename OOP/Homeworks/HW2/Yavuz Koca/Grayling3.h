#ifndef HW2_Grayling3_H
#define HW2_Grayling3_H

#include "Grayling.h"
#include <iostream>

class Grayling3 : public Grayling {
    const short int _dying_age;
public:
    Grayling3(char, std::string);
    Grayling3(const Grayling3&, char, std::string);
    void print() const override;
    void aging() override;
    void givebirth() override;
};


#endif //HW2_Grayling3_H
