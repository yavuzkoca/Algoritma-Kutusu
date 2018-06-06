
 // driver code for stack implementation
#include "stack.hpp"

#include <iostream>
#include <string> 

using namespace std;

int main()
{
    stack<string> s;
    s.push("123");
    s.push("321");
    s.push("999");

    while(!s.isEmpty()){
        auto res = s.top();
        s.pop();
        cout << res << endl;
    }
    return 0; 
}
