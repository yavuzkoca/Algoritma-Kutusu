/* @Author
* Student Name: Muhammed YILMAZ
* Student ID : 150150149
* Date: 24.10.2017
*/

/*				AÇIKLAMALAR
 * Eğer tercihlerde 2 isimli öğrenciler açık ise;
 *  isim-soyisim ayrımı '\t' ile yapılmıştır. Boşluklar 
 *  iki isim arasında kabul edilmiştir. Bu yüzden isim
 *  soyisim arası boşluk var ise soyisim yok sanar ve
 *  soyisimde olması gerekeni de isimlere kaydeder.
 * 
 */
#include <iostream>
#include "list.h"
#include "yardimci.h"
#include "control.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

using namespace std;

/*************************GLOBAL*************************/
	insertList *headInsert, *tailInsert;
	surnameMap *headSurname, *tailSurname;
	studentInfo *headFullMails;
	
	const int NAMEL = 20*4;
	const int SURNAMEL = 20;
	const int FILENAMEL = 40;
	const int MAILL = NAMEL + SURNAMEL + 15;

	bool contBTurkish;
	bool contBTwoName;
	bool contBClearSc;

	/* numberRecord ogrenci sayisi degil, id olusturmak icin
	 * kullanilan bir degiskendir.
	 */
	int numberRecord;
/*************************FINISH*************************/

/*************************FUNC_H*************************/
	bool doOperation(char op);
	bool insertAll(char *fileName);
		bool insertAll1(char *fileName);
		bool insertAll2(char *filename);
	void insertNewRecord();	//
	insertList *insertPerson(char *name, char *surname);
	bool createList();
	char *addSurname(insertList *newSurnameTemp);
	bool listInsert();
	bool listSurname();
	bool createMail(insertList *newMailStudent);
	bool createMailAll();
	bool writeFile(FILE *fileName);
	void trashAll();
	bool clearInsertList();
	void deleteStudent(studentInfo *trashStudent);
	studentInfo *findStudentInfo(char *mail);
	surnameMap *findSurnameMapFromMail(char *mail);
	surnameMap *findSurnameMapPrevFromSurname(char *surname);
	void deleteSurnameNext(surnameMap *trashSurnamePrev);
	void updateStudent(studentInfo *updateStudentX);	//
	void continuePress();
	int strXcmp (const char *str1, const char *str2);
	void createBoolControls();
	bool addToFullMails(studentInfo *tempAddInfo);
	bool clearFullMails();
/*************************FINISH*************************/

int main(int argc, char *argv[]){
	
	//setlocale(LC_ALL, "");
	//setlocale(LC_ALL, "C");
	setlocale(LC_ALL, "tr_TR.UTF-8");
	//setlocale(LC_ALL, "Turkish");


	cout << "TÜRKÇE ğçıöüş ÖÇİŞĞÜ" << endl;
	
	createPreferences();
	setPreferences();
	createBoolControls();
		continuePress();
	
	numberRecord = 0;
	bool exit = 0;
	char operation;
	while(!exit)
	{
		printMenu();
		cin >> operation;
		exit = doOperation(operation);
		continuePress();
	}

	trashAll();
	continuePress();
	
	return EXIT_SUCCESS;
}

/*************************FUNC_H*************************/

/* Bütün maillerin bulunduğu liste oluşturulur. */
bool createFullMails(){

	if(headFullMails != NULL)
	{
		clearFullMails();
	}
	headFullMails = NULL;
	
	surnameMap *iterSurname = headSurname;
	studentInfo * iterStudentInfo;

	do
	{
		iterStudentInfo = iterSurname->mailHead;
		while(iterStudentInfo !=NULL)
		{
			addToFullMails(iterStudentInfo);
			iterStudentInfo = iterStudentInfo->next;
		}
		iterSurname = iterSurname->next;
	}while(iterSurname != headSurname);
}

/* fullMails listesini serbest bırakır. */
bool clearFullMails(){

	if(headFullMails == NULL)
	{
		cout << "War03: FullMails list is already empty." << endl;
		return EXIT_FAILURE;
	}

	studentInfo *iterFullMails = headFullMails;
	studentInfo *trash;

	do
	{
		trash = iterFullMails; 
		iterFullMails = iterFullMails->next;
		delete [] trash->name;
		delete [] trash->surname;
		delete [] trash->mail;
		delete trash;	
	} while(iterFullMails != NULL);

	headFullMails = NULL;
	cout << "FullMails list was cleared." << endl;
	return EXIT_SUCCESS;
}

