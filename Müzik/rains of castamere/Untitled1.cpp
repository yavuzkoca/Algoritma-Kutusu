#include <windows.h>
#include <stdio.h>
#define do 262
#define re 294
#define mi 330
#define fa 349
#define sol 392
#define la 440
#define si 494
void part1(){
	Beep(sol,400);
	Beep(fa,700);
	Beep(sol,350);
	Beep(mi,600);
	Beep(la,350);
	Beep(fa,600);
	Beep(fa,650);
	Beep(mi,800);
	Beep(re,400);
	Beep(la,600);
	Beep(sol,600);
	Beep(fa,600);
	Beep(mi,600);
	Beep(re,1000);
}

void part2(){
	Beep(sol,400);
	Beep(sol,700);
	Beep(la,400);
	Beep(fa,700);
	Beep(do,400);
	Beep(sol,400);
//	Beep(1,50);
	Beep(sol,500);
	Beep(la,500);
	Beep(fa,900);
	Beep(sol,500);
	Beep(la,550);
	Beep(sol,650);
	Beep(mi,700);
	Beep(re,1000);
}
int main(){
	part1();
	Beep(1,1000);
	part2();
	return 0;
}
