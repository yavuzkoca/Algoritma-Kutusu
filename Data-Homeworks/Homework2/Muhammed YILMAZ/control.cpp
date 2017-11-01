#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "control.h"
using namespace std;

/* Tercihler dosyasından türkçe karakterleri kontrol eder. */
bool contTurkish(){

	/*********** Dosyadan tercihler okunur. - Start ***********/
	char *prefName = new char[50];
	char *prefPref = new char[10];
	FILE *dgPrefR;
	if ((dgPrefR = fopen("preferences","r")) == NULL)
	{
		cout << "Err05: \"preferences\" okunamadı for insertAll." << endl;
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 4; ++i)
	{
		fscanf(dgPrefR, "%s %s", prefName, prefPref);
	} 
	fclose(dgPrefR);
	/*********** Dosyadan tercihler okunur. - Bitiş ***********/

	if((strcmp(prefPref, "off")) == 0)
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_FAILURE;
	}
	else if ((strcmp(prefPref, "on")) == 0)
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_SUCCESS;
	}
	else
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_FAILURE;
	}
}

/* Tercihler dosyasından kontrol eder. */
bool contTwoName(){

	/*********** Dosyadan tercihler okunur. - Start ***********/
	char *prefName = new char[50];
	char *prefPref = new char[10];
	FILE *dgPrefR;
	if ((dgPrefR = fopen("preferences","r")) == NULL)
	{
		cout << "Err05: \"preferences\" okunamadı for insertAll." << endl;
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 3; ++i)
	{
		fscanf(dgPrefR, "%s %s", prefName, prefPref);
	} 
	fclose(dgPrefR);
	/*********** Dosyadan tercihler okunur. - Bitiş ***********/

	if((strcmp(prefPref, "off")) == 0)
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_FAILURE;
	}
	else if ((strcmp(prefPref, "on")) == 0)
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_SUCCESS;
	}
	else
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_FAILURE;
	}
}

bool contClearSc(){

	/*********** Dosyadan tercihler okunur. - Start ***********/
	char *prefName = new char[50];
	char *prefPref = new char[10];
	FILE *dgPrefR;
	if ((dgPrefR = fopen("preferences","r")) == NULL)
	{
		cout << "Err05: \"preferences\" okunamadı for continuePress." << endl;
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 2; ++i)
	{
		fscanf(dgPrefR, "%s %s", prefName, prefPref);
	}

	fclose(dgPrefR);
	/*********** Dosyadan tercihler okunur. - Bitiş ***********/

	if((strcmp(prefPref, "off")) == 0)
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_FAILURE;
	}
	else if ((strcmp(prefPref, "on")) == 0)
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_SUCCESS;
	}
	else
	{
		delete [] prefPref;
		delete [] prefName;
		return EXIT_FAILURE;
	}
}