#include <cstring>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Citizen.h"
#define pb push_back

/*
 * This function takes a string and a delimiter character.
 * It returns a vector with exploded string via given delimiter.
 */
vector<string> explode(string const &s, char d) {
    std::istringstream iss(s);
    vector<string> exploded;
    string piece;

    while(getline(iss, piece, d))
        exploded.pb(move(piece));

    return exploded;
}

/*
 * This constructor, sets the values of given citizen.
 */
Citizen::Citizen(const char *idNo, const char *name, const char *surname, const char *appSlot, bool hasApp, Time *appTime) {
    setIdNo(idNo);
    setName(name);
    setSurname(surname);
    setAppSlot(appSlot);
    this->hasApp = hasApp;
    this->appTime = appTime;
}

void Citizen::setAppSlot(const char *appSlot) {
    if(appSlot == nullptr){
        this->appSlot = nullptr;
        return;
    }
    Citizen::appSlot = new char[strlen(appSlot) + 1];
    strcpy(Citizen::appSlot, appSlot);
    Citizen::appSlot[strlen(appSlot)] = '\0';
}

void Citizen::setSurname(const char *surname) {
    Citizen::surname = new char[strlen(surname) + 1];
    strcpy(Citizen::surname, surname);
    Citizen::surname[strlen(surname)] = '\0';
}

void Citizen::setName(const char *name) {
    Citizen::name = new char[strlen(name) + 1];
    strcpy(Citizen::name, name);
    Citizen::name[strlen(name)] = '\0';
}

void Citizen::setIdNo(const char *idNo) {
    Citizen::idNo = new char[strlen(idNo) + 1];
    strcpy(Citizen::idNo, idNo);
    Citizen::idNo[strlen(idNo)] = '\0';
}

string Citizen::getAppTime() {
    return this->GetAppTime()->getTime(0);
}

/*
 * Delete the taken memory which has been taken in constructor.
 */
Citizen::~Citizen() {
    delete[] this->idNo;
    delete[] this->surname;
    if(this->getHasApp())
        delete[] this->appSlot;
    delete[] this->name;
    // delete this->appTime;
}

/*
 * This operator overload helps wApp and wOutApp lists to be sorted.
 * First it controls year, month and day. Then Appointment Slot, after all entry clock.
 */
bool Citizen::operator<(const Citizen &citizen) {
    if((this->appTime->getTime(3)) < (citizen.appTime->getTime(3))) return true;
    if((this->appTime->getTime(3)) > (citizen.appTime->getTime(3))) return false;
    if((this->appTime->getTime(2)) < (citizen.appTime->getTime(2))) return true;
    if((this->appTime->getTime(2)) > (citizen.appTime->getTime(2))) return false;
    if((this->appTime->getTime(1)) < (citizen.appTime->getTime(1))) return true;
    if((this->appTime->getTime(1)) > (citizen.appTime->getTime(1))) return false;
    if(this->hasApp && citizen.hasApp){
        vector<string> v1 = explode2(this->appSlot, '.');
        vector<string> v2 = explode2(citizen.appSlot, '.');
        if(stoi(v1[0]) < stoi(v2[0])) return true;
        if(stoi(v1[0]) > stoi(v2[0])) return false;
        if(stoi(v1[1]) < stoi(v2[1])) return true;
        if(stoi(v1[1]) > stoi(v2[1])) return false;
    }
    if(stoi(this->appTime->getTime(4)) < stoi(citizen.appTime->getTime(4))) return true;
    if(stoi(this->appTime->getTime(4)) > stoi(citizen.appTime->getTime(4))) return false;
    if(stoi(this->appTime->getTime(5)) < stoi(citizen.appTime->getTime(5))) return true;
    if(stoi(this->appTime->getTime(5)) > stoi(citizen.appTime->getTime(5))) return false;
    return false;
}

string Citizen::getName() {
    return this->name;
}

bool Citizen::getHasApp() {
    return this->hasApp;
}

Time* Citizen::GetAppTime() {
    return this->appTime;
}
