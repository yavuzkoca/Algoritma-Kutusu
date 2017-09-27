#ifndef DIZIISLEMLERI_H
#define DIZIISLEMLERI_H

#include <stdio.h>
#include <string>
#include "kayit.h"

#define MAXKAYIT 100

struct Dizi{
    char *dosyaadi;
    FILE *teldefteri;
    Tel_Kayit k[MAXKAYIT];
    void olustur();
    void kapat();
    void ekle(Tel_Kayit *);
    int ara(char []);
    void sil(int kayitno);
    void guncelle(int kayitno, Tel_Kayit *);
    void listele();
    int kayitsayisi;
};



#endif //C_C_DİZİİSLEMLERİ_H
