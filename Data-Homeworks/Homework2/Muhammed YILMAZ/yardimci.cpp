#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "yardimci.h"
using namespace std;



/* string'i kucuk harflere cevirir. */
void kucukHarfCevir(char string[]){

	for (int i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] >= 'A' && string[i] <= 'Z') 
		{
			string[i] = string[i] + 32;
		}
	}
}


/* Türkçe-İngilizce için string'in bütün karakterlerini
 * küçük harfe döndürür. 
 * Programda kullanılmadı.
 */
void turKucukHarfCevir(char string[]){

	for (int i = 0; string[i] != '\0'; ++i)
	{
		if(string[i] == 'I')
		{
			/* küçük 'ı'ya dönüştürmek için stringin bir sonraki yere 
			 * boş eleman ekleyip oraya yazması gerekiyor. Fakat bana
			 * bu işlemde hata ihtimali çok yüksek geldi. Bu program
			 * içinde gerekmiyordu. Ben de o yüzden uğraşmadım
			 */
		}
		/* İngilizce yani ascii'de olan bir karakter ise 
		 * 32 eklererek küçük harfe dönüştürür.
		 */
		else if (string[i] >= 'A' && string[i] <= 'Z') 
		{
			string[i] = string[i] + 32;
		}
		/* Türkçeye has bir karakter ise ardışık iki karakter
		 * kontrol edilir. Küçük harfe çevrilir.
		 */
		else if(string[i] == -59)
		{
			if(string[i+1] == -98 )			// Ş
			{
				string[i+1] += 1;
			}
		}
		else if(string[i] == -60)
		{
			if(string[i+1] == -98 )			// Ğ
			{
				string[i+1] += 1;
			}
			else if(string[i+1] == -80 )	// İ
			{
				string[i] = 'i';
				string[i+1] = 0;
			}
		}
		else if(string[i] == -61)
		{
			if(string[i+1] == -100 )		// Ü
			{
				string[i+1] += 32;
			}
			else if(string[i+1] == -106 )	// Ö
			{
				string[i+1] += 32;
			}
			else if(string[i+1] == -121 )	// Ç
			{
				string[i+1] += 32;
			}
		}
	}

	/* Küçük harfe çevirirken İ->i dönüşümü olduysa
	 * bir char "0"a eşitlenmiştir. Bu elemandan itibaren
	 * birer kaydırılır.
	 */
	charDelete(string, 0);
}

/* mail için stringi ingiliz alfabesindeki küçük harflere çevirir. */
void mailKucukHarfCevir(char string[]){

	for (int i = 0; string[i] != '\0'; ++i)
	{
		/* İngilizce yani ascii'de olan bir karakter ise 
		 * 32 eklererek küçük harfe dönüştürür.
		 */
		if (string[i] >= 'A' && string[i] <= 'Z') 
		{
			string[i] = string[i] + 32;
		}
		/* Türkçeye has bir karakter ise ardışık iki karakter
		 * kontrol edilir. Küçük harfe çevrilir.
		 */
		else if(string[i] == -59)
		{
			if(string[i+1] == -98 || string[i+1] == -97 )			// Ş ve ş
			{
				string[i] = 's';
				string[i+1] = '.';
			}
		}
		else if(string[i] == -60)
		{
			if(string[i+1] == -98 || string[i+1] == -97)			// Ğ ve ğ
			{
				string[i] = 'g';
				string[i+1] = '.';
			}
			else if(string[i+1] == -80 )	// İ
			{
				string[i] = 'i';
				string[i+1] = '.';
			}
			else if(string[i+1] == -79 )	// ı
			{
				string[i] = 'i';
				string[i+1] = '.';
			}
		}
		else if(string[i] == -61)
		{
			if(string[i+1] == -100 || string[i+1] == -68)		// Ü ve ü
			{
				string[i] = 'u';
				string[i+1] = '.';
			}
			else if(string[i+1] == -106 || string[i+1] == -74)	// Ö ve ö
			{
				string[i] = 'o';
				string[i+1] = '.';
			}
			else if(string[i+1] == -121 || string[i+1] == -89)	// Ç ve ç
			{
				string[i] = 'c';
				string[i+1] = '.';
			}
		}
	}
	/* Küçük harfe çevirirken İ->i dönüşümü olduysa
	 * bir char "0"a eşitlenmiştir. Bu elemandan itibaren
	 * birer kaydırılır.
	 */
	charDelete(string, '.');
}

/* Türkçe-İngilizce bütün karakterler için alfabetik sıralamaya göre
 * 0-32 arası bir integer döndürür. Eğer bir karakterin alfatik sıralamada
 * yeri yoksa 0 döndürür.
 */
