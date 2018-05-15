#ifndef YAVUZ_KOCA_GENERIC_ARRAY_H
#define YAVUZ_KOCA_GENERIC_ARRAY_H

#include <iostream>

template<class T>
class GenericArray
{
    const int size;
    T* elements;
    void checkBonusOrPenaltySituation();
public:
    T total;
    explicit GenericArray(int);
    void push(T, int);
    void print() const;
    T sum();
    ~GenericArray();
};

#endif
