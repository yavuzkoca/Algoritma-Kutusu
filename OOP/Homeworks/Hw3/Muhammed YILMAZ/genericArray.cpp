/* HEADER : GENERICARRAY CLASS FUNCTIONS
 * AUTHOR : Muhammed YILMAZ
 * DATE   : 14.05.2018
 * E-MAIL : yilmazmu15@itu.edu.tr
 */

#include <iostream>
#include "genericArray.h"
#include "Money.h"

template <class T>
GenericArray<T>::GenericArray(int inMaxSize):maxSize(inMaxSize), total(0) {

    // Creating array that have maxSize element
    elements = new T[maxSize]();

    // This if else condition provide myType and myBonusType by variable type
    if (std::is_same<T, int>::value) {
        this->myType = "int";
        this->myBonusType = "points";
    }
    else if (std::is_same<T, double>::value) {
        this->myType = "double";
        this->myBonusType = "points";
    }
    else if (std::is_same<T, float>::value) {
        this->myType = "float";
        this->myBonusType = "points";
    }
    else if (std::is_same<T, Money>::value) {
        this->myType = "money";
        this->myBonusType = "tl";
    }
}

template <class T>
GenericArray<T>::~GenericArray(){
    delete [] elements;
}
template <class T>
T GenericArray<T>::sum() {

    // Total is 0
    total = T(0);

    // Adding all elements' value to total.
    for (int i = 0; i < maxSize; ++i) {
        total += elements[i];
    }

    // The total amount is being printed
    std::cout << "The total amount of "<< myType << " array is " << total
              << std::endl;

    // Bonus adding, losing, or not changing according to total value
    if(total > T(100)){
        total += T(5);
        std::cout << "You have won 5 " << myBonusType << " bonus, new total is "
                  << total << std::endl << std::endl;

    }
    else if(total < T(100)){
        total -= T(5);
        std::cout << "You have lose 5 " << myBonusType << ", new total is "
                  << total << std::endl << std::endl;
    }
    else{
        std::cout << "Total is not change" << std::endl << std::endl;
    }

    // Function return total value
    return total;
}