#include <iostream>

using namespace std;

int main(){
    char** doubleString = new char*[100];
    for(int i = 0; i < 100; ++i)
        doubleString[i] = new char[30];

    return 0;
}