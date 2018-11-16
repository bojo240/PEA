#pragma once
#include "klassa.h"
#include <string>
#include <iostream>

class uczen
{
    public:
        std::string nazwaklasy;
    private:
        int wiek;
        std::string imie;
        std::string nazwisko;
    public:
        uczen(int, std::string, std::string, std::string);
        void setWiek(int);
        void setImie(std::string);
        void setNazwisko(std::string);
        int getWiek();
        void wyswietl();
        ~uczen();
};
