#include <iostream>
#include "Money.h"

#define END std::cout << std::endl;


/*
 * If lira or kurus less than 0, throw an exception
 * If kurus more than 99, throw an exception
 */
Money::Money(int lira, int kurus) {
    try{
        if(lira < 0 || kurus < 0){
            throw "The amount of money can not be below zero!";
        }
        if( kurus > 99){
            throw "The amount of kurus can not be more than 99!";
        }
    }catch (const char* msg){
        std::cout << msg; END
    }

    this->lira = lira;
    this->kurus = kurus;
}


/*
 * Prints the current money
 */
void Money::getMoney() const {
    std::cout << "Lira: " << this->lira << " Kurus: " << this->kurus; END
}


/*
 * To set 'total' attribute to zero in the GenericArray Class, I wrote this function
 */
Money& Money::operator=(int num) {
    this->lira = num;
    this->kurus = num;
}


/*
 * Checks if the money is less than 'num'. If it is return true, false otherwise.
 */
bool Money::operator<(int num) const {
    return this->kurus < num || this->lira < num;
}


/*
 * This function has written for the 'sum' function in the GenericArray class.
 * Adds 'lira' and 'kurus' attributes. At the end, if 'kurus' is more than 100,
 * add the carry amount to 'lira' attribute and update the 'kurus' attribute
 */
Money& Money::operator+=(const Money &money) {
    this->lira += money.lira;
    this->kurus += money.kurus;

    if(this->kurus >= 100){
        this->lira += (this->kurus / 100);
    }
    this->kurus %= 100;
}


/*
 * If money is more than 100 returns true to add 5 more points. That is why only checked lira attribute
 */
bool Money::operator>(int a) const {
    return this->lira > a;
}


/*
 * If money object is more than 100 lira, add 5 more lira to 'lira' attribute
 */
Money &Money::operator+=(int a) {
    this->lira += a;
}


/*
 * If money object is less than 100 lira, subtract 5 lira from 'lira' attribute
 */
Money &Money::operator-=(int a) {
    this->lira -= a;
}


/*
 * to print current money by writing "std::cout << this->total;" I wrote this function.
 */
std::ostream & operator << (std::ostream &output, const Money &money) {
    output << money.lira << " lira " << money.kurus << " kurus.";
    return output;
}
