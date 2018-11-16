#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>

int shortestdistance=INT_MAX;
std::string shortestpath= "";

void recurency(int, bool*, std::string, int, int);

int cityamount=0;
int **distances;

int  main()
{
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
    for(int i=0;i<cityamount;++i) //dwuwymiarowa ta\blica dynamiczna
        distances[i]=new int[cityamount];
    for(int i=0;i<cityamount;++i) //zapelnianie tablicy danymi z pliku
        for(int j=0;j<cityamount;++j)
            plik>>distances[i][j];
    plik.close();
    bool* c = new bool[cityamount]; //tworze tablice z miastami ktore odwiedzilem
    for (int i=0;i<cityamount;++i)
        c[i]=false;
    recurency(0, c, "", -1, 0);
    std::cout<<"Najkrotsza droga przez wszystkie miasta to: "<<shortestpath<<'\n';
    std::cout<<"Jej calkowity dystans wynosi: "<<shortestdistance;
}

void recurency(int currentdistance, bool seen[], std::string path, int present, int previous)
{
    bool* copyseen = new bool[cityamount];//kopiuje tablice przekazana jako argument, inaczej operowalbym caly czas na oryginalnych danych
    for(int i=0;i<cityamount;++i)
        copyseen[i]=seen[i];//w tym momencie wiem juz gdzie bylem, a gdzie musze wejsc
    if(present!=(-1))
        copyseen[present]=true; //zaznaczam miasto jako odwiedzone
    else
        present = 0;
    std::string copypath = path;

    for(int j=0;j<cityamount;++j)
        std::cout<<copyseen[j];

    for(int i=0;i<cityamount;++i)//sprawdzam czy jest jeszcze jakies nieodwiedzone miasto
        if(copyseen[i]==false)
        {
            std::cout<<"\n\ndodaje dystans: distances["<<present<<"]["<<i<<"], czyli "<<distances[present][i]<<"\n\n";
            currentdistance+=distances[present][i]; // dodaje odleglosc z miasta obecnego do nastepnego
            std::cout<<"\ncurrentdistance: "<<currentdistance<<"\n\n";
            previous = present;//w kolejnym poziomie rekurencji, poprzednie miasto bedzie obecnym
            present = i; // a miasto do ktorego bede szedl bedzie w kolejnym poziomie rekurencji obecnym
            copypath += 'A'+present; // dodaje obecne miasto do listy odwiedzonych juz miast
            std::cout<<"\ncopypath:"<<copypath<<"\n\n";
            recurency(currentdistance, copyseen, copypath, present, previous); //wejdz do kolejnego miasta
            copypath = path;
            present = previous;
            currentdistance -= distances[present][i];
            std::cout<<copypath<<" "<<path<<" "<<currentdistance<<'\n';\
        }
        //tutaj po powrocie z rekurencji z 4 poziomu na 3 moge sobie wszystko wypisac



    if(path.length()==cityamount)//jezeli jestes na najnizszym z mozliwych poziomow rekurencji
    {
        std::cout<<"\n\njestem w drugim ifie. copypath.length() = 4, copypath:";
        copypath += copypath[0];        //dodaje pierwsze miasto do sciezki
        char c = copypath[0];
        std::cout<<copypath<<'\n';
        std::cout<<"\ndodaje dystans z miasta ostatniego do pierwszego, czyli distances["<<present<<"]["<<static_cast<int>(c-'A')<<"]."<<'\n';
        currentdistance += distances[present][static_cast<int>(c-'A')];
        std::cout<<"w tym momencie currentdistance wynosi:"<<currentdistance<<"\n\nDotad jest git\n\n";
        if(currentdistance<shortestdistance) //jezeli ta sciezka jest krotsza od najkrotszej dotychczas znalezionej, zamien wartosc najkrotszej sciezki na krotsza
        {
            shortestdistance=currentdistance;
            shortestpath=copypath;
        }
        std::cout<<"\nNajkrotsza sciezka w tym momencie to "<<copypath<<'\n';
    }
    delete[] copyseen;
}
