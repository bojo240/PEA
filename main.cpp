#include <iostream>
#include <conio.h>
#include "bnb.h"
#include "comparator.h"
#include "bf.h"
#include <fstream>

void loadData(int, int**);                          // wczytywanie danych z pliku do tablicy

int main()
{
    int choice = 3;
    while(choice!=0)
    {
        std::cout<<"1. Brute Force.\n2. Branch & Bound.\n\n";
        std::cout<<"Twoj wybor: ";
        choice = getche();
        switch(choice)
        {
            case 1:
                executeBF();
                break;
            case 2:
                executeBnB();
                break;
            default:
                break;
        }
    }
}

void loadData(int cityamount, int **distances)      // wczytywanie danych z pliku do tablicy
{
    std::fstream file;
    std::string fileName;
    std::cout<<"Podaj nazwe pliku:";
    std::cin>>fileName;
    file.open(fileName,std::ios::in);
    if(file.good())                                 // zabezpieczenie
        file>>cityamount;
    else
        return;
    distances = new int *[cityamount];              // tablica przechowujaca odleglosci miedzy miastami.
    for(int i=0;i<cityamount;++i)                   // dwuwymiarowa tablica dynamiczna
        distances[i]=new int[cityamount];
    for(int i=0;i<cityamount;++i)                   // zapelnianie tablicy danymi z pliku
        for(int j=0;j<cityamount;++j)
            file>>distances[i][j];
    file.close();
}


