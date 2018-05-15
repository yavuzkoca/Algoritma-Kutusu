#include "GenericArray.h"
#define END std::cout << std::endl;

/*
 * Take memory for given 'size' for the 'elements' array.
 * set 'total' attribute to zero. Since all objects in the 'elements' array may not be used,
 * I set all objects to zero at first to prevent getting garbage values.
 */
template <class T>
GenericArray<T>::GenericArray(int size) : size(size){
    elements = new T[size];
    for(auto i=0; i<size; i++) elements[i] = 0;
    this->total = 0;
}


/*
 * Free the memory that has been taken in the constructor
 */
template <class T>
GenericArray<T>::~GenericArray() {
    delete [] this->elements;
}


/*
 * This function takes two arguments, first one is the object itself that will be added to
 * 'elements' array, second one is the index number to put which index of the 'elements' array.
 */
template <class T>
void GenericArray<T>::push(T object, int index) {
    try{
        if(index < 0 || index >= this->size) throw "Unreachable index";
        if( object < 0 ) {
            throw "Negative money can not add to array!";
        }
        this->elements[index] = object;
    }catch(const char* msg){
        std::cout << msg; END
    }
}


/*
 * I wrote this function to read all objects in the 'elements' array
 */
template <class T>
void GenericArray<T>::print() const {
    for(int i=0; i<this->size; i++)
        std::cout << this->elements[i] << " ";
    END
}


/*
 * This function adds all objects in the 'elements' array and writes the result to 'total' attribute.
 */
template <class T>
T GenericArray<T>::sum() {

    this->total = 0;

    for(int i=0; i<this->size; i++)
        this->total += this->elements[i];

    std::cout << "Your total amount is: " << this->total; END

    /*
     * Bonus or penalty points
     */
    this->checkBonusOrPenaltySituation();

    return this->total;
}


/*
 * If total is more than 100, give 5 more
 * Else, take 5.
 */
template <class T>
void GenericArray<T>::checkBonusOrPenaltySituation() {
    if(this->total > 100){
        this->total += 5;
        std::cout << "Your have won 5 more, your new account is " << this->total; END
    }else if(this->total < 100){
        this->total -= 5;
        std::cout << "You have lost 5 unit, your new account is " << this->total; END
    }
}
