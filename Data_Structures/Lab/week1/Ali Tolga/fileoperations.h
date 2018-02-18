#pragma once

#ifndef DOSYAISLEMLERI_H
#define DOSYAISLEMLERI_H
#include <cstdio>
#include "Record.h"
struct Dosya {
	char *dosyaadi;
	FILE *teldefteri;
	void olustur();
	void kapat();
	void ekle(Tel_Kayit *);
	int ara(char[]);
	void sil(int kayitno);
	void guncelle(int kayitno, Tel_Kayit *);
};
#endif