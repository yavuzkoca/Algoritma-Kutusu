#ifndef CITIZEN_H
#define CITIZEN_H

#include <iostream>
#include "Time.h"

class Citizen
{
    char *idNo;
    char *name;
    char *surname;
    bool hasApp;
    Time *appTime;  //yoksa NULL;
    char *appSlot;

public:
    Citizen(char *idNo, char *name, char *surname, bool hasApp,
                Time appTime,char *slot);
    ~Citizen();
    inline Time getAppTime(){return *appTime;}
    inline const bool getAppState() {return hasApp;}
    const std::string get_appSlot();
    inline const std::string get_name(){return std::string(name);}
};

#endif // CITIZEN_H
