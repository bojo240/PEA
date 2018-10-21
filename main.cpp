#include <fstream>
#include <iostream>
#include <cmath>

int shortestdistance=INT_MAX;
std::string shortestpath= "";
void recurency(int, bool*, std::string, int, int, bool);
int cityamount=0;
int **distances;

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
    bool* c = new bool[cityamount]; //tworze tablice z miastami ktore odwiedzilem
    for (int i=0;i<cityamount;++i)
        c[i]=false;
    recurency(0, c, "", 0, 0, true);
    std::cout<<"Najkrotsza droga przez wszystkie miasta to: "<<shortestpath<<'\n';
    std::cout<<"Jej calkowity dystans wynosi: "<<shortestdistance;
}

//jako argument rekurencji bool init = true, potem juz bylby false, ktory by zrobil co powinien na pierwszym wywolaniu rekurencjki?

void recurency(int currentdistance, bool seen[], std::string path, int present, int previous, bool init)
{
    bool* copyseen = new bool[cityamount];//kopiuje tablice przekazana jako argument, inaczej operowalbym caly czas na oryginalnych danych
    for(int i=0;i<cityamount;++i)
        copyseen[i]=seen[i];//w tym momencie wiem juz gdzie bylem, a gdzie musze wejsc
    std::string copypath = new std::string;
    copypath = path;
    int g=0;
    if(init==false)
        for(;g<cityamount;++g)
            if(copyseen[g]==false)//iterator i przechowuje pierwsze nieodwiedzone miasto, o ile jeszcze takowe istnieje
            {
                copyseen[g]=true; //zaznaczam, ze miasto w ktorym jestem jest juz odwiedzone
                break;
            }
    for(int i=g;i<cityamount;++i)//sprawdzam czy jest jeszcze jakies nieodwiedzone miasto
        if(copyseen[i]==false)//iterator i przechowuje pierwsze nieodwiedzone miasto, o ile jeszcze takowe istnieje
        {
            for(int j=0;j<cityamount;++j)
                std::cout<<copyseen[j];
            currentdistance+=distances[present][i]; // dodaje odleglosc z miasta obecnego do nastepnego
            previous = present;//w kolejnym poziomie rekurencji, poprzednie miasto bedzie obecnym
            present = i; // a miasto do ktorego bede szedl bedzie w kolejnym poziomie rekurencji obecnym
            copypath += 'A'+present; // dodaje obecne miasto do listy odwiedzonych juz miast
            std::cout<<'\n'<<copypath<<"\n\n\n";
            recurency(currentdistance, copyseen, path, present, previous, false); //wejdz do kolejnego miasta
        }
        //g przechowuje ostatnie miasto, trzeba je dodac i dodac pierwsze miasto, potem wyjsc z rekurencji.
    if(copypath.length()==(cityamount-1))//jezeli jestes na najnizszym z mozliwych poziomow rekurencji
    {
        copypath += static_cast<char>('A'+g);           //dodaje ostatnie miasto
        currentdistance += distances[present][g];
        copypath += path[0];                            //dodaje pierwsze miasto do sciezki
        currentdistance += distances[g][static_cast<int>(path[0] - 'A')];
        if(currentdistance<shortestdistance) //jezeli ta sciezka jest krotsza od najkrotszej dotychczas znalezionej, zamien wartosc najkrotszej sciezki na krotsza
        {
            shortestdistance=currentdistance;
            shortestpath=path;
        }
        std::cout<<"\nNajkrotsza sciezka w tym momencie to "<<path<<'\n';
    }
    delete[] copyseen;
}

//    if(path.length()==cityamount)//jezeli jestes na najnizszym z mozliwych poziomow rekurencji
//    {
//        int temp = static_cast<int>('A' - path[0]);
//        int i=0;
//        for(i=0;i<cityamount;++i)//sprawdzam czy jest jeszcze jakies nieodwiedzone miasto
//            if(copyseen[i]==false)//iterator i przechowuje pierwsze nieodwiedzone miasto, o ile jeszcze takowe istnieje
//                break;
//        currentdistance+=distances[i-1][temp];//wroc z ostatniego miasta w ktorym byles do pierwszego miasta
//        char a = path[0];
//        path += a;
//
//        if(currentdistance<shortestdistance) //jezeli ta sciezka jest krotsza od najkrotszej dotychczas znalezionej, zamien wartosc najkrotszej sciezki na krotsza
//        {
//            shortestdistance=currentdistance;
//            shortestpath=path;
//        }
//        std::cout<<"\nNajkrotsza sciezka w tym momencie to "<<path<<'\n';
//    }
//    delete[] copyseen;

//Pierwszy poziom rekurencji jeest nie wazny, bo ta sama trase sprawdzalbym wielokrotnie.
//przy wchodzeniu do kolejnego poziomu rekurencji dodaje do odwiedzonych, a po wyjsciu z niej, usuwam to.
