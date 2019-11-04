#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

int bfcityamount;                           // ilosc miast
int **bfdistances;                          // tablica przechowujaca odleglosci miedzy miastami
int shortestdistance;                       // najkrotsza dotychczasowo odnaleziona odleglosc
int *shortestpath;                          // najkrotsza dotychczasowo odnaleziona sciezka
std::chrono::duration<double> diff = std::chrono::nanoseconds{0};

void loadData()                             // wczytywanie danych z pliku do zmiennych
{
    std::fstream file;
    std::string fileName;
    std::cout<<"Podaj nazwe pliku:";
    std::cin>>fileName;
    file.open(fileName,std::ios::in);
    if(file.good())
        file>>bfcityamount;
    else
        return;
    bfdistances = new int *[bfcityamount];
    shortestpath = new int [bfcityamount+1];
    for(int i=0;i<bfcityamount;++i)
        bfdistances[i]=new int[bfcityamount];
    for(int i=0;i<bfcityamount;++i)
        for(int j=0;j<bfcityamount;++j)
            file>>bfdistances[i][j];
    file.close();
}

void bruteForce(int* sequence, int* city, int visited)
{                                           // mozna by w tym miejscu sprawdzic dotychczasow¹ d³ugosc sciezki,
                                            // jezeli przekracza najkrotsze rozwi¹zanie to nie rozwijac tej œciezki.
    ++visited;                              // zwieksz licznik odwiedzonych miast
    if(visited < bfcityamount)              // jezeli nie odwiedzone wszystkie miasta
        for (int i=0; i<bfcityamount;++i)
            if(city[i] == 0)            // to odwiedz kolejne
            {
                city[i] = 1;
                sequence[visited] = i;
                bruteForce(sequence, city, visited);
                city[i] = 0;            // zaznacz z powrotem jako nieodwiedzone
            }                               // licznik w petli gwarantuje ze dwa razy ta sama droga
                                            // rekurencja nie pojdzie
    if(visited == bfcityamount)             // jezeli odwiedziles wszystkie miasta
    {
        int distance = 0;
        for (int i=0; i<bfcityamount-1;++i) //dodaj odleglosci
            distance += bfdistances[sequence[i]][sequence[i+1]];
        distance += bfdistances[sequence[bfcityamount-1]][0];//wroc do startowego miasta
        if(distance<shortestdistance)       // jezeli znaleziona odleglosc jest krotsza od dotychczasowo najkrotszej
        {                                   //zamien wartosc i sciezke
            shortestdistance = distance;
            for(int i=0;i<bfcityamount;++i)
                shortestpath[i] = sequence[i];
        }
    }
}

void executeBF()
{
    shortestdistance = INT_MAX;
    loadData();
    int* sequence = new int[bfcityamount+1];// tablica z kolejnoscia dotychczasowo odwiedzonych miast
    int* city = new int[bfcityamount];    // tablica z dotychczasowo odwiedzonymi miastami
    for (int i=0;i<bfcityamount+1;++i)
    {
        sequence[i]=0;
        city[i] = 0;
    }
    city[0] = 1;                         // zacznij od pierwszego miasta
    std::clock_t start;                     // licz czas
    double duration;
    start = std::clock();
    bruteForce(sequence, city, 0);          // wywolanie rekurencji
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    shortestpath[bfcityamount] = 0;
    std::cout<<"Najkrotsza droga przez wszystkie miasta to: ";
    for(int i=0;i<bfcityamount;++i)
        std::cout<<shortestpath[i]<<" -> ";
    std::cout<<shortestpath[bfcityamount];
    std::cout<<'\n';
    std::cout<<"Jej calkowity dystans wynosi: "<<shortestdistance<<'\n';
    std::cout << "Czas: "<< duration << " sekund.\n\n";
    for (int i=0;i<bfcityamount;++i)
        delete[] bfdistances[i];
    delete[] bfdistances;
    delete[] shortestpath;
    delete[] sequence;
    delete[] city;
}

void executeBFPomiar()
{
    shortestdistance = INT_MAX;
    int* sequence = new int[bfcityamount+1];// tablica z kolejnoscia dotychczasowo odwiedzonych miast
    int* city = new int[bfcityamount];    // tablica z dotychczasowo odwiedzonymi miastami
    for (int i=0;i<bfcityamount+1;++i)
    {
        sequence[i]=0;
        city[i] = 0;
    }
    city[0] = 1;                         // zacznij od pierwszego miasta
    auto t1 = std::chrono::high_resolution_clock::now();
    bruteForce(sequence, city, 0);          // wywolanie rekurencji
    auto t2 = std::chrono::high_resolution_clock::now();
    diff += t2-t1;
    for (int i=0;i<bfcityamount;++i)
        delete[] bfdistances[i];
    delete[] bfdistances;
    delete[] shortestpath;
    delete[] sequence;
    delete[] city;
}

void pomiar()
{
    loadData();
    int ilepomiarow = 100;
    for(int i=0;i<ilepomiarow;++i)
        executeBFPomiar();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count()/ilepomiarow<<'\n';
}
