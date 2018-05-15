#include "Grayling3.h"
#include <utility>

#define END std::cout << std::endl;

Grayling3::Grayling3(char gender, std::string name) : Grayling(gender, move(name)), _dying_age(3)
{
    this->_MPI = 50;
    this->_MP = 0;
    this->_mutate_at = 100;
}

Grayling3::Grayling3(const Grayling3 &g3, char gender, std::string name)
        : Grayling(gender, std::move(name)), _dying_age(g3._dying_age)
{
    this->_MPI = g3._MPI;
    this->_MP = g3._MP;
    this->_mutate_at = g3._mutate_at;
    this->_age = g3._age;
    this->_alive = g3._alive;
    this->_mutant = g3._mutant;
}

void Grayling3::print() const
{
    std::cout << "Grayling 3 -> Age: " << this->_age
              << " Name: " << this->_name << " G:"
              << this->_gender << " MPI: " << this->_MPI
              << " MP " << this->_MP << " Mutate at: "
              << this->_mutate_at << std::endl;
}

void Grayling3::aging()
{

    /*
     * If fish is not alive, do not age it.
     */
    if(!this->_alive){
        std::cout << "Trying to AGING BUT " << this->_name << " is not alive"; END
        return;
    }


    /*
     * Fish can age, increment the age variable.
     */
    this->_age++;
    this->_MP += this->_MPI;
    std::cout << "AGING: name: " << this->_name << " -> "
              << (this->_mutant ? this->_mutated_name :"")
              << " Age: " << this->_age << " MPI: "
              << this->_MPI << " MP: " << this->_MP; END


    /*
     * If fish is at the dying_age, kill it.
     */
    if(this->_age == this->_dying_age){
        this->_alive = false;
        std::cout << this->_name << " is dead because of AGING"; END
        return;
    }

    /*
    * If fish's MP is greater than 100, kill it.
    */
    if(this->_MP >= this->_mutate_at){
        this->_alive = false;
        std::cout << this->_name << " is dead because of HIGH MUTATION RATE!"; END
        return;
    }

}

void Grayling3::givebirth()
{

    /*
     * If fish is not alive, then:
     */
    if(!this->_alive){
        std::cout << "Trying to GIVE BIRTH BUT "
                  << this->_name << " is not alive and No ability to give birth!";END
        return;
    }

    std::cout << "Trying to GIVE BIRTH BUT "
              << this->_name << " has No ability to give birth!";END
}
