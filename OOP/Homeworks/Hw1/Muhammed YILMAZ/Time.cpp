#include "Time.h"

Time::Time(int day, int month, int year, int hour, int minute)
{
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minute = minute;
}

Time::~Time()
{
}

std::string Time::getTime() const
{
    char timeChar[20];
    if(hour < 10)
        sprintf(timeChar, "0%d", hour);
    else
        sprintf(timeChar, "%d", hour);
    if(minute < 10)
        sprintf(timeChar, "%s.0%d",timeChar, minute);
    else
        sprintf(timeChar, "%s.%d",timeChar, minute);
    if(day < 10)
        sprintf(timeChar, "%s 0%d", timeChar, day);
    else
        sprintf(timeChar, "%s %d", timeChar, day);
    if(month < 10)
        sprintf(timeChar, "%s/0%d", timeChar, month);
    else
        sprintf(timeChar, "%s/%d", timeChar, month);
    if(year < 10)
        sprintf(timeChar, "%s/200%d",timeChar, year);
    else if(year < 100)
        sprintf(timeChar, "%s/20%d",timeChar, year);
    else
        sprintf(timeChar, "%s/%d",timeChar, year);

    std::string time(timeChar);
    return time;
}

// appDate'i "yyyy/mm/dd" formatında döndürür.
std::string Time::get_date() const
{
    char dateChar[11];
    if(year < 10)
        sprintf(dateChar, "200%d", year);
    else if(year < 100)
        sprintf(dateChar, "20%d", year);
    else
        sprintf(dateChar, "%d", year);

    if(month < 10)
        sprintf(dateChar, "%s/0%d", dateChar, month);
    else
        sprintf(dateChar, "%s/%d", dateChar, month);

    if(day < 10)
        sprintf(dateChar, "%s/0%d", dateChar, day);
    else
        sprintf(dateChar, "%s/%d", dateChar, day);

    std::string date(dateChar);
    return date;
}

/* compares two Time objects (this and argument) and returns true if time
 * value of this is earlier than the time value of the argument.
 */
bool Time::operator<(const Time &b)
{
    if(this->year < b.year)
        return true;
    else if(this->year > b.year)
        return false;

    else if(this->month < b.month)
        return true;
    else if(this->month > b.month)
        return false;

    else if(this->day < b.day)
        return true;
    else if(this->day > b.day)
        return false;

    else if(this->hour < b.hour)
        return true;
    else if(this->hour > b.hour)
        return false;

    else if(this->minute < b.minute)
        return true;
    else if(this->minute > b.minute)
        return false;

    else
        return false;
}

/* compares two Time objects (this and argument) and returns true if time
 * value of this is later than the time value of the argument.
 */
bool Time::operator>(const Time &b)
{
    if(this->year < b.year)
        return false;
    else if(this->year > b.year)
        return true;

    else if(this->month < b.month)
        return false;
    else if(this->month > b.month)
        return true;

    else if(this->day < b.day)
        return false;
    else if(this->day > b.day)
        return true;

    else if(this->hour < b.hour)
        return false;
    else if(this->hour > b.hour)
        return true;

    else if(this->minute < b.minute)
        return false;
    else if(this->minute > b.minute)
        return true;

    else
        return false;

}

/* compares two Time objects (this and argument) and returns true if time
 * value of this is equal to the time value of the argument.
 */
bool Time::operator==(const Time &b)
{

    if(day == b.day && month == b.month && year == b.year &&
            hour == b.hour && minute == b.minute)
        return true;
    else
        return false;
}
