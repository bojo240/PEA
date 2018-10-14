#include <fstream>
#include <iostream>
#include <cmath>

int shortestdistance=INT_MAX;
std::string shortestpath= "";
void recurency(int, int, int*, int**, std::string);

int  main()
{
    //-------------------------------------------------------------------
    //WCZYTANIE DANYCH, OBROBKA WSTEPNA DANYCH PRZED WYWOLANIEM ALGORYTMU

    int cityamount=0, b=0;

    std::fstream plik;

    plik.open("plik.txt",std::ios::in);

    if(plik.good()) //zabezpieczenie
    {
        while(plik>>b)
            ++cityamount; //zliczam ile jest odleglosci pomiedzy miastami
    }

    plik.close();

    plik.open("plik.txt",std::ios::in);

    cityamount=sqrt(cityamount); //pierwiastek z ilosci odleglosci da mi ilosc miast

    int **a = new int *[cityamount]; //tablica przechowujaca odleglosci miedzy miastami.
    for(int i=0;i<cityamount;++i)
        a[i]=new int[cityamount];

    for(int i=0;i<cityamount;++i)
        for(int j=0;j<cityamount;++j)
        {
            plik>>b;
            a[i][j]=b;
        }

    //-----------------------------------------------------------------
    // FAKTYCZNY ALGORYTM
    // PRZY WYWOLYWANIU FUNKCJI WYSYLAM JAKO ARGUMENT TABLICE INTOW. 0 - MIASTO NIEODWIEDZONE, 1 - MIASTO ODZWIEDZONE, 2 - MIASTO OBOECNE, 3 - MIASTO OBECNE

    //tworze tablice z zerami i jedna dwojka
    int c[4]={3,0,0,0};
    std::string path = "A";
    recurency(cityamount,0,c, a, path);
    c[0]=0;
    c[1]=3;
    path = "B";
    recurency(cityamount,0,c, a, path);
    c[1]=0;
    c[2]=3;
    path = "C";
    recurency(cityamount,0,c, a, path);
    c[2]=0;
    c[3]=3;
    path = "D";
    recurency(cityamount,0,c, a, path);

    std::cout<<"Najktrotsza droga przez wszystkie miasta to: "<<shortestpath<<'\n';
    std::cout<<"Jej calkowity dystans wynosi: "<<shortestdistance;
}

void recurency(int cityamount, int currentdistance, int seen[], int**distances, std::string path) // zamiast roznych wartosci w tablicach moze by wysylac tablice booli z odwiedzonymi oraz w osobnych argumentach indeksy ostatnio odwiedzonego miasta i pierwszego miasta?
{
//    std::cout<<"cityamount:"<<cityamount<<'\n';
//    std::cout<<"currentdistance:"<<currentdistance<<'\n';
//    std::cout<<"path:"<<path<<'\n';
//    std::cout<<"shortestdistance: "<<shortestdistance<<'\n';
//    std::cout<<"shortestpath: "<<shortestpath<<'\n';

    int* copyseen = new int[cityamount];//kopiuje tablice przekazana jako argument, inaczej operowalbym caly czas na oryginalnych danych

    for(int i=0;i<cityamount;++i)
    {
        copyseen[i]=seen[i];//w tym momencie wiem juz gdzie bylem, a gdzie musze wejsc
        std::cout<<copyseen[i];
    }
    std::cout<<'\n';
    bool end = true;//zmienna pomocnicza, iterator
    int j=0;
    bool a=false;
    for(;j<cityamount;++j)//iterator j przechowuje ostatnio odwiedzone miasto
        if(copyseen[j]==2)
        {
            a=true;//wiem ze byla '2' w tablicy odwiedzonych miast
            break;//mam teraz 'j' nastawione na ostatnio odwiedzone miasto
        }

    for(int i=0;i<cityamount;++i)//sprawdzam czy jest jeszcze jakies nieodwiedzone miasto
    {
        if(copyseen[i]==0)//iterator i przechowuje pierwsze nieodwiedzone miasto,
        {
            end=false;// jezeli znalazl jakies nieodwiedzone miasto, to znaczy ze jeszcze nie skonczyl, nie doszedl do liscia
            if(a)//jezeli znalazl dwojke, zamien dwojke na jedynke -- 10 linijek wyzej deklaruje bool a i zmieniam na true, jezeli znalazl '2' w tablicy
                copyseen[j]=1;
            else//jezeli nie znalazl dwojki (ostatnio odwiedzonego miasta), niech znajdzie trojke,
                for(j=0;j<cityamount;++j)
                    if(copyseen[j]==3)
                        break;
            //mam nastawione j na '3' badz na wczesniejsza'2', jest to bez roznicy, licze teraz odleglosc miedzy obecnym miastem a nastepnym

            currentdistance+=distances[j][i];
            path += 'A'+i;

            copyseen[i]=2;//i pierwsze napotkane 0 zmien na dwojke
            recurency(cityamount, currentdistance, copyseen, distances, path);
        }
    }
    //--nie wchodzi we wczesniejsze fory, mysli ze juz jest koniec, przy odwolaniu sie do talbicy distances[j][g] wypierdala sie
    if(end)//jezeli nie ma juz nieodwiedzonych miast, dodaj ostatnia odleglosc od ostatniego miasta do pierwszego i sprawdz, czy wynik jest krotszy od obecnego najkrotszego, jezeli tak to podmien te wyniki
        {
            //znajdz indeks pierwsezgo miasta
            int g=0;
            for(;g<cityamount;++g)
                if(copyseen[g]==3)
                    break;
            currentdistance+=distances[j][g];
            if(currentdistance<shortestdistance) //jezeli ta sciezka jest krotsza od najkrotszej dotychczas znalezionej, zamien wartosc najkrotszej sciezki na krotsza
            {
                shortestdistance=currentdistance;
                path += 'A'+g;
                shortestpath=path;
            }
        }
    delete[] copyseen;
    //jezeli wyszedl z petli to znaczy ze odwiedzil juz wszystkie miasta i czas wrocic do pierwszego.

}
