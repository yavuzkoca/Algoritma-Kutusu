#ifndef YAVUZ_KOCA_MONEY_H
#define YAVUZ_KOCA_MONEY_H

class Money {
    int lira;
    int kurus;
public:
    Money(int, int);
    Money() = default;
    void getMoney() const ;
    Money& operator=(int);
    bool operator<(int) const;
    bool operator>(int) const;
    Money& operator+=(const Money& money);
    Money& operator+=(int);
    Money& operator-=(int);
    friend std::ostream & operator<<( std::ostream &output, const Money&);
};


#endif
