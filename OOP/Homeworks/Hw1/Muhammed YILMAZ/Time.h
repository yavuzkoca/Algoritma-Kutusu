#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
public: //operatörler inline
    Time(int day, int month, int year, int hour, int minute);
    ~Time();
    std::string getTime() const;
    std::string get_date() const;
    bool operator<(const Time &b);
    bool operator>(const Time &b);
    bool operator==(const Time &b);
};

#endif // TIME_H
