#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <ctime>
#include "bnb.h"
#include "comparator.h"
#include "main.h"

/*
1. BNB polega na odcinaniu rozwiazan/galezi, ktore na pewno nie zawieraja poprawnego rozwiazania.
Aby okreslic, czy galaz nalezy odciac czy rozwijac, nalezy porownac dolne ograniczenie galezi
z obecnym gornym ograniczeniem calego problemu.

Aby okreslic pierwsze dolne ograniczenie dla calego drzewa (korzenia) wystarczy zsumowac
najmniejsze koszty przejscia miedzy miastami.

Pierwsze gorne ograniczenie mozna okreslic poprzez pojscie metoda zachlanna wglab drzewa, kazde kolejne
poprzez osiagniecie liscia, wrocenie do miasta poczatkowego i wyliczenie kosztu przejscia sciezki.

Dolna granica == koszt dotychczasowy sciezki + najmniejszy mozliwy koszt ktory mozemy poniesc,
czyli koszt wyjscia z ostatniego miasta i wszystkich nieodwiedzonych


1. Dodac korzen.
2. Co jakis czas pojsc greedy algorytmem, wyrzucic z kolejki (i zwolnic pamiec) wszystko co ma za duza granice dolna.
3. Dodac wszystkie mozliwe sciezki, jezeli ich koszt nie jest wiekszy od gornej granicy
4. Jezeli przypadkiem doszedlem juz na sam dol, to update na granice gorna, znowu wyczyscic kolejke z niezawierajacych rozwiazania
5. Jak kolejka pusta to koniec.
*/

int bnbcityamount;                                  // ilosc miast
std::priority_queue <Node*, std::vector <Node*>, comparator> q; // utworzenie kolejki do przechowywania
int **bnbdistances;                                 // tablica przechowujaca odleglosci miedzy miastami wczytane z pliku
int upperBound = INT_MAX;
Node::Node(){};
Node::~Node()
{
    delete[] order;
}

Node::reduce()
{
    if(level == bnbcityamount) // jezeli jestesmy na samym koncu, koszt redukcji to koszt podrozy z miasta koncowego do miasta poczatkowego
    {
        return bnbdistances[order[level-1]][0];
    }
    else if (level == bnbcityamount-1) // jezeli zostalo jedno miasto do odwiedzenia, to zwrocmy koszt pojscia do niego i wrocenia do miasta poczatkowego
    {
        int nextCity = 0;
        for(;nextCity<bnbcityamount;++nextCity)
            if(!isAlreadyInOrder(nextCity))//jezeli miasta jeszcze nie odwiedzilismy
                break;
        return bnbdistances[order[level-1]][nextCity] + bnbdistances[nextCity][0];
    }
    else
    {
        //trzeba policzyc minimalne koszty wyjscia i wejscia do i z kazdego z wierzcholkow.
        //ostatni odwiedzony nie moze pojsc do pierwszego, bo zamkneloby to cykl, ale kazdy inny juz moze(ktorys musi)
        //wejsc do nieodwiedzonych mozemy tylko z nieodwiedzonych, a do miasta pierwszego z kazdego ale nie z ostatniego dotychczasowego
        int* notVisited = new int[bnbcityamount - level + 1];
        int licznik = 0;
        for(int i=0;i<bnbcityamount;++i)
            if(!isAlreadyInOrder(i))
            {
                notVisited[licznik] = i;
                ++licznik;
            }
        int temp = INT_MAX;
        for (int i=0;i<licznik;++i)
            if(bnbdistances[order[level-1]][notVisited[i]]<temp)
                temp = bnbdistances[order[level-1]][notVisited[i]];
        int reducecost = temp;                  // w tym momencie mamy koszt wyjscia z ostatniego miasta do nieodwiedzonych node'ow
        notVisited[bnbcityamount - level] = 0;  // do tablicy przechowujaca nieodwiedzone node'y
        ++licznik;                              //dodajemy pierwsze miasto i liczymy granice dla kazdego z nich
        for(int i=0;i<licznik-1;++i)
        {
            temp = INT_MAX;
            for(int j=0;j<licznik;++j)
                if(notVisited[i]!=notVisited[j]&&notVisited[i]!=0)
                    if(bnbdistances[notVisited[i]][notVisited[j]]<temp)
                        temp = bnbdistances[notVisited[i]][notVisited[j]];
            reducecost+=temp;
        }
        delete[] notVisited;
        return reducecost;
    }
}

void clearQueueAndFreeMemory()
{
    Node **temp = new Node*[q.size()];
    int licznik = 0;
    temp[licznik] = q.top();
    while(licznik<q.size()&&temp[licznik]->lowerBound <= upperBound)
    {
        q.pop();
        ++licznik;
        temp[licznik] = q.top();
    }
    while(!q.empty())
    {
        Node* tempp = q.top();
        q.pop();
        delete tempp;
    }
    for(int i=0;i<licznik-1;++i)
        q.push(temp[i]);
    delete[] temp;
}

