#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#define X 8
#define Y 8
#define HIT 1
#define RED "\033[22;34m"
#define RESET "\033[0m"
int Matrice[Y][X]={0},i,j,x,y,Q = 7,W = 6, i,g=7,h=2,a=1,b=1,c=1,d=2,e=1,z=1,n=8,gg=6,hh=5,dd=8,ee=7,aa=1,bb=1;
void giris(){
	
	system("color a");
	Beep(1568, 250);
    Beep(1568, 250);
    Beep(1568, 250);
    Beep(1245, 1200);
    Beep(1397, 250);
    Beep(1397, 250);
    Beep(1397, 250);
    Beep(1175, 1200);
    printf("!!!!HOSGELDINIZ!!!!");
    Beep(1,1000);
    system("cls");
    Beep(523,500);  // 523 hertz (C5) for 500 milliseconds
  Beep(587,500);
  Beep(659,500);
  Beep(698,500);
  Beep(784,500);
  Beep(884,500);
  Beep(984,1500);
    printf("YAVUZ PRODUKSIYON GURURLA SUNAR!!!!");
    Beep(1,1700);
    system("cls");
    printf("KARSINIZDA AMIRAL BATTI OYUNU!!");
    Beep(1,1700);
    system("cls");
}
void koordinatlar(){
	
	Matrice[g][h]=1;
	Matrice[g][h+1]=1;
	Matrice[gg][hh]=1;
	Matrice[gg+1][hh]=1;
	Matrice[d][e]=1;
	Matrice[d][e+1]=1;
	Matrice[dd][ee]=1;
	Matrice[dd][ee+1]=1;
	Matrice[z][n]=1;
	Matrice[z+1][n]=1;
	Matrice[z+2][n]=1;
	Matrice[x][y]=5;
	//printf("%d,%d,%d",Matrice[x][y],x,y);
}

void taslak(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes;
	//system("cls");
	printf("    ");
	for(i=0;i<Y;i++){
		printf("%4d",i+1);
	}
	putchar('\n');
	putchar('\n');
	for(i=1;i<=Y;i++){
		printf("%3d: ",i);
		for(j=1;j<=X;j++){
			if(Matrice[x][y]==HIT)
				Matrice[x][y] = 5;
			if(Matrice[i][j]==5){
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				printf("  O ");
				SetConsoleTextAttribute(hConsole, originalAttrs);}
			else if(Matrice[i][j]==1)
			printf("    ");
			else if(Matrice[i][j]==2){
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				printf("  X ");
				SetConsoleTextAttribute(hConsole, originalAttrs);}
			else 
				printf("    ");
			
		}
		putchar('\n');
		putchar('\n');
	}
	
}
void taslak3(){
	printf("    ");
	for(i=0;i<Y;i++){
		printf("%4d",i+1);
	}
	putchar('\n');
	putchar('\n');
	for(i=1;i<Y+1;i++){
		printf("%3d: ",i);
		for(j=1;j<X+1;j++){
			Matrice[x][y] = 0;
			//printf("%3d ",Matrice[i][j]);
		}
		putchar('\n');
		putchar('\n');
	}
	
}
void taslak_reset(){
	//printf("    ");
	//for(i=0;i<Y;i++){
//		printf("%4d",i+1);
//	}
//	putchar('\n');
	for(i=0;i<Y;i++){
//		printf("%3d: ",i+1);
		for(j=0;j<X;j++){
			Matrice[i+1][j+1] = 0;
		}
//		putchar('\n');
	}
	
}
int Gemi(){
	int gemi;
	gemi = Matrice[g][h]+Matrice[g][h+1]+Matrice[gg+1][hh]+Matrice[gg][hh];
	return gemi;
	
}
int DenizAlti(){
	int denizalti;
	denizalti =  Matrice[d][e]+Matrice[d][e+1]+Matrice[dd][ee]+Matrice[dd][ee+1];
	return denizalti;
	
}
int Amiral(){
	int amiral;
	amiral =  Matrice[z+1][n]+Matrice[z+2][n]+Matrice[z+3][n];
	return amiral;
}
int Sonuc(){
	int topla=0;
	for(i=0;i<Y;i++)
		for(j=0;j<X;j++){
			topla += Matrice[i][j];}
	return topla;
}
void part3(){
	Beep(749, 300);
	Beep(659, 300);
	Beep(749, 300);
	Beep(800, 300);
	Beep(749, 300);
	Beep(659, 300);
	Beep(600, 500);
	Beep(550, 300);
	Beep(659, 300);
	Beep(600, 300);
	Beep(550, 300);
	Beep(600, 600);
}
void part4(){
	Beep(749, 500);
	Beep(659, 300);
	Beep(749, 300);
	Beep(800, 300);
	Beep(749, 300);
	Beep(659, 300);
	Beep(600, 500);
	Beep(550, 300);
	Beep(659, 300);
	Beep(600, 300);
	Beep(550, 300);
	Beep(500, 600);
}
int main(){
	giris();
	//	koordinatlar();
	//sifirla(8,8);
	printf("Iste Dusman Kuvvetleri:\n");
	//taslak_reset();
	//koordinatlar();
	taslak3();
	//printf("%d",Matrice[1][1]);
	koordinatlar();
	printf("Hedefi vurmak icin once satir sonra sutun numarasini soyleyiniz:\n");
	Gemi();
	DenizAlti();
	Amiral();
	while(Sonuc() != 0){
		scanf("%d%d",&x,&y);
		
		system("cls");
		if(x < 1 || x > 8 || y < 1 || y > 8 )
			printf("Lutfen Duzgun bir deger giriniz! -_-\n");
		else{
			printf("Soylediginiz komut: %d.satir ve %d. sutun ",x,y);
			if(Matrice[x][y]==HIT){
				Beep(75,1000);
				Matrice[x][y] = 5;
				//printf("%d",Amiral());
				if(Amiral()==10 && DenizAlti()==20 && Gemi()==20){
					printf("Hepsini Vurdunuz! Tebrikler.. :)  :) \n");
					part3();
					part4();
					break;
				}else
				if(Gemi()==12 && a > 0){
					printf("Gemiyi batirdiniz :) !!\n");
					a--;
				}
				else if(Gemi()==20 && aa > 0){
					printf("Gemileri batirdiniz :) !!\n");
					aa--;
				}
				else if(DenizAlti()==12 && b > 0){
					printf("Deniz Altini Batirdiniz :) !!\n ");
					b--;
				}
				else if(DenizAlti()==20 && bb > 0){
					printf("Deniz Altilarini Batirdiniz :) !!\n ");
					bb--;
				}
				else if(Amiral()==10 && c > 0){
					printf("Amiral'i Batirdiniz :D !!\n");
					c--;
				}
				else{
					
					printf("Guzel! Vurdunuz..:)\n");
					}
				
				Beep(500,200);
				}
				else{
					Matrice[x][y] = 2;
					Beep(75,1000);
					printf("Karavana..:/\n");
					Beep(300,500);
					
				}
				//taslak_reset();
				Beep(1,600);
				taslak();
				Beep(1000,200);
				//koordinatlar();
				
		}			
	}
	system("PAUSE");
	return 0;	
}
