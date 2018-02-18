#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"
using namespace std;

int lex_cmp(const char *word1, const char *word2){
	if (int(*(word1)) > int(*(word2))){
		return 1;
	}
	else if (int(*(word1)) == int(*(word2))){
		char *temp_word1 = (char *)malloc(sizeof(char)* 80);
		char *temp_word2 = (char *)malloc(sizeof(char)* 80);
		for (int i = 0; *(word1 + i + 1) != '\0'; ++i)
			temp_word1[i] = *(word1 + i + 1);
		for (int i = 0; *(word2 + i + 1) != '\0'; ++i)
			temp_word2[i] = *(word2 + i + 1);
		return lex_cmp(temp_word1, temp_word2);
	}
	else{
		return 0;
	}
}

void Dizi::ekle(Tel_Kayit *ykptr){
	int char_index_of_search = 0;
	int buraya_kaydet_index = -1;
	for (int i = 0; i < kayitsayisi; ++i){
		if (lex_cmp((k + i)->ad, ykptr->ad)){
			buraya_kaydet_index = i;
			break;
		}
		else{
			continue;
		}
	}

	if (buraya_kaydet_index != -1){
		for (int i = kayitsayisi - 1; i >= buraya_kaydet_index; --i){
			strcpy((k + i + 1)->ad, (k + i)->ad);
			strcpy((k + i + 1)->telno, (k + i)->telno);
		}
	}
	else{
		strcpy((k + kayitsayisi)->ad, ykptr->ad);
		strcpy((k + kayitsayisi)->telno, ykptr->telno);
	}

	strcpy((k + buraya_kaydet_index)->ad, ykptr->ad);
	strcpy((k + buraya_kaydet_index)->telno, ykptr->telno);
	kayitsayisi++;
}
void Dizi::olustur(){
	kayitsayisi = 0;
	FILE *file_ptr = fopen("kayitlar.txt", "r");
	if (!file_ptr){
		cout << "File couldn't be opened." << endl;
		return;
	}
	while (!feof(file_ptr)){
		char *temp_name = (char *)malloc(sizeof(char) * 80);
		char *temp_num = (char *)malloc(sizeof(char)* 80);
		fscanf(file_ptr, "%s %s", temp_name, temp_num);
		strcpy(k[kayitsayisi].ad, temp_name);
		strcpy(k[kayitsayisi].telno, temp_num);
		kayitsayisi++;
	}
	fclose(file_ptr);
}
int Dizi::ara(char aranacak[]){
	int sayac = 0;
	bool tumu = false;
	int bulunan, flag = 0;
	if (strcmp(aranacak, "*") == 0)
		tumu = true;
	for (int i = 0; i<kayitsayisi; i++){
		if (strcmp(k[i].ad, aranacak) == 0 || tumu)
		{
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

void Dizi::ustuneyaz(){
	FILE *file_ptr = fopen("kayitlar.txt", "w");
	if (!file_ptr){
		cout << "File couldn't be opened." << endl;
		return;
	}
	for (int i = 0; i < kayitsayisi; ++i){
		char *temp_name = (char *)malloc(sizeof(char)* 80);
		char *temp_num = (char *)malloc(sizeof(char)* 80);
		strcpy(temp_name, k[i].ad);
		strcpy(temp_num, k[i].telno);
		if ( strcmp(temp_name, "") == 0 && strcmp(temp_num, "") == 0){
			continue;
		}
		if (i == kayitsayisi - 1)
			fprintf(file_ptr, "%s %s", temp_name, temp_num);
		else
			fprintf(file_ptr, "%s %s\n", temp_name, temp_num);
	}
	fclose(file_ptr);
}