/* tempAddInfo'daki bilgileri tüm maillerin olduğu listeye ekler. */
bool addToFullMails(studentInfo *tempAddInfo){
			
	/* Öğrenci bilgileri alınır. */
	studentInfo *addInfoToFull = new studentInfo;
	addInfoToFull->name = new char[NAMEL];
	addInfoToFull->surname = new char[SURNAMEL];
	addInfoToFull->mail = new char[MAILL];

	strcpy(addInfoToFull->name, tempAddInfo->name);
	strcpy(addInfoToFull->surname, tempAddInfo->surname);
	strcpy(addInfoToFull->mail, tempAddInfo->mail);
	addInfoToFull->id = tempAddInfo->id;
	addInfoToFull->next = NULL;
	addInfoToFull->prev = NULL;

	/*Liste boş ise head oluşturulur. */
	if(headFullMails == NULL)
	{
		headFullMails = addInfoToFull;
		addInfoToFull->next = NULL;
		addInfoToFull->prev = NULL;
	}
	/* headFullMails'ten önceye ekleme */
	else if(strcmp(headFullMails->mail, addInfoToFull->mail) > 0)
	{
		addInfoToFull->next = headFullMails;
		addInfoToFull->prev = NULL;
		headFullMails->prev = addInfoToFull;
		headFullMails = addInfoToFull;
	}
	else
	{
		studentInfo *iterFullMails = headFullMails;
		studentInfo *yakalaFullMails = iterFullMails;
		while(iterFullMails != NULL)
		{	

			/* iterFullMails'ten önceye (ortaya) ekleme */
			if(strcmp(iterFullMails->mail, addInfoToFull->mail) > 0)
			{
				addInfoToFull->next = iterFullMails;
				addInfoToFull->prev = iterFullMails->prev;
				iterFullMails->prev->next = addInfoToFull;
				iterFullMails->prev = addInfoToFull;
				break;
			}

			yakalaFullMails = iterFullMails;
			iterFullMails = iterFullMails->next;
		}
		/* sona ekle*/
		if(iterFullMails == NULL)
		{
			addInfoToFull->next = NULL;
			yakalaFullMails->next = addInfoToFull;
			addInfoToFull->prev = yakalaFullMails;
		}
	}
}

/* Preferences ayarları için sonuçları hafızada tutar. */
void createBoolControls(){

	contBTurkish = contTurkish();
	contBTwoName = contTwoName();
	contBClearSc = contClearSc();
}

/* Türkçe karakter kontrolüne göre işlem yapar. */
int strXcmp (const char *str1, const char *str2){

	if(contBTurkish == EXIT_FAILURE)
	{
		return strCcmp(str1,str2);
	}
	else
	{
		return strTcmp(str1,str2);
	}
}

/* İslem sonrsai devam icin ve kullanicinin istegine gore ekran
 * ciktilari durumu icin
 */
void continuePress(){

	if(contBClearSc == EXIT_SUCCESS)
	{
		cout << endl << endl << "Press \"Enter\" to continue...";
		getchar();	getchar();

		#ifdef _WIN32
		system("cls");
		#else
		system("clear");
		#endif
	}
}

/* Ogrenci ismi ve soyismi guncellemesi */
void updateStudent(studentInfo *updateStudentX){

	char *name = new char[NAMEL], *surname = new char[SURNAMEL];

	cout << endl;
	cout << "Old name of student is \"" << updateStudentX->name << "\"" << endl;
	cout << "If you want update name, enter new name "
		 << "(if don't want, press 'X/x'): ";
	if(contBTwoName == EXIT_FAILURE)
	{
		cin >> name;
	}
	else
	{
		getchar();
		fgets(name, sizeof(char)*(NAMEL+SURNAMEL), stdin);
		/* Sondaki satır sonunu siler. */
		for (int i = 0; name[i] != '\0'; ++i)
		{
			if(name[i] == '\r')
			{
				name[i] = '\0';
			}
			else if(name[i] == '\n')
			{
				name[i] = '\0';
			}
		}
	}
	cout << endl;

	if((name[0] == 'X' || name[0] == 'x') && name[1] =='\0')
	{
		strcpy(name, updateStudentX->name);
	}

	cout << "Old surname of student is \"" << updateStudentX->surname
		 << "\"" << endl;
	cout << "If you want update surname, enter new surname "
		 << "(if don't want, press 'X/x'): ";
	cin >> surname;
	
	
	cout << endl;
	if((surname[0] == 'X' || surname[0] == 'x') && surname[1] =='\0')
	{
		strcpy(surname, updateStudentX->surname);
	}

	/* Eski ogrenci bilgileri silinir. */
	deleteStudent(updateStudentX);

	/* Yeni ogrenci bilgileri eklenir.*/
	insertPerson(name, surname);
	cout << "Student was added insertList. You should do \"Create\" "
		 << "operation for creating mail." << endl;

	delete [] name;
	delete [] surname;
}

/* Program bitiminde dinamik veriler silinir ki yer kaplamasin. */
void trashAll(){

	clearInsertList();
	clearFullMails();

	if(headSurname == NULL)
	{
		cout << "War02: surnameMap is already empty." << endl;
		return;
	}
	
	surnameMap *trashSurname = tailSurname;
	/* Son elemana kadar dongu. */
	while(tailSurname != NULL)
	{
		trashSurname = tailSurname;
		deleteSurnameNext(trashSurname);		
	}
	cout << "All records were deleted." << endl;
	return; 
}

