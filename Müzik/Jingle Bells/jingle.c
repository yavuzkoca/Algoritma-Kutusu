#include <stdio.h>
#include <windows.h>
#define mi 330
void part1(){
	/*
		Mi mi mi mi mi mi,mi sol do re mi,fa fa fa,mi mi mi,re do re mi re sol...
		Mi mi mi mi mi mi
	*/
	Beep(mi,300);
	Beep(330,300);
	Beep(330,700);
	Beep(330,300);
	Beep(330,300);
	Beep(330,700);
	
	Beep(330,300);
	Beep(392,300);
	Beep(262,600);
	Beep(294,200);
	Beep(330,700);
}
void part2(){


	Beep(349,300);
	Beep(349,300);
	Beep(349,500);
	
	Beep(330,290);
	Beep(330,260);
	Beep(330,500);
	
	Beep(294,300);
	Beep(262,300);
	Beep(294,300);
	Beep(330,300);
	Beep(294,500);
	Beep(392,700);
}


int main(){
	part1();
	part2();
}
