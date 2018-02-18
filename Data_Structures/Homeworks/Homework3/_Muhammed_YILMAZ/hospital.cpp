/* @Author
 * Muhammed YILMAZ
 * 150150149
 * yilmazmu15@itu.edu.tr
 */

#include <iostream>
#include <fstream>
#include <cstdlib>	// for EXIT_SUCCESS
#include <cstring>
#include "queue.h"

using namespace std;

/*******************FUNCTIONS__START*******************/
	void createQueues();
	void readInputs();
	void sureliDiz();
	bool allPatientFinish();
	void tedaviOl(int *);
	void topQSend(int *);
	void sendQueueComp(qNode);
	void outputPrint();
/*******************FUNCTIONS_FINISH*******************/

qQueue inputQ, greenQ, yellowQ, redQ, outputQ;

int main(int argc, char *argv[])
{
	createQueues();
	readInputs();
	sureliDiz();
	outputPrint();
	return EXIT_SUCCESS;
}

/*******************FUNCTIONS__START*******************/

/* Queue yapıları oluşturulur. */
void createQueues(){

	inputQ.create();
	greenQ.create();
	yellowQ.create();
	redQ.create();
	outputQ.create();
}

/* Dosyadan veriler okunur. */
void readInputs(){

	qNode temp;
	ifstream dosya;
	dosya.open("patientsInfo.txt");

	// Başlık satırı okunur, islem yapılmaz.
	string gecici;
	getline(dosya,gecici);
	
	// Hasta bilgileri okunur, inputQ'ya eklenir.
	while(!dosya.eof())
	{
		dosya >> temp.name >> temp.arrival
			  >> temp.treatment >> temp.complaint;
		inputQ.enqueue(temp);
	}

	dosya.close();
}

/* Zaman ilerler, gerekli işlemler yapilir. */
void sureliDiz(){

	int time = 0;
	int *timePtr = &time;

	// Tüm hastalar tedavi edilene kadar döngü devam eder.
	while(!allPatientFinish())
	{
		// Hastanın hastaneye gelis zamanı geldiyse ilgili queue'ya eklenir.
		topQSend(timePtr);
		// zaman ilerler
		(*timePtr)++;
		// Hastanede tedavi edilmemis hasta varsa sırayla tedavi edilir.
		tedaviOl(timePtr);
	}
}

/* Tedavi edilmemis hasta var mı diye kontrol eder. 
 * Eğer varsa "true" döner.
 */
bool allPatientFinish(){

	return inputQ.isEmpty() && greenQ.isEmpty()
			 && yellowQ.isEmpty() && redQ.isEmpty();
}

/* Hastayı önceliğine ve (önceliğinin) tedavi süresine göre tedavi eder.
 * Bu sırada zamanın da ilerlemesini sağlar. 
 */
void tedaviOl(int *timePtr){

	if(!redQ.isEmpty())
	{
		// redQ'dan hasta alinir.
		qNode temp = redQ.dequeue();
		// RED icin gerekli zamanda (1) islem yapilir.
		for (int i = 0; i < 1; ++i)
		{
			// Tedavi zamaninda baska hasta gelirse siraya eklenir.
			topQSend(timePtr);
			// Suanki hastanın gerekli toplam tedavi suresi azaltilir.
			temp.treatment--;
			// Zaman ilerletilir.
			(*timePtr)++;
			// Cikti icin outputQ'ya eklenir.
			outputQ.enqueue(temp);
			// Eger gerekli tedavi suresi bittiyse taburcu edilir.
			if(temp.treatment == 0)
			{
				// sureliDiz() fonksiyonunda da zaman arttırıldıgı icin
					// iki kere arttırılmaması icin bir kez azaltilir.
				(*timePtr)--;
				return;
			}
		}
		// sureliDiz() fonksiyonunda da zaman arttırıldıgı icin
			// iki kere arttırılmaması icin bir kez azaltilir.
		(*timePtr)--;
		// Onceligi degistirilir.
		strcpy(temp.complaint, "YELLOW");
		// Bir alt oncelik queue'suna eklenir.
		yellowQ.enqueue(temp);
		
	}
	// redQ icin yapilan islemlerin yellowQ hali yapilir.
	else if(!yellowQ.isEmpty())
	{
		qNode temp = yellowQ.dequeue();
		for (int i = 0; i < 2; ++i)
		{
			topQSend(timePtr);
			temp.treatment--;
			(*timePtr)++;
			outputQ.enqueue(temp);
			if(temp.treatment == 0)
			{
				(*timePtr)--;
				return;
			}
		}
		(*timePtr)--;
		strcpy(temp.complaint, "GREEN");
		greenQ.enqueue(temp);
		
	}
	// redQ icin yapilan islemlerin greenQ hali yapilir.
	else if(!greenQ.isEmpty())
	{
		qNode temp = greenQ.dequeue();
		for (int i = 0; i < 3; ++i)
		{
			topQSend(timePtr);
			temp.treatment--;
			(*timePtr)++;
			outputQ.enqueue(temp);
			if(temp.treatment == 0)
			{
				(*timePtr)--;
				return;
			}
		}
		(*timePtr)--;
		strcpy(temp.complaint, "GREEN");
		greenQ.enqueue(temp);
		
	}
	// Butun oncelik queue'ları bos ise tedavi yapılmaz. 
	else
	{
		// outputPrint()'a bakilirsa burasinin anlasilmasi kolaylasir.
		qNode temp;
		strcpy(temp.name, "No treatment...");
		outputQ.enqueue(temp);
	}
}

/* inputQ'daki hastaları hastaneye geldikleri zamanda
 * öncelik queue'larına ekler.
 */
void topQSend(int *time){

	// Eger hastaneye gelecek hastalar bittiyse islem yapilmaz.
	if(inputQ.isEmpty())
		return;

	// Hastaneye gelecek hastanın vakti geldiyse;
	if(inputQ.front->arrival == *time)
	{
		// Ilgili queue yapisina ekler. (redQ, yellowQ, greenQ)
		sendQueueComp(inputQ.dequeue());
		// Aynı anda gelen hasta varsa diye islem tekrar eder.
		topQSend(time);
	}
}

/* newPatient hastasını öncelik queue'larına ekler. */
void sendQueueComp(qNode newPatient){

	if(strcmp(newPatient.complaint, "RED") == 0)
	{
		redQ.enqueue(newPatient);
	}
	else if(strcmp(newPatient.complaint, "YELLOW") == 0)
	{
		yellowQ.enqueue(newPatient);
	}
	else if(strcmp(newPatient.complaint, "GREEN") == 0)
	{
		greenQ.enqueue(newPatient);
	}
}

/* hangi zamanda kimin tedavi olduğunu ekrana yazdırır. */
void outputPrint(){

	for (int i = 1; !outputQ.isEmpty(); ++i)
	{
		cout << i << ". time slice " << outputQ.dequeue().name << endl;
	}
}
/*******************FUNCTIONS_FINISH*******************/