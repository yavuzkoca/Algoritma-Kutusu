#include <typeinfo>
#include <iostream>
#include "GenericArray.cpp"
#include "Money.h"

int main() {

    GenericArray<Money> m1(7);
    GenericArray<int> m2(7);
    GenericArray<double> m3(7);
    Money a (100, 7);
    Money b (10, 8);
    Money c (-3, 5);
    m1.push(a, 0);
    m1.push(b, 1);
    m1.push(c, 2);
    m2.push(10, 0);
    m2.push(5,1);
    m2.push(7,2);
    m3.push(100.8, 0);
    m3.push(12.4, 9);

    m1.total = m1.sum();
    m2.total = m2.sum();
    m3.total = m3.sum();


    return 0;
}