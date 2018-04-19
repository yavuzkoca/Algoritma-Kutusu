#ifndef ALGORITMA_KUTUSU_TIME_H
#define ALGORITMA_KUTUSU_TIME_H

#include <string>

using namespace std;

class Time {
    int day, month, year, hour, minute;
public:
    Time(int, int, int, int, int);
    string getTime(int);
    bool operator<(const Time& time);
    bool operator>(const Time& time);
    bool operator==(const Time& time);
};


#endif //ALGORITMA_KUTUSU_TIME_H
