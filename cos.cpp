#include <fstream>
#include <iostream>
#include <cmath>

int shortestdistance=INT_MAX;
std::string shortestpath= "";
void recurency(int, bool*, char*, int, int, int, bool);
int cityamount=0;
int **distances;

int  main()
{
    int b=0;
    std::fstream plik;
    plik.open("plik.txt",std::ios::in);
    if(plik.good()) //zabezpieczenie
        plik>>cityamount;
    else
    {
        std::cout<<"Brak pliku. Dobranoc.";
        return 0;
    }
    distances = new int *[cityamount]; //tablica przechowujaca odleglosci miedzy miastami.
    for(int i=0;i<cityamount;++i) //dwuwymiarowa tablica dynamiczna
        distances[i]=new int[cityamount];
    for(int i=0;i<cityamount;++i) //zapelnianie tablicy danymi z pliku
        for(int j=0;j<cityamount;++j)
            plik>>distances[i][j];
    plik.close();
    bool* c = new bool[cityamount]; //tworze tablice z miastami ktore odwiedzilem
    for (int i=0;i<cityamount;++i)
        c[i]=false;
    recurency(0, c, "", 0, 0, 0, true);
    std::cout<<"Najkrotsza droga przez wszystkie miasta to: "<<shortestpath<<'\n';
    std::cout<<"Jej calkowity dystans wynosi: "<<shortestdistance;
}

void recurency(int currentdistance, bool seen[], char path[], int currentlevel, int present, int previous, bool init)
{
    bool* copyseen = new bool*;
    for(int i=0;i<cityamount;++i)
        copyseen[i] = seen[i];
    char* copypath = new char[currentlevel+2];//
    for(int i=0;i<currentlevel;++i)
        copypath[i] = path[i];
    copypath[currentlevel+1] = '\0';

}
