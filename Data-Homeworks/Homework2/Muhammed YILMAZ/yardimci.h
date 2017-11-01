#ifndef YARDIMCI_H
#define YARDIMCI_H

void kucukHarfCevir(char string[]);
void turKucukHarfCevir(char string[]);
void mailKucukHarfCevir(char string[]);
int myValueChar(const char ch1, const char ch2);
int strCcmp (const char *str1, const char *str2);
int strTcmp (const char *str1, const char *str2);
bool setPreferences();
void printMenu();
bool createPreferences();
void charDelete (char *str, char ch);

struct stPref
{
	char *prefName;
	char *prefPref;
};

#endif