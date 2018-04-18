#include "CivilRegistry.h"
#include <cstring>
using namespace std;
CivilRegistry::CivilRegistry()
{

}

// İlgili listeye ekleme fonksiyonuna yönlendirir.
void CivilRegistry::insertCitizen(Citizen *newCitizen)
{
    // Randevulu vatandaşlar
    if(newCitizen->getAppState() == true)
        insert_citizen_to_wApp(newCitizen);
    // Randevusuz vatandaşlar
    else
        insert_citizen_to_wOutApp(newCitizen);


}

/* return 1 -> Silme başarılı
 * return 0 -> İlgili liste boş
 * return -1 -> Geçersiz argüman
 */
int CivilRegistry::removeCitizen(int whichList)
{
    switch (whichList) {
    // 1 -> Randevulu listesi
    case 1:
        if(wApp.empty() == true)
            return 0;
        cout << wApp.begin()->get_name() << endl;
        wApp.pop_front();
        return 1;
    // 2 -> Randevusuz listesi
    case 2:
        if(wOutApp.empty() == true)
            return 0;
        cout << wOutApp.begin()->get_name() << endl;
        wOutApp.pop_front();
        return 1;
    default:
        return -1;
    }
}

/* Randevulu vatandaşları tarih, appSlot ve geliş saatine göre
 * sıralı olarak ekler.
 */
void CivilRegistry::insert_citizen_to_wApp(Citizen *newCitizen)
{
    list<Citizen>::iterator it;
    for(it = wApp.begin(); it != wApp.end(); ++it){
        if(citizen_minor_operator(*newCitizen, *it)){
            wApp.insert(it,*newCitizen);
            break;
        }
    }
    if(it == wApp.end())
        wApp.insert(it,*newCitizen);
}

/* Randevusu olmayan vatandaşları sadece geliş tarih ve saatine
 * göre sıralı olarak ekler.
 */
void CivilRegistry::insert_citizen_to_wOutApp(Citizen *newCitizen)
{
    std::list<Citizen>::iterator it;
    for(it = wOutApp.begin(); it != wOutApp.end(); ++it){
        if(newCitizen->getAppTime() < it->getAppTime() ){
            wOutApp.insert(it,*newCitizen);
            break;
        }
    }
    if(it == wOutApp.end())
        wOutApp.insert(it,*newCitizen);

}

/* Önce tarihlere bakılır. Tarihlerde "a", "b"den önce ise "true",
 * büyükse "false" döner. Eğer tarihler aynıysa appSlotlara bakılır.
 * appSlotlarda "a", "b"den önceyse true, büyükse "false" döner.
 * Son olarak da geliş saatlerine bakılır. gelis saati önce olan
 * sıralamada önce olur.
 */
bool CivilRegistry::citizen_minor_operator(Citizen a, Citizen b)
{
    // Tarihlere bakılır
    if(a.getAppTime().get_date() > b.getAppTime().get_date())
        return false;
    if(a.getAppTime().get_date() < b.getAppTime().get_date())
        return true;

    //appSlot'lara bakılır
    if(a.get_appSlot() > b.get_appSlot())
        return false;
    if(a.get_appSlot() < b.get_appSlot())

        return true;
    //Saatlere bakılır
    return a.getAppTime() < b.getAppTime();
}
