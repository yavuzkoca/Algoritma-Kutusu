/*
 * Muhammed YILMAZ
 * 150150149
 * 23.04.2018
 */

#include "Grayling.h"

Grayling::~Grayling() = default;

void Grayling::print() {
    cout << "This fish is " << name << endl;
}

void Grayling::aging() {

    //Control alive or not
    if(!isAlive){
        std::cout << "Trying to AGING BUT " << name << " is not alive"
                  << std::endl;
        return;
    }

    // Aging
    age++;
    mp += mpi;

    // Print information to screen
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
    //killOrNot();  // Tür içlerinde

    // Control mutate or not
    //mutatedTo();  // Tür içlerinde
}

int Grayling::givebirth() {

    if(!isAlive){
        std::cout << "Trying GIVE BIRTH BUT " << name << " is not alive";
        if(mpi == 50)
            std::cout << " and No ability to give birth!";
        std::cout << std::endl;
        return 0;
    }

    if(gender == 'm'){
        std::cout << "Trying GIVE BIRTH BUT " << name << " can not give"
                  << " birth because of gender being male" << std::endl;
        return 0;
    }

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

/*
bool Grayling::mutatedTo() {

    if(!isAlive)
        return false;

    if(mp >= 2*mpi){
        mp = 0;
        isMutant = true;
        if(mpi == 30)
            mutatedToForm = "Grayling2";
        else if(mpi == 40)
            mutatedToForm = "Grayling3";
        std::cout << "Mutated to: " << mutatedToForm << std::endl;
        mpi += 10;
        return true;
    }

    return false;
}

void Grayling::killOrNot() {

    // Control of dead because of AGE
    if(mpi == 30 && age >= 5){          //Grayling1 dies at 5.
        kill_him();
        std::cout << name << " is dead because of AGING!" << std::endl;
    }
    else if(mpi == 40 && age >= 4){     //Grayling2 dies at 4.
        kill_him();
        std::cout << name << " is dead because of AGING!" << std::endl;
    }
    else if(mpi == 50 && age >= 3){     //Grayling3 dies at 3.
        kill_him();
        std::cout << name << " is dead because of AGING!" << std::endl;
    }

    // Control of dead because of MUTATION
    if(mp>=100) {
        kill_him();
        std::cout << name << " is dead because of HIGH MUTATION RATE!"
                  << std::endl;
    }

    // Control of dead because of TRYING GIVE BIRTH


}

Grayling::Grayling() : isAlive(false) {
    cout << "This fish was born dead." << endl;
}
*/
void Grayling::kill_him() {

    if(isAlive){
        isAlive = false;
        /*
        cout << "This fish dead -> " << "Name: " << name << " Gender: "
             << gender << " Age: " << age << " IsAlive: " << isAlive
             << " IsMutant: " << isMutant << " MutatedToForm: "
             << mutatedToForm << " Mpi: " << mpi << " Mp: " << mp
             << " MutateAt: " << mutateAt << endl;
             */

    }
}