/* trashSurnamePrev'den sonra gelen soyismi ve altındaki kayitlar silinir. */
void deleteSurnameNext(surnameMap *trashSurnamePrev){

	surnameMap *trashSurname, *trashSurnameNext;
	/* Tek soyisim var, ve bu soyisim silinecekse... */
	if(headSurname == tailSurname)
	{
		trashSurname = trashSurnamePrev;
		headSurname = NULL;
		tailSurname = NULL;
	}
	/* İlk soyisim silinecekse... */
	else if(trashSurnamePrev == tailSurname)
	{
		trashSurname = headSurname;
		trashSurnameNext = headSurname->next;
		trashSurnamePrev = tailSurname;
		headSurname = trashSurnameNext;
	}
	/* Sondaki kayit silinecekse... */
	else if(trashSurnamePrev->next == tailSurname)
	{
		trashSurname = trashSurnamePrev->next;
		trashSurnameNext = trashSurname->next;
		tailSurname = trashSurnamePrev;
	}
	/* Ortadan soyisim silinecekse */
	else
	{
		trashSurname = trashSurnamePrev->next;
		trashSurnameNext = trashSurname->next;
	}
	trashSurnamePrev->next = trashSurnameNext;

	char *tempSurname;
	tempSurname = new char[SURNAMEL];
	strcpy(tempSurname, trashSurname->surname);
	studentInfo *iterStudentInfo = trashSurname->mailHead;
	studentInfo *trashStudent;
	/* Soyisim altindaki kayitlar silinir. */
	while(iterStudentInfo !=NULL)
	{
		trashStudent = iterStudentInfo;
		iterStudentInfo = iterStudentInfo->next;
		delete [] trashStudent->name;
		delete [] trashStudent->surname;
		delete [] trashStudent->mail;
		delete trashStudent;
	}
	delete [] trashSurname->surname;
	delete trashSurname;

	cout << "Records of \"" << tempSurname << "\" was deleted." << endl;
	delete [] tempSurname;
}

/* Girilen soyisimden oncesi surnameMap node'unu dondurur.
 * Oncekini dondurme sebebi silme islemi icin onceki gerekiyor.
 */
surnameMap *findSurnameMapPrevFromSurname(char *surname){

	if(headSurname == NULL)
	{
		cout << "Surname list could not be found. " << endl
			 << "Please do \"Create\" function first." << endl;
		return NULL;
	}
	
	surnameMap *iterSurname = headSurname;
	surnameMap *iterSurnamePrev = tailSurname;
	do
	{
		if(strXcmp(surname, iterSurname->surname) == 0)
		{
			return iterSurnamePrev;
		}
		iterSurnamePrev = iterSurname;
		iterSurname = iterSurname->next;
	}while(iterSurname != headSurname);

	cout << "Surname could not be found." << endl;
	return NULL; 
}

/* Girilen mail sahibi ogrencinin uyesi oldugu surnameMap node'nu dondurur. */
surnameMap *findSurnameMapFromMail(char *mail){
	
	if(headSurname == NULL)
	{
		cout << "Surname list could not be found. " << endl
			 << "Please do \"Create\" function first." << endl;
		return NULL;
	}
	
	surnameMap *iterSurname = headSurname;
	studentInfo * iterStudentInfo;

	do
	{
		iterStudentInfo = iterSurname->mailHead;
		while(iterStudentInfo !=NULL)
		{
			if(strXcmp(mail, iterStudentInfo->mail) == 0)
			{
				return iterSurname;
			}

			iterStudentInfo = iterStudentInfo->next;
		}
		iterSurname = iterSurname->next;
	}while(iterSurname != headSurname);

	cout << "email could not be found." << endl;
	return NULL; 
}

/* Girilen mail adresinin sahibi ogrencinin studentInfo node'unu dondurur. */
studentInfo *findStudentInfo(char *mail){

	if(headSurname == NULL)
	{
		cout << "Surname list could not be found. " << endl
			 << "Please do \"Create\" function first." << endl;
		return NULL;
	}
	
	surnameMap *iterSurname = headSurname;
	studentInfo * iterStudentInfo;

	do
	{
		iterStudentInfo = iterSurname->mailHead;
		while(iterStudentInfo !=NULL)
		{
			if(strTcmp(mail, iterStudentInfo->mail) == 0)
			{
				return iterStudentInfo;
			}

			iterStudentInfo = iterStudentInfo->next;
		}
		iterSurname = iterSurname->next;
	}while(iterSurname != headSurname);
	return NULL;
}

/* Girilen ogrencinin bilgilerini siler. Eger o soyisimde baska kayit
 * kalmadiysa, o soyismini de siler.
 */
void deleteStudent(studentInfo *trashStudent){

	studentInfo *iterTrashPrev = trashStudent->prev;
	studentInfo *iterTrashNext = trashStudent->next;
	char *tempMail;
	tempMail = new char [55];
	strcpy(tempMail, trashStudent->mail);

	surnameMap *trashFromSurname;
	trashFromSurname = findSurnameMapFromMail(trashStudent->mail);
	/* Bastan ogrenci bilgisi silinir. */
	if(trashStudent->prev == NULL)
	{
		if(trashFromSurname == NULL)
		{
			cout << "\"" << tempMail << "@itu.edu.tr\" could not be deleted."
				 << endl;
			cout << "Err04" << endl;
			return;
		}

		trashFromSurname->mailHead = iterTrashNext;
		if(iterTrashNext != NULL)
		{
			iterTrashNext->prev = NULL;
		}
		delete [] trashStudent->name;
		delete [] trashStudent->surname;
		delete [] trashStudent->mail;
		delete trashStudent;
	}
	/* Ortadan ogrenci bilgisi silinir. */
	else if (trashStudent->next != NULL)
	{
		iterTrashPrev->next = iterTrashNext;
		iterTrashNext->prev = iterTrashPrev;
		delete [] trashStudent->name;
		delete [] trashStudent->surname;
		delete [] trashStudent->mail;
		delete trashStudent;
	}
	/* Sondan ogrenci bilgisi silinir. */
	else
	{
		iterTrashPrev->next = NULL;
		delete [] trashStudent->name;
		delete [] trashStudent->surname;
		delete [] trashStudent->mail;
		delete trashStudent;
	}

	cout << "\"" << tempMail << "@itu.edu.tr\" is deleted." << endl;
	delete [] tempMail;

	surnameMap *trashSurnamePrev;
	trashSurnamePrev = findSurnameMapPrevFromSurname(trashFromSurname->surname);
	if(trashFromSurname->mailHead == NULL)
	{
		if(trashSurnamePrev != NULL)
			{
				deleteSurnameNext(trashSurnamePrev);
			}
	}
}

