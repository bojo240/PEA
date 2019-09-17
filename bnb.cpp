#include <iostream>
#include <queue>
#include <vector>
#include "bnb.h"
#include "comparator.h"
#include "main.h"

int bnbcityamount;                                  // ilosc miast

int **bnbdistances;                                 // tablica przechowujaca odleglosci miedzy miastami wczytane z pliku

int reduce(int**);                                  // redukcja tablicy dystansow

//----------------------------------------------------------------------------------------------------------------------------A moze by tak z tego
Node* newNode(Node*, int);                          // funkcja tworzaca nowego node'a
//----------------------------------------------------------------------------------------------------------------------------konstruktor zrobic?

void executeBnB()
{
    loadData();          // wczytywanie danych z pliku
    Node* root = new Node;                          // utworzenie node'a - roota, czyli pierwszego miasta
    root->city = 0;
    root->reducedMatrix = bnbdistances;             // dla pierwszego miasta oryginalna tablica to ta wczytana z pliku
    root->cost = reduce(bnbdistances);              // funkcja redukuje tablice jednoczesnie zwracajac koszt redukcji
    root->order = new int[1];
    root->order[0] = 1;
    root->level = 0;

    std::priority_queue <Node*, std::vector <Node*>, comparator> q; // utworzenie kolejki do przechowywania
                                                    // najbardziej obiecujacych node'ow w odpowiedniej kolejnosci
    q.push(root);                                   // w kolejce znajduje sie korzen, czyli pierwsze miasto

    while(!q.empty())                               // dopoki q nie jest pusta
    {
        Node* best = q.top();                       // zapisz node'a we wskazniku
        q.pop();                                    // zdejmij go z kolejki
        if(best->level == bnbcityamount - 1)        // jezeli to juz ostatni poziom
        {
            std::cout<<"Koszt sciezki wynosi: "<<best->cost<<", a jej kolejnosc to:\n";
            for(int i=0;i<best->level+1;++i)        // wypisz potrzebne informacje
                std::cout<<best->order[i]<<" -> ";
            std::cout<<best->order[0]<<"\n\n";
            for(int i=0;i<bnbcityamount;++i)        // zwolnij pamiec
                delete[] best->reducedMatrix[i];
            delete[] best->reducedMatrix;
            delete[] best->order;
            break;                                  // wyjdz z programu
        }

        for(int i=0;i<bnbcityamount;++i)            // dla kazdego nieodwiedzonego miasta
            if(best->reducedMatrix[best->city][i] < 9999)
            {
                Node* child = newNode(best, i);     // utworz nowego node'a
                q.push(child);                      // dodaj go do kolejki
            }

        for(int i=0;i<bnbcityamount;++i)            // skoro wszystkie nieodwiedzone miasta sa w kolejce
            delete[] best->reducedMatrix[i];        // usun obecnie rozwazane node'a z pamieci
        delete[] best->reducedMatrix;
        delete[] best->order;
    }
}

Node* newNode(Node* prev, int citynumber)
{
    Node* node = new Node;                          // utworzenie nowego node'a

    node->level = prev->level+1;                    // zapisanie poziomu w drzewie

    node->order = new int[node->level+1];           // ustawienie wskaznika na poprzedniego node'a

    for(int i=0;i<node->level;++i)                  // zapisanie w tablicy dotychczas odwiedzonych miast
        node->order[i] = prev->order[i];
    node->order[node->level] = citynumber+1;

    node->city = citynumber;                        // ustawienie numeru miasta node'a

    node->reducedMatrix = new int *[bnbcityamount]; // utworzenie tablicy

    for(int i=0;i<bnbcityamount;++i)
        node->reducedMatrix[i]=new int[bnbcityamount];

    for(int i=0;i<bnbcityamount;++i)                // skopiowanie zredukowanej tablicy z prev do node
        for(int j=0;j<bnbcityamount;++j)
            node->reducedMatrix[i][j] = prev->reducedMatrix[i][j];

    for(int i=0;i<bnbcityamount;++i)                // zabezpieczenie przed powrotem do odwiedzonego miasta
    {
        node->reducedMatrix[prev->city][i] = 9999;
        node->reducedMatrix[i][node->city] = 9999;
    }

    node->reducedMatrix[node->city][0] = 9999;

    node->cost = prev->cost + prev->reducedMatrix[prev->city][node->city] + reduce(node->reducedMatrix);
                                                    // policzenie kosztu dla node'a
    return node;
}

int reduce(int** a)                                 // funkcja redukujaca tablice odleglosci
{                                                   // zwraca rowniez koszt redukcji
    int reducecost = 0;                             // deklaracja kosztu
    int temp;                                       // zmienna pomocnicza
    for(int i=0;i<bnbcityamount;++i)
    {
        temp=9999;
        for(int j=0;j<bnbcityamount;++j)
            if(a[i][j]<temp)
                temp = a[i][j];                     // dla kazdego wiersza znajdz najmniejsza wartosc
        if(temp!=0&&temp!=9999)                     // jezeli komorka w wierszu nie jest 0 ani 9999
        {
            reducecost += temp;                     // dodaj znaleziona wartosc do kosztu redukcji
            for(int j=0;j<bnbcityamount;++j)        // i zredukuj kazda komorke w wierszu o ta wartosc
                if(a[i][j]!=0 && a[i][j]!=9999)     // o ile nie jest to 0 badz 9999
                    a[i][j] -= temp;
        }
    }
                                                    // analogicznie dla kolumn
    for(int i=0;i<bnbcityamount;++i)
    {
        temp=9999;
        for(int j=0;j<bnbcityamount;++j)
            if(a[j][i]<temp)
                temp = a[j][i];
        if(temp!=0 && temp!=9999)
        {
            reducecost += temp;
            for(int j=0;j<bnbcityamount;++j)
                if(a[j][i]!=0 && a[j][i]!=9999)
                    a[j][i] -= temp;
        }
    }

    return reducecost;                              // zwroc koszt redukcji
}
