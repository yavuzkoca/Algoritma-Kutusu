#include "Grayling.h"
#include <utility> // std::move

Grayling::Grayling(char gender, std::string name)
        : _gender(gender), _name(std::move(name)), _MPI(30), _age(0), _alive(true), _mutant(false) {
}

Grayling::Grayling() : _gender('')
{
    this->_alive = false;
}