/* insertList'teki butun kayitlari siler. */
bool clearInsertList(){

	if(headInsert == NULL)
	{
		cout << "War01: insertList is already empty." << endl;
		return EXIT_FAILURE;
	}

	insertList *iterInsert = headInsert;
	insertList *trash;

	do
	{
		trash = iterInsert; 
		iterInsert = iterInsert->next;
		delete [] trash->name;
		delete [] trash->surname;
		delete trash;	
	} while(iterInsert != headInsert);

	headInsert = NULL;
	tailInsert = NULL;
	cout << "Insert list was cleared." << endl;
	return EXIT_SUCCESS;
}

/* mail adresleri ve isim-soyisimleri fileName dosyasina yazar. */
bool writeFile(FILE *fileName){

	if(fileName == NULL)
	{
		cout << "File could not be opened." << endl;
		return EXIT_FAILURE;
	}

	if(headSurname == NULL)
	{
		cout << "Surname could not be found. " << endl
			 << "Please do \"Create\" function first." << endl;
		return EXIT_FAILURE;
	}
	createFullMails();

	studentInfo *iterFullMails = headFullMails;

	while(iterFullMails != NULL)
	{
		fprintf(fileName, "%s@itu.edu.tr\t%s\t%s\n", 
				iterFullMails->mail, iterFullMails->name,
				iterFullMails->surname );
		iterFullMails = iterFullMails->next;
	}
	return EXIT_SUCCESS;
}

/* insertList'teki butun ogrencilerin mail adreslerini olusturur */
bool createMailAll(){

	if (headInsert == NULL)
	{
		cout << "List is empty. "
			 << "Please \"Insert All\" or \"Insert New Record\" first." << endl
			 << "If you have inserted previously, the inserted recordings "
			 << "have been deleted." << endl;
		return EXIT_FAILURE;
	}
	
	insertList *iterInsert = headInsert;
	do
	{
		createMail(iterInsert);
		iterInsert = iterInsert->next;
	} while(iterInsert != headInsert);
	clearInsertList();
	return EXIT_SUCCESS;
}

