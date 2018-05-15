#include "Grayling2.h"
#include <utility>

#define END std::cout << std::endl;

Grayling2::Grayling2(char gender, std::string name) : Grayling(gender, move(name))
{
    this->_MPI = 40;
    this->_MP = 0;
    this->_dying_age = 4;
    this->_mutate_at = 80;
}

Grayling2::Grayling2(const Grayling2 &g2, char gender, std::string name) : Grayling(gender, std::move(name))
{
    this->_MPI = g2._MPI;
    this->_MP = g2._MP;
    this->_dying_age = g2._dying_age;
    this->_mutate_at = g2._mutate_at;
    this->_age = g2._age;
    this->_alive = g2._alive;
    this->_mutant = g2._mutant;
}

void Grayling2::print() const
{
    std::cout << "Grayling 2 -> Age: " << this->_age
              << " Name: " << this->_name << " G:"
              << this->_gender << " MPI: " << this->_MPI
              << " MP " << this->_MP << " Mutate at: "
              << this->_mutate_at << std::endl;
}

void Grayling2::aging()
{

    /*
     * If fish is not alive, do not age it.
     */
    if(!this->_alive){
        std::cout << "Trying to AGING BUT " << this->_name << " is not alive"; END
        return;
    }


    /*
     * Fish can age, increment the age variable and MP.
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
     * If the fish hasn't mutate yet and MP is greater than 80, it means the fish going to
     * mutate to Grayling3 kind. Therefore, MP, MPI, mutated_name and dying_age variables
     * will change with respect ot mutation
     */
    if(!this->_mutant && this->_MP >= this->_mutate_at){
        this->_mutant = true;
        this->_mutated_name = "Grayling3";
        this->_MP = 0;
        this->_MPI = 50;
        this->_dying_age = 3;
        this->_mutate_at = 100;
        std::cout << "Mutated TO: " << this->_mutated_name; END
    }
}

void Grayling2::givebirth()
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
     * If fish hasn't mutated and alive:
     */
    std::cout << this->_name
              << " gave birth to 1 offsprings!";END
}