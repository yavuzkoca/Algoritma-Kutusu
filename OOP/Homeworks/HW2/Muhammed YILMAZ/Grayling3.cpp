/*
 * Muhammed YILMAZ
 * 150150149
 * 23.04.2018
 */

#include "Grayling3.h"

void Grayling3::print() {
    std::cout << "Grayling 3 -> Age: " << age << " Nname: " << name
              << " G: " << gender << " MPI: " << mpi << " MP: " << mp
              << " Mutate at: " << mutateAt << std::endl;
}

Grayling3::Grayling3(char inGender, std::string inName) :
        Grayling(inGender, std::move(inName)), ageOfDied(3) {
    mpi = 50;
    mutateAt = 100;
}

Grayling3::Grayling3(const Grayling3 &obj, char inGender, std::string inName)
        :Grayling(obj, inGender, std::move(inName)), ageOfDied(3) {
    mpi = 50;
    mutateAt = 100;
}

Grayling3::~Grayling3() = default;

void Grayling3::aging() {

    // General control alive or not
    if(!isAlive){
        std::cout << "Trying to AGING BUT " << name << " is not alive"
                  << std::endl;
        return;
    }

    // General aging
    age++;
    mp += mpi;

    // General print information to screen
    if(!isMutant)
        std::cout << "AGING: name: " << name << " -> Age: " << age
                  << " MPI: " << mpi << " MP: " << mp << std::endl;
    else
        std::cout << "AGING: name: " << name << " -> " << mutatedToForm
                  << " Age: " << age << " MPI: " << mpi << " MP: " << mp
                  << std::endl;

    // dead or not
    if(mp >= 100){
        //dead
        kill_him();
    }

    // Control kill or not
    killOrNot();

    // Control mutate or not
    // cannot mutate

}

void Grayling3::killOrNot() {

    // Control of dead because of AGE
    if(age >= ageOfDied){
        kill_him();
        std::cout << name << " is dead because of AGING!" << std::endl;
    }

    // Control of dead because of MUTATION
    if(mp>=100) {
        kill_him();
        std::cout << name << " is dead because of HIGH MUTATION RATE!"
                  << std::endl;
    }
}

int Grayling3::givebirth() {

    if(!isAlive || gender == 'm'){
        std::cout << "Trying GIVE BIRTH BUT " << name << " can not give "
                  << "birth because";
        if(!isAlive)
            std::cout << " it is not alive and";
        /*
        if(gender=='m')
            std::cout << " male and";
            */
        std::cout << " Grayling3 has no ability" << std::endl;
    }
    else{
        std::cout << "Trying GIVE BIRTH BUT " << name << " (Grayling3) has no"
                  << " ability to give birth! " << std::endl;

        if(isAlive){
            kill_him();
            std::cout << name << " is dead because of trying to give birth."
                      << std::endl;
        }
    }
    return 0;
}

void Grayling3::kill_him() {

    if(isAlive){
        isAlive = false;
        /*
        std::cout << "This fish dead -> " << "Name: " << name << " Gender: "
             << gender << " Age: " << age << " IsAlive: " << isAlive
             << " IsMutant: " << isMutant << " MutatedToForm: "
             << mutatedToForm << " Mpi: " << mpi << " Mp: " << mp
             << " MutateAt: " << mutateAt << std::endl;
             */

    }
}