/* gelenInsert'teki ogrencinin mail adresi olusturulur. */
bool createMail(insertList *gelenInsert){

	surnameMap *iterSurname = headSurname;

	/* Öğrencinin soyismi ile havuzdaki soyismi aynı yapana
	 * kadar listeyi döndürür.
	 */
	if(iterSurname->surname != gelenInsert->surname)
	{
		iterSurname = iterSurname->next;
		while(iterSurname != headSurname && 
			strXcmp(iterSurname->surname, gelenInsert->surname) != 0)
		{
			iterSurname = iterSurname->next;
		}

		/* Eğer soyisimler aynı olduğu için döngü bittiyse bir şey yapılmaz,
		 * kontrollerden çıkılır. Öğrenci bilgileri alıcanacak, mail
		 * oluşturulacak, kayıt eklenecek.
		 */
		if(strXcmp(iterSurname->surname, gelenInsert->surname) == 0);

		/* Eğer dairesel bağlı liste olan surnameMap 1 tur döndü ve
		 * ve bu yüzden while döngüsünden çıkıldıysa, soyadı bulunamamış
		 * demektir, soyadının bulunamadığını ekrana yazdırır, fonksiyon
		 * olumsuz olarak sonuçlanır. 
		 */
		else if(iterSurname == headSurname)
		{
			cout << "Err02: Soyadi bulunamadi.\n\tid:" 
				<< gelenInsert->id << endl;
			return EXIT_FAILURE;
		}
		/* Eğer bu iki durum dışında beklenmedik bir şey olmuş ise
		 * hata verir ve fonksiyon olumsuz sonuçlanır, bu kontrol kullanıcı
		 * için değil yazılımcı içindir. 
		 */
		else
		{
			cout << "Err01: \n\tid:" << gelenInsert->id << endl;
			return EXIT_FAILURE;
		}
	}

	/* Öğrenci bilgileri alınır. */
		studentInfo *newStudentInfo = new studentInfo;
		newStudentInfo->name = new char[NAMEL];
		newStudentInfo->surname = new char[SURNAMEL];
		newStudentInfo->mail = new char[MAILL];

		strcpy(newStudentInfo->name, gelenInsert->name);
		strcpy(newStudentInfo->surname, gelenInsert->surname);
		newStudentInfo->id = gelenInsert->id;
		newStudentInfo->next = NULL;
		newStudentInfo->prev = NULL;

	cout << "Mail oluşturuluyor: " << newStudentInfo->name << " " 
		<< newStudentInfo->surname << endl;

	/************ newStudentInfo->mail OLUŞTURMA - BAŞLANGIÇ. ************/

	char *tempName = new char[strlen(newStudentInfo->name)+1],
		 *tempSurname = new char[strlen(newStudentInfo->surname)+1];
	strcpy(tempName, newStudentInfo->name);
	strcpy(tempSurname, newStudentInfo->surname);
	mailKucukHarfCevir(tempName);
	mailKucukHarfCevir(tempSurname);

	/* isim ve soyisimlerin harf sayısı alındı. */
	int x = strlen(tempSurname),
		y = strlen(tempName);

	/* Geçici mail dizileri oluşturulur, eğer içerisinde
	 * bir şey varsa temizlenir.
	 */						
	char *mailTemp = new char[x+y+20], *mailTemp2 = new char[x+y+20];

	for (int i = 0; i < x+y+20; ++i)
	{
		mailTemp[i] = '\0';
		mailTemp2[i] = '\0';
	}

	/* mailTemp2'ye soyisim+isim kopyalanır. */
	sprintf(mailTemp2, "%s%s" ,tempSurname ,tempName);

	delete [] tempSurname;
	delete [] tempName;
	/* Boşluklar silinir -> 2 isimlilerde boşluk var. */
	/* mailTemp2 içerisindeki büyük harfler küçük harfe dönüştürülür. */
	/* tercihlerde türkçe karakter durumuna göre dönüştürme yapılır. */
	if(contBTurkish == EXIT_FAILURE)
	{
		kucukHarfCevir(mailTemp2);
	}
	else
	{
		charDelete(mailTemp2, ' ');
		mailKucukHarfCevir(mailTemp2);
	}
	

	studentInfo *iterStudentInfo = iterSurname->mailHead;
	studentInfo *iterStudentInfoPrev = iterStudentInfo;

	/* Eğer hiç öğrenci bilgisi yoksa, ilk öğrencinin maili oluşturulur. */
	if(iterStudentInfo == NULL)
	{
		for (int i = 0; ; ++i)
		{
			/*mailTemp2'den soyadı uzunluğu kadarı mailTemp'e kopyalanır. */
			strncpy(mailTemp, mailTemp2, sizeof(char)*x+i);
			
			if(findStudentInfo(mailTemp) == NULL)
			{
				break;
			}
		}
	}
	/* Eğer daha önce ayni isim-soyisimdeki(maildeki) öğrenci bilgisi kaydedilmiş ise
	 * yeni öğrenci için mail oluşturulur. 
	 */
	else
	{
		int z = strlen(mailTemp2);
		for (int i = x; iterStudentInfo != NULL; )
		{
			if(mailTemp2[i-1] < 0)
			{
				i++;
			}

			if(i>z)
			{
				/*if(i-z>9)
				{
					cout << "Aynı isim ve soyisimden mailde 9'dan büyük ek "
						 << "numara olacak sekilde giremezsiniz."
						 << endl;
					return EXIT_FAILURE;
				}*/
				sprintf(mailTemp, "%s%d", mailTemp2, i-z);
				if(i-z > 15)	return EXIT_FAILURE;
				
			}
			else
			{	
				strncpy(mailTemp, mailTemp2, sizeof(char)*i);
			}

			if(findStudentInfo(mailTemp) != NULL)
			{
				i++;
				continue;
			}

			if(strcmp(iterStudentInfo->mail, mailTemp) == 0)
			{
				i++;
				continue;
			}
			else if(strcmp(iterStudentInfo->mail, mailTemp) < 0)
			{
				iterStudentInfoPrev = iterStudentInfo;
				iterStudentInfo = iterStudentInfo->next;
				
				continue;
			}
			else if(strcmp(iterStudentInfo->mail, mailTemp) > 0)
			{
				break;
			}
		}
	}



	/* mailTemp, newStudentInfo->mail'e kopyalanır.
	 * newStudentInfo->mail oluşturulmuş olur.
	 */
	strcpy(newStudentInfo->mail, mailTemp);
	//cout << "Mail oluşturuldu. mail: " << newStudentInfo->mail << endl;
	/************** newStudentInfo->mail OLUŞTURMA - BİTİŞ. **************/

	//cout << "Kayıt ekleniyor. Id: " << newStudentInfo->id << endl;

	/************** newStudentInfo KAYIT EKLEME - BAŞLANGIÇ **************/
	/* Eğer hiç öğrenci bilgisi yoksa, ilk öğrencinin kaydı yapılır. */
	if(iterSurname->mailHead == NULL)
	{
		iterSurname->mailHead = newStudentInfo;
	}
	/* Head öncesine ekleme yapilir, ilk mail oluşturma için değil,
	 * sonraki mail oluşturma işlemleri içindir.
	 * Not: Bu kontrol özel bir kontroldür. Sadece (ilk mail oluşturmadan)
	 * sonra "iterSurname->mailHead" konumundaki mail silinir ve
	 * "<surname>@itu.edu.tr" olan ilk mail adresi silinmiş, ondan sonraki
	 * mail yeni "iterSurname->mailHead" olmuş, "Update" ve ya
	 * "Insert New Record" ile bu Surname'e yeni bir kayit geldiyse çalışır.
	 * Bu yüzden bu kontroldeki "iterStudentInfo", "iterStudentInfo->prev",
	 * "newStudentInfo"nun birbirlerine göre olan konumları diğer kontrollerden
	 * farklıdır.
	 * Bu kontrolde -> newStudentInfo, iterStudentInfo öncesine eklenir.
	 * Diğerlerinde -> newStudentInfo, iterStudentInfoPrev sonrasına eklenir.
	 */
	else if(iterStudentInfo != NULL && iterStudentInfo->prev == NULL)
	{
		newStudentInfo->next = iterStudentInfo;
		iterStudentInfo->prev = newStudentInfo;
		iterSurname->mailHead = newStudentInfo;
	}
	/* Eğer son kayıt olarak eklenecek ise, gerekli işlemler yapılır. */
	else if(iterStudentInfo == NULL && iterStudentInfoPrev != NULL)
	{
		newStudentInfo->prev = iterStudentInfoPrev;
		iterStudentInfoPrev->next = newStudentInfo;
	}
	/* Eğer ortaya ekleme yapılacaksa, gerekli işlemler yapılır. */
	else if(iterStudentInfo != NULL && iterStudentInfoPrev != NULL)
	{
		newStudentInfo->next = iterStudentInfo;
		iterStudentInfo->prev = newStudentInfo;
		newStudentInfo->prev = iterStudentInfoPrev;
		iterStudentInfoPrev->next = newStudentInfo;
	}

	cout << "Record was added: " << newStudentInfo->mail
		 << "@itu.edu.tr"<< endl << endl;
	/**************** newStudentInfo KAYIT EKLEME - BİTİŞ ****************/
	delete [] mailTemp;
	delete [] mailTemp2;

	return EXIT_SUCCESS;
}

