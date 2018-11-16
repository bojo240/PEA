#include <fstream>
#include <iostream>

int shortestdistance=INT_MAX;
std::string shortestpath;
int cityamount;
int **distances;

void bruteForce(int, bool*, std::string, int, int, bool);

int  main()
{
    std::fstream plik;
    plik.open("plik.txt",std::ios::in);
    if(plik.good()) //zabezpieczenie
        plik>>cityamount;
    else
        return 3;
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
//    for (int i=0;i<cityamount;++i)
//        distances[i][i] = 0;

    bruteForce(0, c, "", 0, -1, true);
    std::cout<<"Najkrotsza droga przez wszystkie miasta to: "<<shortestpath<<'\n';
    std::cout<<"Jej calkowity dystans wynosi: "<<shortestdistance;
}

void bruteForce(int currentdistance, bool seen[], std::string path, int present, int previous, bool init)
{
    std::string copypath = path;
    if (copypath.length()==2)
        std::cout<<copypath<<'\n';
    for(int i=0;i<cityamount;++i)//sprawdzam czy jest jeszcze jakies nieodwiedzone miasto
        if(seen[i]==false)
        {
            if(previous>=0)
                currentdistance+=distances[present][i]; // dodaje odleglosc z miasta obecnego do nastepnego
            previous = present;//w kolejnym poziomie rekurencji, poprzednie miasto bedzie obecnym
            present = i; // a miasto do ktorego bede szedl bedzie w kolejnym poziomie rekurencji obecnym
            seen[present]=true; //zaznaczam miasto jako odwiedzone
            copypath += 'A'+present; // dodaje obecne miasto do listy odwiedzonych juz miast
            bruteForce(currentdistance, seen, copypath, present, previous, false); //wejdz do kolejnego miasta
            if(init)//jezeli to pierwsze wywolanie rekurencji
                return;// to nie wchodz w kolejne miasta tylko wyjdz z niej
            copypath = path;//przywroc zmiany
            seen[present] = false;
            present = previous;
            currentdistance -= distances[present][i];
        }
    if(path.length()==cityamount)//jezeli jestes na najnizszym z mozliwych poziomow rekurencji
    {
        copypath += copypath[0];        //dodaje pierwsze miasto do sciezki
        char c = copypath[0];
        currentdistance += distances[present][c-'A'];
        if(currentdistance<shortestdistance) //jezeli ta sciezka jest krotsza od najkrotszej dotychczas znalezionej, zamien wartosc najkrotszej sciezki na krotsza
        {
            shortestdistance=currentdistance;
            shortestpath=copypath;
        }
    }
}
