#include "Citizen.h"
#include <cstring>
// Verilere göre Citizen oluşturulur.
Citizen::Citizen(char *idNo, char *name, char *surname, bool hasApp,
                 Time appTime, char *appSlot)
{
    this->idNo = new char[strlen(idNo)+1];
    strcpy(this->idNo, idNo);

    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);

    this->surname = new char[strlen(surname)+1];
    strcpy(this->surname, surname);

    this->hasApp = hasApp;

    this->appTime = new Time(appTime);

    if(!hasApp)
        this->appSlot = NULL;
    else{
        this->appSlot = new char[strlen(appSlot)+1];
        strcpy(this->appSlot, appSlot);
    }
    //std::cout << idNo << " created" << std::endl;
}

// Olulturulan Citizen free'lenir.
Citizen::~Citizen()
{
    //std::cout << idNo << " removed" << std::endl;
    /*
    delete [] idNo;
    delete [] name;
    delete [] surname;
    delete appTime;
    if(appSlot)
        delete [] appSlot;
    */
}

//appSlotu "hh.mm-hh.mm" formatında döndürür.
const std::string Citizen::get_appSlot()
{
    char appSlotChar[15], copyAppSlot[15], *tok, temp[5];
    strcpy(copyAppSlot, this->appSlot);

    // strtok'lar dizgiyi parçalar
    tok = strtok(copyAppSlot, ".-");
    strcpy(temp, tok);
    // saatin başında 0 yoksa ve 10'dan küçükse sıfır koyar.
    if(temp[1] == '\0')
        sprintf(appSlotChar, "0%s", temp);
    else
        sprintf(appSlotChar, "%s", temp);

    tok = strtok(NULL, ".-");
    strcpy(temp, tok);
    // dakikanın başında 0 yoksa ve 10'dan küçükse sıfır koyar.
    if(temp[1] == '\0')
        sprintf(appSlotChar, "%s.0%s",appSlotChar, temp);
    else
        sprintf(appSlotChar, "%s.%s",appSlotChar, temp);

    tok = strtok(NULL, ".-");
    strcpy(temp, tok);
    // saatin başında 0 yoksa ve 10'dan küçükse sıfır koyar.
    if(temp[1] == '\0')
        sprintf(appSlotChar, "%s-0%s", appSlotChar, temp);
    else
        sprintf(appSlotChar, "%s-%s", appSlotChar, temp);

    tok = strtok(NULL, ".-");
    strcpy(temp, tok);
    // dakikanın başında 0 yoksa ve 10'dan küçükse sıfır koyar.
    if(temp[1] == '\0')
        sprintf(appSlotChar, "%s.0%s", appSlotChar, temp);
    else
        sprintf(appSlotChar, "%s.%s", appSlotChar, temp);

    //std::string olarak döner
    std::string appSlotString(appSlotChar);
    return appSlotString;
}

/* deneme amaçlı Citizen yazdırma fonksiyonu.
void Citizen::print_citizen()
{

    if(appSlot)
        std::cout << idNo << "\t" << name << "\t" << surname << "\t"
                  << hasApp << "\t" << appTime->getTime() << "\t"
                  << get_appSlot() << std::endl;
    else
        std::cout << idNo << "\t" << name << "\t" << surname << "\t"
                  << hasApp << "\t" << appTime->getTime() << "\t"
                  << "........." << std::endl;
}
*/