/* Gelen ogrenci bilgisinden, eger yoksa soyismini ekler.
 * Fonksiyon gelen ogrencinin soyismini dondurur.
 */
char *addSurname(insertList *newSurnameTemp){

	surnameMap *newSurname = new surnameMap;
	newSurname->surname = new char[SURNAMEL];
	strcpy(newSurname->surname, newSurnameTemp->surname);
	newSurname->mailHead = NULL;

	/* İlk kayit alinir, headSurname ve tailSurname oluşturulur */
	if(headSurname==NULL)
	{
		headSurname = newSurname;
		tailSurname = newSurname;
	}
	/* ilk kayit var, sonraki kayitlar eklenir */
	else 
	{	
		surnameMap *iterSurname;
		iterSurname = headSurname;
		/* soyismi ilk sırada var ise ekleme yapmaz. */
		/* gereksiz bir işlem olmuş. sonradan farkettim */
		if(strXcmp(iterSurname->surname, newSurname->surname) == 0)
		{
			return newSurname->surname;
		}
		/* İlk sıraya ekle. */
		if(strXcmp(iterSurname->surname, newSurname->surname) > 0)
		{
			newSurname->next = iterSurname;
			headSurname = newSurname;
		}
		/* Ilk siraya degil de ...'ya ekle. */
		else
		{
			while(iterSurname->next != headSurname)
			{	
				/* Ortaya ekle. */
				if(strXcmp(iterSurname->next->surname, newSurname->surname) > 0)
				{
					newSurname->next = iterSurname->next;
					iterSurname->next = newSurname;
					/* break yerine return olabilirdi, sonradan farkettim. */
					break;
				}
				iterSurname = iterSurname->next;
				/* soyismi var ise ekleme yapmaz. */
				if(strXcmp(iterSurname->surname, newSurname->surname) == 0)
				{
					return newSurname->surname;
				}
			}
			/* Sona ekle */
			if(iterSurname->next == headSurname)								
			{
				iterSurname->next = newSurname;
				tailSurname = newSurname;
			}
		}
	}
	tailSurname->next = headSurname;	
	return newSurname->surname;
}

/* surnameMap dairesel bagli listesi olusturulur. (allSurnameAdd) */
bool createList(){

	if (headInsert == NULL)
	{
		cout << "List is empty. "
			 << "Please \"Insert All\" or \"Insert New Record\" first." << endl
			 << "If you have inserted previously, the inserted recordings "
			 << "have been deleted." << endl;
		return EXIT_FAILURE;
	}
	insertList *iterInsert = headInsert;
	char *surnameTemp = new char[20];

	do
	{
		if (strXcmp(surnameTemp, iterInsert->surname) != 0)
		{
			strcpy(surnameTemp, addSurname(iterInsert));
			cout << "add surname -> " << surnameTemp<< endl;
		}
		iterInsert = iterInsert->next;
	} while(iterInsert != headInsert);

	delete [] surnameTemp;
	return EXIT_SUCCESS;
}

/* insertList bagli listesini ekrana yazdirir. */
bool listInsert(){

	if(headInsert == NULL)
	{
		cout << "Liste bos, lutfen yeni ogrenci ekleyin. Eger daha önce"
			 << " öğrenci ekleyip MAILLerini oluşturduysanız, MAILLer"
			 << " oluşturulduktan sonra liste temizlenmistir." << endl;
		return EXIT_FAILURE;
	}
	cout << "LİSTELE INSERT" << endl;
	insertList *iterInsert = headInsert;

	int i = 0;
	
	do
	{
		cout << ++i << " - " << iterInsert->name << "\t" 
			<< iterInsert->surname << "\t" << iterInsert->id << endl;
		iterInsert = iterInsert->next;
	} while(iterInsert != headInsert);
	

	
	return EXIT_SUCCESS;
}

/* Soyisim->mail agaci seklinde MAILLeri yazdirir. */
bool listSurname(){

	if(headSurname == NULL)
	{
		cout << "surnameMap bos, lutfen \"Create\" ile soyisimleri olusturun."
			 << endl;
		return EXIT_FAILURE;
	}
	cout  << endl << "LİSTELE SURNAME" << endl;
	surnameMap *iterSurname = headSurname;
	studentInfo * iterStudentInfo;

	int i = 1;
	do
	{
		cout << i++ << " - " << iterSurname->surname << endl;
		iterStudentInfo = iterSurname->mailHead;
		while(iterStudentInfo !=NULL)
		{
			cout << "\t" << iterStudentInfo->mail << "@itu.edu.tr\t"
				 << iterStudentInfo->name << "\t"
				 << iterStudentInfo->surname << endl;
			iterStudentInfo = iterStudentInfo->next;
		}
		iterSurname = iterSurname->next;
	}while(iterSurname != headSurname);
	cout << endl << endl;

	return EXIT_SUCCESS;
}

