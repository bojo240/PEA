#include <fstream>
#include <iostream>
#include <cmath>

int shortestdistance=INT_MAX;
std::string shortestpath= "";
void recurency(int, int, int*, int**, std::string, int, int, int);


//WYPIERDOLIC copyseen[i]=licznik; TAK, ZEBY ZAZNACZALO TO DOPIERO PO WEJSCIU W MIASTO!!!!!!!!!!!! ZACZNIE DZIALAC NA 100%!


int  main()
{
    int cityamount=0, b=0;
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
    int **a = new int *[cityamount]; //tablica przechowujaca odleglosci miedzy miastami.
    for(int i=0;i<cityamount;++i) //dwuwymiarowa tablica dynamiczna
        a[i]=new int[cityamount];
    for(int i=0;i<cityamount;++i) //zapelnianie tablicy danymi z pliku
        for(int j=0;j<cityamount;++j)
            plik>>a[i][j];
    plik.close();
    int* c = new int[cityamount]; //tworze tablice z miastami ktore odwiedzilem
    for (int i=0;i<cityamount;++i)
        c[i]=0;
    recurency(cityamount, 0, c, a, "", 0, 0, 0);
    std::cout<<"Najkrotsza droga przez wszystkie miasta to: "<<shortestpath<<'\n';
    std::cout<<"Jej calkowity dystans wynosi: "<<shortestdistance;
}
//musze sobie wyswietlac ta tablice booli na kazdym poziomie, zeby wiedziec czy on sie poprawnie wraca
//moze byc po prostu problem z tymi zjebanymi indexami itd, a nie z tym czy sie wraca czy nie.
//NIECH TABLICA BEDZIE PO PROSTU KOLEJNOSCIA, NP 1432, 1324, 1234

void recurency(int cityamount, int currentdistance, int seen[], int**distances, std::string path, int present, int previous, int licznik)
{
    int* copyseen = new int[cityamount];//kopiuje tablice przekazana jako argument, inaczej operowalbym caly czas na oryginalnych danych
    for(int i=0;i<cityamount;++i)
        copyseen[i]=seen[i];//w tym momencie wiem juz gdzie bylem, a gdzie musze wejsc
    for(int j=0;j<cityamount;++j)
        std::cout<<copyseen[j];
    std::cout<<"\n\n\n";
    for(int i=0;i<cityamount;++i)
        if(copyseen[i]==0)//iterator i przechowuje pierwsze nieodwiedzone miasto, o ile jeszcze takowe istnieje
            copyseen[i]=licznik; //zaznaczam, ze miasto w ktorym jestem jest juz odwiedzone
    for(int i=0;i<cityamount;++i)//sprawdzam czy jest jeszcze jakies nieodwiedzone miasto
        if(copyseen[i]==0)//iterator i przechowuje pierwsze nieodwiedzone miasto, o ile jeszcze takowe istnieje
        {
            ++licznik;
            currentdistance+=distances[present][i]; // dodaje odleglosc z miasta obecnego do nastepnego
            previous = present;//w kolejnym poziomie rekurencji, poprzednie miasto bedzie obecnym
            present = i; // a miasto do ktorego bede szedl bedzie w kolejnym poziomie rekurencji obecnym
            path += 'A'+present; // dodaje obecne miasto do listy odwiedzonych juz miast
            std::cout<<"\n\n";
            recurency(cityamount, currentdistance, copyseen, distances, path, present, previous, licznik); //wejdz do kolejnego miasta
        }
    if(path.length()==cityamount)//jezeli jestes na najnizszym z mozliwych poziomow rekurencji
    {
        int temp = static_cast<int>('A' - path[0]);
        int i=0;
        for(i=0;i<cityamount;++i)//sprawdzam czy jest jeszcze jakies nieodwiedzone miasto
            if(copyseen[i]==0)//iterator i przechowuje pierwsze nieodwiedzone miasto, o ile jeszcze takowe istnieje
                break;
        currentdistance+=distances[i-1][temp];//wroc z ostatniego miasta w ktorym byles do pierwszego miasta
        char a = path[0];
        path += a;

        if(currentdistance<shortestdistance) //jezeli ta sciezka jest krotsza od najkrotszej dotychczas znalezionej, zamien wartosc najkrotszej sciezki na krotsza
        {
            shortestdistance=currentdistance;
            shortestpath=path;
        }
        std::cout<<"\nNajkrotsza sciezka w tym momencie to "<<path<<'\n';
    }
    delete[] copyseen;
}

//Pierwszy poziom rekurencji jeest nie wazny, bo ta sama trase sprawdzalbym wielokrotnie.
//przy wchodzeniu do kolejnego poziomu rekurencji dodaje do odwiedzonych, a po wyjsciu z niej, usuwam to.
