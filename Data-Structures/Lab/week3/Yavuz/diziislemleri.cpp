#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"

using namespace std;

void Dizi::ekle(Tel_Kayit *ykptr){
	strcpy(k[kayitsayisi].ad, ykptr->ad);
	strcpy(k[kayitsayisi].telno, ykptr->telno);
	kayitsayisi++;
}

void Dizi::olustur(){
	dosyaadi = "teldefteri.txt";
	teldefteri = fopen(dosyaadi, "r+");
	if (!teldefteri) {
		if (!(teldefteri = fopen(dosyaadi, "w+"))) {
			cerr << "File can not be opened" << endl;
			exit(1);
		}
	}
	Tel_Kayit l;
	kayitsayisi = 0;
	while (!feof(teldefteri)) {
		//fread(&l, sizeof(Tel_Kayit), 1, teldefteri);
		fscanf(teldefteri,"%s %s", &n, &num);
		//cout << n << num << endl;
		strcpy(k[kayitsayisi].ad, n);
		strcpy(k[kayitsayisi].telno, num);
		kayitsayisi++;
		//cout << k[kayitsayisi].ad;
		if (feof(teldefteri)) break;
	}
	kayitsayisi -= 1;
}

int Dizi::ara(char aranacak[]){
	int sayac = 0;
	bool tumu = false;
	int bulunan, flag = 0;
	if (strcmp(aranacak, "*") == 0)
		tumu = true;
	//cout << kayitsayisi;
	for (int i = 0; i<kayitsayisi; i++){
		if (!tumu && strncmp(k[i].ad, aranacak, strlen(aranacak)) != 0)
			continue;
		cout << i + 1 << ". " << k[i].ad << endl;
		bulunan = i;
		flag = 1;
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
		cout << i + 1 << ". " << (k + i)->ad << " \t" << (k + i)->telno << endl;
}

void Dizi::kapat() {
	sortData();
	writeToFile();
	fclose(teldefteri);
}

void Dizi::sortData(){
	for (int i = 0; i < kayitsayisi; i++){
		for (int j = i+1; j < kayitsayisi; j++){
			if (strcmp((k + i)->ad, (k + j)->ad) > 0){
				strcpy(temp, (k + i)->ad);
				strcpy((k + i)->ad, (k + j)->ad);
				strcpy((k + j)->ad, temp);
				
				strcpy(temp, (k + i)->telno);
				strcpy((k + i)->telno, (k + j)->telno);
				strcpy((k + j)->telno, temp);
			}
		}
	}
}
void Dizi::writeToFile(){
	fclose(teldefteri);
	dosyaadi = "teldefteri.txt";
	teldefteri = fopen(dosyaadi, "w");
	fseek(teldefteri, 0, SEEK_SET);
	for (int i = 0; i < kayitsayisi; i++)
		if (strcmp((k+i)->ad, "") != 0)
			fprintf(teldefteri, "%s %s\n", (k + i)->ad, (k + i)->telno);
		
	
}