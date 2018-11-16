
#include <fstream>
#include <iostream>
#include <cmath>

int shortestdistance=INT_MAX;
std::string shortestpath= "";
bool* seen;
int* order;
int** distances;
int cityamount = 0;

void bruteforce();


//licznik informujacy w ktore miasto w tej iteracji juz wszedl, jezeli wszedl w 3 miasto, to znaczy ze w 1 i 2 tez wszedl?

int  main()
{
    int b=0;
    std::fstream plik;
    plik.open("plik.txt",std::ios::in);
    if(plik.good()) //zabezpieczenie
        while(plik>>b)
            ++cityamount; //zliczam ile jest odleglosci pomiedzy miastami
    else
    {
        std::cout<<"Brak pliku. Dobranoc.";
        return 0;
    }
    plik.clear(); // czyszcze flage eof -- dopiero standard c++11 zapewnia, ze seekg czysci flage eof
    plik.seekg(0); // wracam na poczatek pliku
    cityamount=sqrt(cityamount); //pierwiastek z ilosci odleglosci da mi ilosc miast
    distances = new int *[cityamount]; //tablica przechowujaca odleglosci miedzy miastami.
    for(int i=0;i<cityamount;++i) //dwuwymiarowa tablica dynamiczna
        distances[i]=new int[cityamount];
    for(int i=0;i<cityamount;++i) //zapelnianie tablicy danymi z pliku
        for(int j=0;j<cityamount;++j)
            plik>>distances[i][j];
    plik.close();
    //musze tu jeszcze potworzyc odpowiednie tablice z wskaznikow globalnych, dopiero potem wywolac rekurencje.
    seen = new bool[cityamount];
    order = new int[cityamount];
    bruteforce(0, 0, "");
}

//rekurencja moze rowniez cos zwracac!

void bruteforce(int licznik, int previous, string order)
{
    if(order.length()==cityamount)//jezeli skonczyles.
    {

        return;
    }//przelicz droge z pierwszego miasta do drugiego itd, zsumuj i sprawdz czy nie jest krotsza niz dotychczasowo
    for(int i=order.length();i<cityamount;++i)
    {
        currentdistance+=distances[previous][licznik]; // dodaje odleglosc z miasta obecnego do nastepnego
        previous = licznik;
        seen[licznik] = true; // wejdz do miasta
        order += static_cast<char>('A'+licznik);
        ++licznik;    //licznik ustawiony na 0;
        bruteforce(licznik, previous, order);
    }



}
