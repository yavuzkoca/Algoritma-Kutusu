#include "CivilRegistry.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>

#define pb push_back
// using namespace std;

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
 * Read the input.txt file and put every citizen to related list. Then sort them by citizen < operator.
 */
CivilRegistry::CivilRegistry() {
    ifstream infile("input.txt");
    bool firstLine = true;
    string idNo, name, surname, hasApp, appDate, appSlot, entryClock, True("TRUE");

    while(infile >> idNo >> name >> surname >> hasApp >> appDate >> appSlot >> entryClock){
        if(firstLine){
            firstLine = false;
            continue;
        }

        vector<string> t1 = explode(appDate, '-'), t2 = explode(entryClock, '.');
        auto *t = new Time(stoi(t1[0]), stoi(t1[1]), stoi(t1[2]), stoi(t2[0]), stoi(t2[1]));

        auto *citizen = new Citizen(idNo.c_str(), name.c_str(), surname.c_str(),
                        (strcmp(hasApp.c_str(), True.c_str()) == 0 ? appSlot.c_str() : nullptr),
                        strcmp(hasApp.c_str(), True.c_str()) == 0, t);
        this->insertCitizen(citizen);
    }
    this->wApp.sort();
    this->wOutApp.sort();
}

void CivilRegistry::insertCitizen(Citizen *citizen) {
    if(citizen->getHasApp())
        this->wApp.push_back(*citizen);
    else
        this->wOutApp.push_back(*citizen);
}

/*
 * Print the sorted citizens.
 */
void CivilRegistry::getAllCitizens() {
    list <Citizen>::iterator it;
    std::cout << "Citizens with an appointment:" << std::endl;
    for(it=this->wApp.begin(); it!=this->wApp.end(); it++, removeCitizen(1)){
        std::cout << it->getName();
        std::cout << std::endl;
    }

    std::cout << std::endl << "Citizens without an appointment:" << std::endl;
    for(it=this->wOutApp.begin(); it!=this->wOutApp.end(); it++, removeCitizen(0)){
        std::cout << it->getName() << std::endl;
    }

}

void CivilRegistry::removeCitizen(int a) {
    if(a==1){
        Citizen *citizen = &this->wApp.front();
        this->wApp.pop_front();
        // delete citizen;
    }else{
        Citizen *citizen = &this->wOutApp.front();
        this->wOutApp.pop_front();
        // delete citizen;
    }
}
