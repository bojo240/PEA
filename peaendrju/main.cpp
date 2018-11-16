#include <fstream>
#include <iostream>
#include <cmath>

int shortestdistance=INT_MAX;
std::string shortestpath= "";

void recurency(int, bool*, std::string, int, int, bool);
int cityamount=0;
int **distances;
void wypisz();
void fileread();
int  main()
{
    bool* c = new bool[cityamount]; //tworze tablice z miastami ktore odwiedzilem
    for (int i=0;i<cityamount;++i)
        c[i]=false;
    fileread();
    wypisz();
    std::cout<<"Najkrotsza droga przez wszystkie miasta to: "<<shortestpath<<'\n';
    std::cout<<"Jej calkowity dystans wynosi: "<<shortestdistance;
}

//funkcja do odczytyawnia danych z pliku
void fileread()
{
    int copycityamount;
    std::fstream plik;
    plik.open("plik.txt",std::ios::in);
    if(plik.good()) //zabezpieczenie
    {
        plik>>cityamount;
        distances = new int* [cityamount];
        for(int i=0;i<cityamount;++i) //dwuwymiarowa tablica dynamiczna
            distances[i]=new int[cityamount];
        for(int i=0;i<cityamount;++i) //zapelnianie tablicy danymi z pliku
            for(int j=0;j<cityamount;++j)
                plik>>distances[i][j];
    }
}

void wypisz()
{
    for(int i=0;i<cityamount;++i)
    {
        for(int j=0;j<cityamount;++j)
            std::cout<<distances[i][j]<<" ";
        std::cout<<'\n';
    }
}

