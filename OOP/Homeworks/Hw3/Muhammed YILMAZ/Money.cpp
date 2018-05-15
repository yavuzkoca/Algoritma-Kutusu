/* HEADER : MONEY CLASS FUNCTIONS
 * AUTHOR : Muhammed YILMAZ
 * DATE   : 13.05.2018
 * E-MAIL : yilmazmu15@itu.edu.tr
 */

#include <iostream>
#include "Money.h"
#include "color.h"

Money::Money(int inLira, int inKurus) {
    // kurus and lira are defined by coming value.
    try {
        // If value is smaller than 0, return throw
        if(inLira*100 + inKurus < 0)
            throw "The amount of money can not be below zero!";
        this->kurus = inKurus % 100;
        this->lira = inLira + (inKurus / 100);
    }
    // If catch throw, it is being printed to screen with color
    // Color maybe is not printed, if it is being, output maybe has color code
    catch (const char *result){
        std::cout << COLOR_FG_RED << result << COLOR_FG_DEF << std::endl;
    }
}

// Sum operator overloading for Money
Money Money::operator+(const Money &obj) {
    return Money(this->lira + obj.lira + (this->kurus + obj.kurus)/100, (this->kurus + obj.kurus)%100);
}

// Minus operator overloading for Money
Money Money::operator-(const Money &obj) {
    return Money(( (this->lira*100 + this->kurus) - (obj.lira*100 + obj.kurus) ) / 100 , (100 + this->kurus - obj.kurus) % 100);
}

// Sum-equivalent operator overloading for Money
Money &Money::operator+=(const Money &obj) {
    this->lira = this->lira + obj.lira + (this->kurus + obj.kurus)/100;
    this->kurus = (this->kurus + obj.kurus)%100;
    return *this;
}

// Minus-equivalent operator overloading for Money
// Money cannot be created less than zero, so I think difference of two Money cannot be.
Money &Money::operator-=(const Money &obj) {
    *this = *this - obj;
    return *this;
}

// For printing Money obje with std::cout
std::ostream &operator<<(std::ostream &os, const Money &obj) {
    return os << obj.lira << " lira " << obj.kurus << " kurus";
}