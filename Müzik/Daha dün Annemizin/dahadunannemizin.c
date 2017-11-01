#include <windows.h>
#include <stdio.h>
void part1(){
Beep(540, 500);
Beep(540, 500);
Beep(749, 500);
Beep(749, 500);  
Beep(840, 500);
Beep(849, 500);
Beep(729, 700);  
Beep(1,   300);
Beep(700, 500);
Beep(700, 500);
Beep(659, 500);
Beep(659, 500);
Beep(603, 500);
Beep(603, 500);
Beep(500, 800);
Beep(1,   300);
}
void part2(){
Beep(700, 500);
Beep(700, 500);
Beep(659, 500);
Beep(659, 500);
Beep(603, 500);
Beep(603, 500);
Beep(500, 800);
Beep(1,300);
}
int main()
{
part1();
part1();
part2();
part2();
part1();

    return 0;
}
