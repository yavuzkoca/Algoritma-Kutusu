#include <stdio.h>
#include <windows.h>
#define do 262
#define re 294
#define mi 330
#define fa 349
#define sol 392
#define la 440
#define si 494

void part1(){
	Beep(do,400);
	Beep(re,500);
	Beep(mi,800);
	Beep(sol,500);
	Beep(mi,600);
	Beep(re,500);
	Beep(mi,500);
	Beep(re,500);
	Beep(do,700);
}
void part2(){
	
	Beep(mi,500);
	Beep(sol,500);
	Beep(la,800);
	Beep(do,500);
	Beep(si,800);
	Beep(sol,500);
	Beep(mi,600);
	Beep(fa,450);
	Beep(re,700);
}

int main(){
	part1();
	part2();
	part1();
	part2();
	
	return 0;
}
