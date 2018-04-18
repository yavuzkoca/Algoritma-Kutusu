#ifndef CIVILREGISTRY_H
#define CIVILREGISTRY_H

#include "Citizen.h"
#include <iostream>
#include <list>

class CivilRegistry
{
    std::list <Citizen> wApp;
    std::list <Citizen> wOutApp;
    void insert_citizen_to_wApp(Citizen *newCitizen);
    void insert_citizen_to_wOutApp(Citizen *newCitizen);
    bool citizen_minor_operator(Citizen a, Citizen b);
public:
    CivilRegistry();  //The constructor may take values according to attribute values.
    void insertCitizen(Citizen *newCitizen);
    int removeCitizen(int whichList);
};
#endif // CIVILREGISTRY_H