/* name-surname'den ogrenciyi insertList'e soyadi siralamasi ile ekler. */
insertList *insertPerson(char *name, char *surname){

	insertList *newPerson = new insertList;
	newPerson->name = new char[NAMEL];
	newPerson->surname = new char[SURNAMEL];

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->next = NULL;
	newPerson->id = ++numberRecord;

	/* headInsert olustur */
	if(headInsert==NULL)
	{
		headInsert = newPerson;
		tailInsert = newPerson;
	}
	/* headInsert zaten var */
	else 
	{	
		insertList *iterInsert;
		iterInsert = headInsert;
		/* Ilk siraya ekle */
		if(strXcmp(iterInsert->surname, newPerson->surname) > 0)
		{
			newPerson->next = iterInsert;
			headInsert = newPerson;
		}
		else
		{
			while(iterInsert->next != headInsert)
			{
				/* Ortaya yaz. */
				if(strXcmp(iterInsert->next->surname, newPerson->surname) > 0)
				{
					newPerson->next = iterInsert->next;
					iterInsert->next = newPerson;
					break;
				}
				iterInsert = iterInsert->next;
			}
			/* Sona ekle */
			if(iterInsert->next == headInsert)
			{
				iterInsert->next = newPerson;
				tailInsert = newPerson;
			}
		}
	}
	tailInsert->next = headInsert;	
	return newPerson;
}

/* Dosyadan ogrenci kayitlarini ekler. */
bool insertAll(char *fileName){

	if(contBTwoName == EXIT_FAILURE)
	{
		return insertAll1(fileName);
	}
	else
	{
		return insertAll2(fileName);
	}
}

/* Dosyadan ogrenci kayitlarini ekler.
 * Bu işlemi yaparken 2 isimli öğrenciler dikkate alınmaz.
 */
bool insertAll1(char *fileName){

	FILE *dgInsert;
	if((dgInsert = fopen(fileName, "r")) == NULL)
	{
		cout << "Data could not be inserted." << endl;
		return EXIT_FAILURE;
	}

	char *name = new char[NAMEL], *surname = new char[SURNAMEL];

	while(!feof(dgInsert))
	{
		fscanf(dgInsert, "%s %s", name, surname);
		insertPerson(name, surname);
	}
	
	delete [] name;
	delete [] surname;

	fclose(dgInsert);
	
	return EXIT_SUCCESS;
}

/* Dosyadan öğrenci kayitlarini ekler.
 * Bu işlemi yaparken 2 isimli öğrenciler de dikkate alınır.
 */
bool insertAll2(char *fileName){

	FILE *dgInsert;
	if((dgInsert = fopen(fileName, "r")) == NULL)
	{
		cout << "Data could not be inserted." << endl;
		return EXIT_FAILURE;
	}

	char *name = new char[NAMEL], *surname = new char[SURNAMEL];
	char *birlesik = new char[NAMEL+SURNAMEL];

	while(!feof(dgInsert))
	{
		for (int i = 0; i < NAMEL; ++i)
		{
			name[i] = '\0';
		}
		for (int i = 0; i < SURNAMEL; ++i)
		{
			surname[i] = '\0';
		}

		/* Dosyadan isimler-soyisim satırını komple alır. */
		fgets(birlesik, sizeof(char)*(NAMEL+SURNAMEL), dgInsert);
		/* Sondaki satır sonunu siler. */
		for (int i = 0; birlesik[i] != '\0'; ++i)
		{
			if(birlesik[i] == '\r')
			{
				birlesik[i] = '\0';
			}
			else if(birlesik[i] == '\n')
			{
				birlesik[i] = '\0';
			}
		}
		/* isim-soyisim olarak böler. */
		for (int i = 0, a=0,c=0; birlesik[i] != '\0'; ++i)
		{
			if(c==0)
			{	
				if(birlesik[i] == '\t')
				{
					c++;
				}
				else
				{
					name[a] = birlesik[i];
					a++;
				}
			}
			else if(a!=0 /*c!=0*/)
			{
				if(birlesik[i] == '\t')
				{
					cout << "Err03: " << birlesik << endl;
					break;
				}
				else
				{
					surname[c-1] = birlesik[i];
					c++;
				}
			}
		}
		
		insertPerson(name, surname);
		
	}
	
	delete [] name;
	delete [] surname;
	delete [] birlesik;

	fclose(dgInsert);
	
	return EXIT_SUCCESS;
}

