/* HEADER : GENERICARRAY CLASS HEADER
 * AUTHOR : Muhammed YILMAZ
 * DATE   : 14.05.2018
 * E-MAIL : yilmazmu15@itu.edu.tr
 */

#ifndef GENERICARRAY_H
#define GENERICARRAY_H

#include <string>

template <class T>
class GenericArray {
    int maxSize;
    std::string myType;
    std::string myBonusType;
public:
    T *elements;
    T total;
    explicit GenericArray(int inMaxSize);
    ~GenericArray();
    T sum();
};

#endif //GENERİCARRAY_H