void greedyAlgorithm(Node* top)
{
    Node* temp = new Node;
    temp->level = top->level;
    temp->cost = top->cost;
    temp->order = new int[bnbcityamount];
    for (int i=0;i<top->level;++i)
        temp->order[i] = top->order[i];
    for (int i=0;i<bnbcityamount - top->level;++i) // znajdz tyle miast ilu jeszcze nie odwiedziles
    {
        int city = 0;
        int tempcost = INT_MAX;
        for (int j=0;j<bnbcityamount;++j)
            if(!temp->isAlreadyInOrder(j) && bnbdistances[temp->order[temp->level-1]][j] < tempcost)
            {
                tempcost = bnbdistances[temp->order[temp->level-1]][j];
                city = j;
            }
        temp->cost += bnbdistances[temp->order[temp->level - 1]][city];
        temp->order[temp->level] = city;
        ++temp->level;
    }
    temp->cost += bnbdistances[temp->order[temp->level-1]][0];
    if(temp->cost < upperBound)
    {
        upperBound = temp->cost;
        clearQueueAndFreeMemory();
    }
    delete temp;
}

void executeBnB()
{
    upperBound = INT_MAX;
    bnbloadData();
    Node* root = new Node;                          // utworzenie node'a - roota, czyli pierwszego miasta
    root->order = new int[1];
    root->order[0] = 0;
    root->level = 1;
    root->cost = 0;
    root->lowerBound = root->reduce();
    std::clock_t start;                             // licz czas
    double duration;
    start = std::clock();
    q.push(root);                                   // w kolejce znajduje sie korzen, czyli pierwsze miasto
    long licznik = 0;
    while(!q.empty())                               // dopoki q nie jest pusta
    {
        Node* top = q.top();                        // zapisz node'a we wskazniku
        q.pop();                                    // zdejmij go z kolejki
        if(top->level == bnbcityamount+1)
        {
            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
            std::cout<<"Najkrotsza droga przez wszystkie miasta to: ";
            for(int i=0;i<top->level-1;++i)        // wypisz potrzebne informacje
                std::cout<<char('A'+top->order[i])<<" -> ";
            std::cout<<char('A'+top->order[0])<<"\n";
            std::cout<<"Jej calkowity dystans wynosi:"<<top->cost<<'\n';
            std::cout << "Czas: "<< duration << " sekund.\n\n";
            delete top;
            while(!q.empty())
            {
                top = q.top();
                q.pop();
                delete top;
            }
            for(int i=0;i<bnbcityamount;++i)
                delete[] bnbdistances[i];
            delete[] bnbdistances;
            break;
        }
        else if(top->level == bnbcityamount)
        {
            top->cost += bnbdistances[top->order[top->level-1]][0];
            if(top->cost < upperBound)
            {
                upperBound = top->cost;
                clearQueueAndFreeMemory();
            }
            ++top->level;
            q.push(top);
            continue;
        }
        if(licznik % bnbcityamount == 0) // co jakis czas zapusc greedy algorithm
            greedyAlgorithm(top);
        for(int i=1;i<bnbcityamount;++i) // zawsze pomijaj pierwsze miasto bo od niego zaczynamy
            if(!top->isAlreadyInOrder(i)) // jezeli miasta jeszcze nie ma
            {
                Node* temp = new Node(top,i); // pojdz do niego
                if(temp->lowerBound <= upperBound) // jezeli warto
                    q.push(temp); // to dodaj go do kolejki
                else // a jak nie
                    delete temp; // to zwolnij po nim pamiec
            }
        delete top; // zwolnij pamiec po rozwazonym juz nodzie
        ++licznik;
    }
}

Node::Node(Node* previous, int city) // parametry to rodzic oraz miasto do ktorego wlasnie wchodzimy tworzac tego node'a
{
    level = previous->level + 1; // ilosc dot. odwiedzonych miast
    order = new int[level]; // tablica przechowujaca sciezke, bazujaca na rodzicu
    for(int i=0; i<level-1;++i)
        order[i] = previous->order[i];
    order[level-1] = city;
    cost = previous->cost + bnbdistances[order[level - 2]][city]; // koszt dotychczasowej sciezki
    lowerBound = cost + reduce();// dolne ograniczenie dla node'a to obecny koszt + minimalny koszt przejscia pozostalych miast i powrotu do miasta poczatkowego
}

bool Node::isAlreadyInOrder(int city) // metoda sprawdza czy zadane miasto zostalo juz odwiedzone
{
    for (int i=0;i<level;++i)
        if(city==order[i])
            return true;
    return false;
}

void bnbloadData()                             // wczytywanie danych z pliku do zmiennych
{
    std::fstream file;
    std::string fileName;
    std::cout<<"Podaj nazwe pliku:";
    std::cin>>fileName;
    file.open(fileName,std::ios::in);
    if(file.good())
        file>>bnbcityamount;
    else
        return;
    bnbdistances = new int *[bnbcityamount];
    for(int i=0;i<bnbcityamount;++i)
        bnbdistances[i]=new int[bnbcityamount];
    for(int i=0;i<bnbcityamount;++i)
        for(int j=0;j<bnbcityamount;++j)
            file>>bnbdistances[i][j];
    file.close();
}
