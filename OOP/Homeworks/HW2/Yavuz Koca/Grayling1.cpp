#include "Grayling1.h"
#include <utility>

#define END std::cout << std::endl;

Grayling1::Grayling1(char gender, std::string name)
        : Grayling(gender, std::move(name))
{
    this->_MPI = 30;
    this->_dying_age = 5;
    this->_mutate_at = 60;
    this->_MP = 0;
}

Grayling1::Grayling1(const Grayling1 &g1, char gender, std::string name)
        : Grayling(gender, std::move(name))
{
    this->_MPI = g1._MPI;
    this->_MP = g1._MP;
    this->_dying_age = g1._dying_age;
    this->_mutate_at = g1._mutate_at;
    this->_age = g1._age;
    this->_alive = g1._alive;
    this->_mutant = g1._mutant;
}

void Grayling1::print() const
{
    std::cout << "Grayling 1 -> Age: " << this->_age
              << " Name: " << this->_name << " G:"
              << this->_gender << " MPI: " << this->_MPI
              << " MP " << this->_MP << " Mutate at: "
              << this->_mutate_at; END
}

void Grayling1::aging()
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
    if(this->_MP >= 100){
        this->_alive = false;
        std::cout << this->_name << " is dead because of HIGH MUTATION RATE!"; END
        return;
    }


    /*
     * If the fish hasn't mutate yet and MP is greater than 60, it means the fish going to
     * mutate to Grayling2 kind. Therefore, MP, MPI, mutated_name and dying_age variables
     * will change with respect ot mutation
     */
    if(!this->_mutant && this->_MP >= this->_mutate_at){
        this->_mutant = true;
        this->_mutated_name = "Grayling2";
        this->_MP = 0;
        this->_MPI = 40;
        this->_dying_age = 4;
        this->_mutate_at = 80;
        std::cout << "Mutated TO: " << this->_mutated_name; END
    }


    /*
     * If the fish already mutated to Grayling2 from Grayling1 and MP is greater than 80,
     * then this fish going to mutate to Grayling3 from Grayling2.
     * Therefore, MP, MPI, mutated_name and dying age variables will change with respect to
     * mutation.
     */
    if(this->_mutant && this->_MP >= this->_mutate_at){
        this->_mutated_name = "Grayling3";
        this->_MP = 0;
        this->_MPI = 50;
        this->_dying_age = 3;
        this->_mutate_at = 100;
        std::cout << "Mutated TO: " << this->_mutated_name; END
    }
}

void Grayling1::givebirth()
{

    /*
     * If fish is not alive and (not female or Grayling3 kind), then:
     */
    if(!this->_alive && (this->_gender != 'f' || this->_mutate_at == 100)){
        std::cout << "Trying to GIVE BIRTH BUT "
                  << this->_name << " is not alive and No ability to give birth!";END
        return;
    }

    /*
     * If fish is not alive
     */
    if(!this->_alive){
        std::cout << "Trying to GIVE BIRTH BUT "
                  << this->_name << " is not alive";END
        return;
    }

    /*
     * If fish is male or G3 type, then:
     */
    if(this->_gender != 'f' || this->_mutate_at == 100){
        std::cout << "Trying to GIVE BIRTH BUT "
                  << this->_name << " has No ability to give birth!";END
        return;
    }

    /*
     * If fish has mutated once
     */
    if(this->_mutate_at == 80){
        std::cout << this->_name
                  << " gave birth to 1 offsprings!";END
        return;
    }

    /*
     * If fish hasn't mutated and alive:
     */
    std::cout << this->_name
              << " gave birth to 2 offsprings!";END
}