/* Kullanicidan el ile yeni kayit ekler. */
void insertNewRecord(){

	char *name = new char[NAMEL], *surname = new char[SURNAMEL];
	char *birlesik = new char[NAMEL+SURNAMEL];
	cout << "If you press <tab> between <name> and <surname>,"
		 << "the record can not be added." << endl
		 <<"Enter name and surname of new student (<names> <tab> <surname>): ";
	
	if(contBTwoName == EXIT_FAILURE)
	{
		cin >> name >> surname;
	}
	else
	{
		getchar();
		/* Kullanıcıdan isimler-soyisim satırını komple alır. */
		fgets(birlesik, sizeof(char)*(NAMEL+SURNAMEL), stdin);
		/* Sondaki satır sonunu siler. */
		for (int i = 0; birlesik[i] != '\0'; ++i)
		{
			if(birlesik[i] == '\r')
			{
				birlesik[i] = '\0';
			}
			else if(birlesik[i] == '\n')
			{
				birlesik[i] = '\0';
			}
		}
		/* isim-soyisim olarak böler. */
		for (int i = 0, a=0,c=0; birlesik[i] != '\0'; ++i)
		{
			if(c==0)
			{	
				if(birlesik[i] == '\t')
				{
					c++;
				}
				else
				{
					name[a] = birlesik[i];
					a++;
				}
			}
			else if(a!=0 /*c!=0*/)
			{
				if(birlesik[i] == '\t')
				{
					cout << "Err03: " << birlesik << endl;
					break;
				}
				else
				{
					surname[c-1] = birlesik[i];
					c++;
				}
			}
		}
	}

	
	insertPerson(name, surname);
	delete [] name;
	delete [] surname;
	delete [] birlesik;
}

/* menuye gore secilen islemi uygular. */
bool doOperation(char op){

	switch (op)
	{
		case '1':
			if(!createList())
			{
				createMailAll();
			}
			break;
		
		case '2':
			char *fileName;
			fileName = new char[FILENAMEL];
			char fileOp;
			cout << "\t1 - dataset_wOutTurkishChars.txt" << endl
				 << "\t2 - newStudentsList.txt" << endl
				 << "\t3 - Enter new file name" << endl << endl
				 << "\tEnter your choice: " ;
			cin >> fileOp;
			switch(fileOp)
			{
				case '1':
				strcpy(fileName, "dataset_wOutTurkishChars.txt");
				break;
				case '2':
				strcpy(fileName, "newStudentsList.txt");
				break;
				case '3':
				cout << "\t\tEnter your file's name: ";
				cin >> fileName;
				break;
				default:
				cout << "Enter valid choice!" << endl;
				fileOp = 'x';
				break;
			}
			if(fileOp == 'x')	break;

			if(!insertAll(fileName))
			{
				cout << "Students' name and surname from \"" << fileName 
				<< "\" are reading." << endl;
			}
			
			delete []fileName;
			
			break;
		
		case '3':
			insertNewRecord();
			break;
		
		case '4':
			if(writeFile(stdout)==EXIT_FAILURE)
			{
				break;
			}
			char *mail;
			mail = new char[55];
			cout << endl << "Enter the part before \"@\" of email of "
				 << "the student you want to delete: ";
			cin >> mail;
			if(findStudentInfo(mail) == NULL)
			{
				cout << "email could not be found." << endl;
				break;
			}
			deleteStudent(findStudentInfo(mail));
			delete [] mail;
			break;
		
		case '5':
			if(listSurname()==EXIT_FAILURE)
			{
				break;
			}
			char *surname;
			surname = new char[55];
			cout << endl << "Enter surname you want to delete: ";
			cin >> surname;
			if(findSurnameMapPrevFromSurname(surname) != NULL)
			{
				deleteSurnameNext(findSurnameMapPrevFromSurname(surname));
			}
			
			delete [] surname;
			break;
		
		case '6':
			if(writeFile(stdout)==EXIT_FAILURE)
			{
				break;
			}
			char *mail2;
			mail2 = new char[55];
			cout << endl << "Enter the part before \"@\" of email of the"
				 << " student you want to update: ";
			cin >> mail2;
			if(findStudentInfo(mail2) == NULL)
			{
				cout << "email could not be found." << endl;
				break;
			}
			updateStudent(findStudentInfo(mail2));
			break;
		
		case '7':
			FILE *dgPrint;
			char *fileNameP;
			fileNameP = new char[40];
			char fileOpP;
			cout << "\t1 - Print to \"emailList.txt\"" << endl
				 << "\t2 - Print to screen" << endl
				 << "\t0 - Print to another file" << endl << endl
				 << "\tEnter your choice: " ;
			cin >> fileOpP;
			switch(fileOpP)
			{
				case '1':
				if((dgPrint = fopen("emailList.txt","w"))==NULL)
				{
					cout << "\"emailList.txt\" could not be created." << endl;
					break;
				} 
				else
				{
					cout << "Writes the latest version of the list to" 
						 <<	"\"emailList.txt\"" << endl;
					writeFile(dgPrint);
					fclose(dgPrint);
				}
				break;

				case '2':
				cout << "Writes the latest version of the list to screen"
					 << endl;
				writeFile(stdout);
				break;

				case '0':
				cout << "\t\tEnter your file's name: ";
				cin >> fileNameP;
				if((dgPrint = fopen(fileNameP,"w"))==NULL)
				{
					cout << "\"" << fileNameP << "\" could not be created."
						 << endl;
					break;
				} 
				else
				{
					cout << "Writes the latest version of the list to \"" 
						 <<	fileNameP << "\"" << endl;
					writeFile(dgPrint);
					fclose(dgPrint);
				}
				break;

				default:
				cout << "Enter valid choice!" << endl;
			}
			delete []fileNameP;
			break;
		
	/***********PROGRAM DISI KONTROL SEÇENEKLERİ***************/
		case '0':
			return EXIT_FAILURE;

		case '8':
			setPreferences();
			createBoolControls();
			break;
		
		case '9':
			listSurname();
			listInsert();
			break;

		case 'x':
			createList();
			break;
	/*************************BITIS****************************/
		default:
			cout << "Enter valid operations!" << endl;
			break;
		
	}
	return EXIT_SUCCESS;
}
/*************************FINISH*************************/
