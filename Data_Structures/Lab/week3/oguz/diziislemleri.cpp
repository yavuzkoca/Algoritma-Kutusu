#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"

using namespace std;
void Dizi::ekle(Tel_Kayit *ykptr){
	
	Tel_Kayit *ptr;
	ptr = &k[0];
	int place = 0;

	for (int i = 0; i < kayitsayisi; i++){
		if (strcmp(ykptr->ad, ptr->ad)>0){
			place = i+1;
		}
		ptr++;
	}

	for (int i = kayitsayisi; i > place; i--){
		strcpy(ptr->ad, (ptr - 1)->ad);
		strcpy(ptr->telno, (ptr - 1)->telno);
		ptr--;
	}

	strcpy(ptr->ad, ykptr->ad);
	strcpy(ptr->telno, ykptr->telno);
	kayitsayisi++;
}

void Dizi::olustur(){
	kayitsayisi = 0;
}

int Dizi::ara(char aranacak[]){
	int sayac = 0;
	bool tumu = false;
	int bulunan, flag = 0;
	if (strcmp(aranacak, "*") == 0) {
		tumu = true;
		listele();
		return tumu;
	}
	for (int i = 0; i<kayitsayisi; i++) {
		if (strcmp(k[i].ad, aranacak) == 0) {
			cout << i + 1 << ". " << k[i].ad << endl;
			bulunan = i;
			flag = 1;
		}
	}
	return flag;
}

void Dizi::guncelle(int kayitno, Tel_Kayit *ykptr){
	strcpy(k[kayitno - 1].ad, ykptr->ad);
	strcpy(k[kayitno - 1].telno, ykptr->telno);
}

void Dizi::sil(int kayitno){
	Tel_Kayit temp;
	strcpy(temp.ad, "");
	strcpy(temp.telno, "");
	int indisno;
	indisno = kayitno - 1;
	k[indisno] = temp;
}

void Dizi::listele(){
	for (int i = 0; i<kayitsayisi; i++)
		cout << i + 1 << ". " << k[i].ad << " \t" << k[i].telno << endl;
}

void Dizi::yazdir(){
	FILE *output;
	output = fopen("input.txt", "w+");
	for (int i = 0; i < kayitsayisi; i++)
		if (strlen(k[i].ad)!=0)
		fprintf(output, "%s %s\n", k[i].ad, k[i].telno);
	fclose(output);
}
