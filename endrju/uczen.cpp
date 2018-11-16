#include "uczen.h"
//#include <iostream>
void uczen::setWiek(int wiek)
{
    this.wiek = wiek;
}
int uczen::getWiek()
{
    return uczen::wiek;
}
uczen::uczen(int age, std::string name, std::string lastname, std::string classname)
{
    wiek=age;
    imie=name;
    nazwisko = lastname;
    //nazwaklasy = classname;
}

void uczen::wyswietl()
{
    std::cout<<'\n'<<klasa<<wiek<<imie<<nazwisko;
    }
