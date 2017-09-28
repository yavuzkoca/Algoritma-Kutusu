#ifndef DIZIISLEMLERI_H
#define DIZIISLEMLERI_H

#include <stdio.h>
#include <string>
#include "kayit.h"

#define MAXKAYIT 100

struct Dizi{
	char *dosyaadi;
	char temp[30];
	char n[30];
	char num[30];
	FILE *teldefteri;
	Tel_Kayit k[MAXKAYIT];
	void olustur();
	void kapat();
	void ekle(Tel_Kayit *);
	int ara(char[]);
	void sil(int kayitno);
	void guncelle(int kayitno, Tel_Kayit *);
	void listele();
	void sortData();
	int kayitsayisi;
	void Dizi::writeToFile();
};



#endif //C_C_DÝZÝÝSLEMLERÝ_H
