#ifndef ALGORITMA_KUTUSU_CIVILREGISTRY_H
#define ALGORITMA_KUTUSU_CIVILREGISTRY_H


#include "Citizen.h"
#include <list>

class CivilRegistry {
    list<Citizen> wApp;
    list<Citizen> wOutApp;
public:
    CivilRegistry();
    void insertCitizen(Citizen*);
    void removeCitizen(int);
    void getAllCitizens();
};


#endif //ALGORITMA_KUTUSU_CIVILREGISTRY_H