int myValueChar(const char ch1, const char ch2){

	switch (ch1)
	{
		case 97:	case 65:	//a ve A
		return 1;
		case 98:	case 66:	//b ve B
		return 2;
		case 99:	case 67:	//c ve C
		return 3;
		case 100:	case 68:	//d ve D
		return 5;
		case 101:	case 69:	//e ve E
		return 6;
		case 102:	case 70:	//f ve F
		return 7;
		case 103:	case 71:	//g ve G
		return 8;
		case 104:	case 72:	//h ve H
		return 10;
					case 73:	//     I
		return 11;
		case 105:				//i
		return 12;
		case 106:	case 74:	//j ve J
		return 13;
		case 107:	case 75:	//k ve K
		return 14;
		case 108:	case 76:	//l ve L
		return 15;
		case 109:	case 77:	//m ve M
		return 16;
		case 110:	case 78:	//n ve N
		return 17;
		case 111:	case 79:	//o ve O
		return 18;
		case 112:	case 80:	//p ve P
		return 20;
		case 113:	case 81:	//q ve Q
		return 21;
		case 114:	case 82:	//r ve R
		return 22;
		case 115:	case 83:	//s ve S
		return 23;
		case 116:	case 84:	//t ve T
		return 25;
		case 117:	case 85:	//u ve U
		return 26;
		case 118:	case 86:	//v ve V
		return 28;
		case 119:	case 87:	//w ve W
		return 29;
		case 120:	case 88:	//x ve X
		return 30;
		case 121:	case 89:	//y ve Y
		return 31;
		case 122:	case 90:	//z ve Z
		return 32;
		
		case -61:
			switch (ch2)
			{
				case -89:	case -121:	//ç ve Ç
				return 4;
				case -74:	case -106:	//ö ve Ö
				return 19;
				case -68:	case -100:	//ü ve Ü
				return 27;
			}
		case -60:
			switch (ch2)
			{
				case -97:	case -98:	//ğ ve Ğ
				return 9;
				case -79:				//ı
				return 11;
							case -80:	//     İ
				return 12;
			}
		case -59:
			switch (ch2)
			{
				case -97:	case -98:	//ş ve Ş
				return 24;
			}

		default:
		return 0;

	}
}

/* Buyuk, kucuk harf duyarliligi kaldirildi. Siralamada artik önemli degil */
int strCcmp (const char *str1, const char *str2 ){
	
		char *strC1, *strC2;
		strC1 = new char[50];
		strC2 = new char[50];

		strcpy(strC1, str1);
		strcpy(strC2, str2);

		kucukHarfCevir(strC1);
		kucukHarfCevir(strC2);

		int result = strcmp(strC1, strC2);

		delete [] strC1;
		delete [] strC2;

		return result;
}

/* Türkçe karakter hassasiyetli sıralama fonksiyonu. */
int strTcmp ( const char * str1, const char * str2 ){

	/* Kısa olanın uzunluğuna kadar tek tek kontrol eder,
	 * eğer değerler farklı içe farkı "result"a yazar,
	 */
	int i = 0, j=0, result = 0;
	for (; str1[i] != '\0' && str2[j] != '\0' && result == 0; ++i, j++)
	{
		if(isdigit(str1[i]) && isdigit(str2[j])) {
			
			result = str1[i] - str2[j];
		} else if (isdigit(str1[i]) && !isdigit(str2[j])) {

			result = -200;
		} else if (!isdigit(str1[i]) && isdigit(str2[j])) {

			result = 200;
		} else{
			int x1 = myValueChar(str1[i], str1[i+1]);
			if(str1[i] < 0)	i++;
			int x2 = myValueChar(str2[j], str2[j+1]);
			if(str2[j] < 0)	j++;

			if(x1 == x2)
			{
				result = 0;
			}
			else
			{
				result = x1 - x2;
			}
		}

		
	}

	/* Eğer sonuna kadar değerler aynı fakat uzunlukları farklı ise
	 * uzun olana göre "100" ve ya "-100" döndürür.
	 */
	if(result == 0 &&  str1[i] != '\0')
	{	
		result = 100;
	}
	else if(result == 0 && str2[j] != '\0')
	{
		result = -100;
	}

	return result;
}

/* Kullanıcıya özel tercihleri ayarlama.
 * Program başladığında otomatik sorulur.
 */
