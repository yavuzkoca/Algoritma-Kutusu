#ifndef ALGORITMA_KUTUSU_CITIZEN_H
#define ALGORITMA_KUTUSU_CITIZEN_H

#include "Time.h"

class Citizen {
    char *idNo, *name, *surname, *appSlot;
    bool hasApp;
    Time *appTime;
    void setIdNo(const char *idNo);
    void setName(const char *name);
    void setSurname(const char *surname);
    void setAppSlot(const char *appSlot);
public:
    Citizen(const char *idNo, const char *name, const char *surname, const char *appSlot, bool hasApp, Time *appTime);
    string getAppTime();
    string getName();
    bool getHasApp();
    bool operator<(const Citizen& citizen);
    Time* GetAppTime();
    ~Citizen();
};


#endif //ALGORITMA_KUTUSU_CITIZEN_H
