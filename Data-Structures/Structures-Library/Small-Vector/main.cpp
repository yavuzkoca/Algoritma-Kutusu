#include <cstdio>
#include "SmallVector.h"

int main(){
    int temp[35];
    for (int i = 0; i < 35; i++)
        temp[i] = i;
    SmallVector test(temp, 10);
    SmallVector test2(temp, 35);
    test.reverse().print();
    SmallVector test3;
    test3 = test2 + test;
    test3.print();
    SmallVector test4(test);
    SmallVector test5(temp, 2);
    test5 = test5 * 5;
    test5.print();
    test5.push_back(12);
    test5[0] = 4;
    test5.reverse().print();
    SmallVector test6;
    test6 = test5 = test4;
    test6.print();
    test5.print();
    SmallVector test7(temp, 35);
    test7.print();
    test7 = test7 + test6;
    test3.print();
    test7.print();
    test3 = test7 = test5 = test7 = test5;
    test3.print();
    test7.print();
    return 0;
}