bool setPreferences(){

	int numberPref = 0;
	int edit;

	/*********** Dosyadan tercihler okunur. - Start ***********/
	FILE *dgPrefR;
	if ((dgPrefR = fopen("preferences","r")) == NULL)
	{
		cout << "Err05: \"preferences\" okunamadı." << endl;
		return EXIT_FAILURE;
	}

	stPref *arPref = new stPref[10];

	for (numberPref = 0; !feof(dgPrefR); ++numberPref)
	{
		arPref[numberPref].prefName = new char[50];
		arPref[numberPref].prefPref = new char[10];
		fscanf(dgPrefR, "%s %s", 
			arPref[numberPref].prefName, arPref[numberPref].prefPref);
	} 
	fclose(dgPrefR);
	/*********** Dosyadan tercihler okunur. - Bitiş ***********/

	/***************Tercihleri yazdırma - Start ***************/
	for (int i = 0; i < numberPref; ++i)
	{
		if(i==0)
		{
			cout << endl << "\tPREFERENCES" << endl;
			continue;
		}	
		
		cout << i << " - " << arPref[i].prefName << " -> " << arPref[i].prefPref
			 << endl;
	}

	cout << endl << "Değiştirmek istediğiniz ayarın numarasını giriniz "
		 << "(yoksa '0'): ";
	cin >> edit;
	if(edit == 0 || edit >= numberPref)
	{
		for (int i = 0; i < numberPref; ++i)
		{
			delete [] arPref[i].prefName;
			delete [] arPref[i].prefPref;
		}
		delete [] arPref;
		return EXIT_SUCCESS;
	}
	/***************Tercihleri yazdırma - Bitiş ***************/

	/****************Tercih değiştirme - Start ****************/
	while (!(edit == 0 || edit >= numberPref))
	{
		cout << edit << "- " << arPref[edit].prefName << "->"
			 << arPref[edit].prefPref << endl;
		cout << "Enter the new value (on/off): ";
		cin >> arPref[edit].prefPref;
		cout << endl << "Değiştirmek istediğiniz diğer ayarın "
			 << "numarasını giriniz (yoksa '0'): ";
		cin >> edit;
	}
	/****************Tercih değiştirme - Bitiş ****************/

	/********* Dosyaya yeni ayarlar yazılıyor - Start *********/
	FILE *dgPrefW;
	if ((dgPrefW = fopen("preferences","w")) == NULL)
	{
		cout << "Err06: \"preferences\" oluşturulamadı." << endl;
		for (int i = 0; i < numberPref; ++i)
		{
			delete [] arPref[i].prefName;
			delete [] arPref[i].prefPref;
		}
		delete [] arPref;
		return EXIT_FAILURE;
	}
	
	for (int i = 0; i < numberPref; ++i)
	{
		fprintf(dgPrefW, "\n%s\t%s", arPref[i].prefName, arPref[i].prefPref);
		delete [] arPref[i].prefName;
		delete [] arPref[i].prefPref;
	}
	delete [] arPref;

	fclose(dgPrefW);
	/********* Dosyaya yeni ayarlar yazılıyor - Bitiş *********/

	return EXIT_SUCCESS;
}

/* Menuyu yazdirir. */
void printMenu(){

	cout << endl << endl
		 << "e-mail Address Program:" << endl
		 << "1) Create" << endl
		 << "2) Insert All" << endl
		 << "3) Insert New Record" << endl
		 << "4) Delete Student" << endl
		 << "5) Delete Surname Node" << endl
		 << "6) Update" << endl
		 << "7) Write to File" << endl
		 << "8) Set preferences" << endl
		 << "9) Print \"insertList\" and\n\t \"fullMails with Surname\"" << endl
		 << "0) Exit" << endl
		 << endl
		 << "Enter a choice: ";
}

bool createPreferences(){

	FILE *dgPrefW;
	if ((dgPrefW = fopen("preferences","r")) == NULL)
	{
		cout << "There is not file of preferences. It is created." << endl;
		if ((dgPrefW = fopen("preferences","w")) == NULL)
		{
			cout << "Err05: \"preferences\" olusturulamadi." << endl;
			return EXIT_FAILURE;
		}
	}
	else 
	{
		return EXIT_FAILURE;
	}


	fprintf(dgPrefW, "\nPREFERENCES\tON");
	fprintf(dgPrefW, "\nclear_after_operations\toff");
	fprintf(dgPrefW, "\nstudent_has_two_name\toff");
	fprintf(dgPrefW, "\nturkish_characters\toff");

	fclose(dgPrefW);
}

/* str'deki ch'leri siler. */
void charDelete (char *str, char ch){

	for (unsigned int i = 0, j=0; j < strlen(str);)
		{
			if(i>=strlen(str))
			{
				str[j++] = '\0';
				continue;
			}
			if (str[i] != ch )
			{
				str[j++] = str[i++];
			}
			else
			{
				i++;
				str[j++] = str[i++];
			}
		}
}