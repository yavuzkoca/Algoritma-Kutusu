/*
 * Muhammed YILMAZ
 * 150150149
 * 23.04.2018
 */

#include "Grayling2.h"

Grayling2::Grayling2(char inGender, std::string inName) :
        Grayling(inGender, std::move(inName)), ageOfDied(4) {
    mpi = 40;
    mutateAt = 80;
}

Grayling2::Grayling2(const Grayling2 &obj, char inGender, std::string inName)
        :Grayling(obj, inGender, std::move(inName)), ageOfDied(4){
    mpi = 40;
    mutateAt = 80;
}

void Grayling2::print() {
    if(isMutant)
        std::cout << mutatedToForm;
    else
        std::cout << "Grayling 2";
    std::cout << " -> Age: " << age << " Nname: " << name
              << " G: " << gender << " MPI: " << mpi << " MP: " << mp
              << " Mutate at: " << mutateAt << std::endl;
}

Grayling2::~Grayling2() = default;

void Grayling2::aging() {

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
    mutatedTo();

}

void Grayling2::killOrNot() {

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

bool Grayling2::mutatedTo() {

    if(!isAlive)
        return false;

    if(mp >= mutateAt){
        mp = 0;
        isMutant = true;
        mutatedToForm = "Grayling3";
        std::cout << "Mutated to: " << mutatedToForm << std::endl;
        mpi = 50;
        mutateAt += 20;
        ageOfDied--;
        killOrNot();
        return true;
    }

    return false;
}

int Grayling2::givebirth() {

    if(!isAlive || gender == 'm'){
        std::cout << "Trying GIVE BIRTH BUT " << name << " can not give "
                  << "birth because of it is";
        if(!isAlive)
            std::cout << " not alive and";
        if(gender=='m')
            std::cout << " male and";
        std::cout << " Grayling3 has no ability" << std::endl;
    }
    else{
        std::cout << "Trying GIVE BIRTH BUT " << name << " (Grayling3) has no"
                  << " ability to give birth! " << std::endl;
    }

    if(isAlive){
        kill_him();
        std::cout << name << " is dead because of trying to give birth."
                  << std::endl;
    }
    // Control alive or not
    if(!isAlive){

        std::cout << "Trying GIVE BIRTH BUT " << name << " is not alive";
        if(mpi == 50)
            std::cout << " and No ability to give birth!";
        std::cout << std::endl;
        return 0;
    }

    // Control gender
    if(gender == 'm'){
        std::cout << "Trying GIVE BIRTH BUT " << name << " can not give"
                  << " birth because of gender being male";
        if(mpi == 50)
            std::cout << " and No ability to give birth!";
        std::cout << std::endl;
        return 0;
    }

    // Control number of offsprings
    if(mpi == 40) {
        std::cout << name << " gave birth to 1 offsprings!" << std::endl;
        return 1;
    }
    else {
        std::cout << "Trying GIVE BIRTH BUT " << name << " has no ability"
                  << " to give birth! " << std::endl;
        kill_him();
        std::cout << name << " is dead because of trying to give birth."
                  << std::endl;

        return 0;
    }
}

void Grayling2::kill_him() {

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