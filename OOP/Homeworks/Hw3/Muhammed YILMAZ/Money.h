/* HEADER : MONEY CLASS HEADER
 * AUTHOR : Muhammed YILMAZ
 * DATE   : 13.05.2018
 * E-MAIL : yilmazmu15@itu.edu.tr
 */

#ifndef MONEY_H
#define MONEY_H
#include <ostream>

class Money {
    friend std::ostream &operator<<(std::ostream &os, Money const &m);
private:
    int lira;
    int kurus;
public:
    explicit Money(int inLira = 0, int inKurus = 0);
    ~Money() = default;
    Money operator+(const Money &obj);
    Money operator-(const Money &obj);
    Money &operator+=(const Money &obj);
    Money &operator-=(const Money &obj);
    inline bool operator<(const Money &obj) {
        return this->lira * 100 + this->kurus < obj.lira * 100 + obj.kurus;}
    inline bool operator>(const Money &obj) {
        return this->lira * 100 + this->kurus > obj.lira * 100 + obj.kurus;}
};

#endif //MONEY_H
