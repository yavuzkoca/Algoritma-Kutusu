#include "Time.h"
#include <sstream>
using namespace std;

string Time::getTime(int param=0){
    if(param == 0){
        stringstream ss;
        ss << this->hour << ".";
        if(this->minute < 10) ss << "0";
        ss << this->minute << " " << this->day << "/" << this->month << "/" << this->year;
        return ss.str();
    }if(param == 1){ // Day
        return to_string(this->day);
    }if(param == 2){ // Month
        return to_string(this->month);
    }if(param == 3){ // Year
        return to_string(this->year);
    }if(param == 4){ // Hour
        return to_string(this->hour);
    }if(param == 5){ // Minute
        return to_string(this->minute);
    }

}

Time::Time(int day, int month, int year, int hour, int minute) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minute = minute;
}

bool Time::operator<(const Time &time) {
    if(this->year < time.year) return true;
    if(this->year > time.year) return false;
    if(this->month < time.month) return true;
    if(this->month > time.month) return false;
    if(this->day < time.day) return true;
    if(this->day > time.day) return false;
    if(this->hour < time.hour) return true;
    if(this->hour > time.hour) return false;
    if(this->minute < time.minute) return true;
    if(this->minute > time.minute) return false;
    return false;
}

bool Time::operator>(const Time &time) {
    if(this->year < time.year) return false;
    if(this->year > time.year) return true;
    if(this->month < time.month) return false;
    if(this->month > time.month) return true;
    if(this->day < time.day) return false;
    if(this->day > time.day) return true;
    if(this->hour < time.hour) return false;
    if(this->hour > time.hour) return true;
    if(this->minute < time.minute) return false;
    return this->minute > time.minute;
}

bool Time::operator==(const Time &time) {
    return this->year == time.year && this->month == time.month &&
            this->day == time.day && this->hour == time.hour && this->minute == time.minute;
}
