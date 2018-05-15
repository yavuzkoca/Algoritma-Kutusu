/*
 * Muhammed YILMAZ
 * 150150149
 * 23.04.2018
 */

#include "Grayling1.h"

void Grayling1::print() {
    if(isMutant)
        std::cout << mutatedToForm;
    else
        std::cout << "Grayling 1";
    std::cout << " -> Age: " << age << " Nname: " << name
              << " G: " << gender << " MPI: " << mpi << " MP: " << mp
              << " Mutate at: " << mutateAt << std::endl;
}

Grayling1::Grayling1(char inGender, std::string inName) :
        Grayling(inGender, std::move(inName)), ageOfDied(5) {
    mpi = 30;
    mutateAt = 60;
}

Grayling1::Grayling1(const Grayling1 &obj, char inGender, std::string inName)
        :Grayling(obj, inGender, std::move(inName)), ageOfDied(5) {
    mpi = 30;
    mutateAt = 60;
}

Grayling1::~Grayling1() = default;

void Grayling1::aging() {

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

void Grayling1::killOrNot() {

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

bool Grayling1::mutatedTo() {

    if(!isAlive)
        return false;

    if(mp >= mutateAt){
        mp = 0;
        isMutant = true;
        if(mpi == 30)
            mutatedToForm = "Grayling2";
        else if(mpi == 40)
            mutatedToForm = "Grayling3";
        std::cout << "Mutated to: " << mutatedToForm << std::endl;
        mpi += 10;
        mutateAt += 20;
        ageOfDied--;
        killOrNot();
        return true;
    }

    return false;
}

int Grayling1::givebirth() {

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
    if(mpi == 30) {
        std::cout << name << " gave birth to 2 offsprings!" << std::endl;
        return 2;
    }
    else if(mpi == 40) {
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

void Grayling1::kill_him() {

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
