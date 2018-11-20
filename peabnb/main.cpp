#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

int cityamount;                                 // ilosc miast

int **distances;                                // tablica przechowujaca odleglosci miedzy miastami wczytane z pliku

int reduce(int**);                              // redukcja tablicy dystansow
void loadData();                                // wczytywanie danych z pliku

struct Node
{
    int* order;                                                     // tablica przechowujaca kolejnosc dotychczas odwiedzonych miast
    int** reducedMatrix;                                            // tablica 2-wymiarowa na zredukowana macierz
    int cost;                                                       // koszt, dolna granica
    int city;                                                       // okresla jednoznacznie miasto
    int level;                                                      // poziom w 'drzewie', zrobiony domyslnie jako 0;
    Node(){};
    Node(Node*, int);
};

struct comparator                                                   // objekt do porownywania node'ow w kolejce priorytetowej
{
    bool operator()(const Node* first, const Node* second) const
    {
        if(first->cost > second-> cost)
            return true;
        else if(first->cost < second -> cost)
            return false;
        else                                                        // zwraca wynik w postaci bool, porownuje poziomy sciezek, wybiera ten z wiekszym poziomem
            return first->level < second -> level;
    }                                                               // przekazanego node'a jest wiekszy niz drugiego
};

int  main()
{
    int asd = cityamount;                                           // zapisuje w ktorym momencie ma sie odbyc przeszukiwanie wglab i okreslenie ograniczenia gornego0
    loadData();                                                     // wczytywanie danych z pliku
    Node* root = new Node();                                        // utworzenie node'a - roota, czyli pierwszego miasta
    root->city = 0;
    root->reducedMatrix = distances;                                // dla pierwszego miasta oryginalna tablica to ta wczytana z pliku
    root->cost = reduce(distances);                                 // funkcja redukuje tablice jednoczesnie zwracajac koszt redukcji
    root->order = new int[1];                                       // zrobilbym to inaczej w przypadku roota
    root->order[0] = 1;
    root->level = 0;
    std::priority_queue <Node*, std::vector <Node*>, comparator> q; // utworzenie kolejki do przechowywania
                                                                    // najbardziej obiecujacych node'ow w odpowiedniej kolejnosci
    q.push(root);                                                   // w kolejce znajduje sie korzen, czyli pierwsze miasto

    while(!q.empty())                                               // dopoki q nie jest pusta
    {

        Node* best = q.top();                                       // zapisz najbardziej obiecujacego node'a we wskazniku
        q.pop();                                                    // zdejmij go z kolejki
//        int* bsdfafd;
        if(best->level == cityamount - 1)       // jezeli to juz ostatni poziom
            {
                std::cout<<"Koszt sciezki wynosi: "<<best->cost<<", a jej kolejnosc to:\n";
                for(int i=0;i<best->level+1;++i)    // wypisz potrzebne informacje
                    std::cout<<best->order[i]<<" -> ";
                std::cout<<best->order[0]<<"\n\n";

                delete[] best->order;

                for(int i=0;i<cityamount;++i)       // zwolnij pamiec
                    delete[] best->reducedMatrix[i];
                delete[] best->reducedMatrix;

                break;                              // wyjdz z programu
            }
        if(q.size() >= asd)                     // jezeli nadszedl czas sprawdzenia wglab i okreslenia gornego ograniczenia
        {
//            int a = 0; // nie bedzie istniec
//            int* a = new int; // bedzie istniec
//            a = 2;
//            bsdfafd = a;
            std::priority_queue <Node*, std::vector <Node*>, comparator> tempQ; // pomocnicza kolejka
            Node *tempBest = best;              // pomocniczy wskaznik
            while(tempBest->level != (cityamount-1)) // dopoki nie dojdziesz na sam dol
            {
                for(int i=0;i<cityamount;++i)           // dla kazdego nieodwiedzonego miasta
                    if(tempBest->reducedMatrix[tempBest->city][i] < 9999)
                    {
                        Node* child = new Node(tempBest, i); //
                        tempQ.push(child);              // dodaj go do temporary kolejki
                    }
                tempBest = tempQ.top();             // wybierz najbardziej obiecujace ze swoich dzieci,
                std::cout<<"\n\n\nOrder:";
                for(int i=0;i<=tempBest->level;++i)
                            std::cout<<tempBest->order[i]<<"->";
                for(int i=0;i<cityamount;++i)
                {
                    std::cout<<"\n";
                    for(int j=0;j<cityamount;++j)
                        std::cout<<tempBest->reducedMatrix[i][j]<<" ";

                }



                tempQ.pop();
                while(!tempQ.empty())           // wyczysc temporary kolejke
                {
                    q.push(tempQ.top());
                    tempQ.pop();
                }
            }


            int upperBound = best->cost;        // gornym ograniczeniem staje sie koszt najglebszego miasta


            do
            {
                tempBest = q.top();             // zapisz wskazanie na pierwszy element w kolejce
                q.pop();                        // zdejmij go z glownej kolejki
                tempQ.push(tempBest);           // dodaj go do tymczasowej kolejki
            }
            while(tempBest->cost <= upperBound);

            while(!q.empty())                // przywroc zmiany, ale nie dodawaj node'ow, ktore maja koszt wiekszy od upperbounda
            {
                tempQ.push(q.top());
                q.pop();
            }

            while(!tempQ.empty())                    // dopoki kolejka nie bedzie pusta, zwolnij pamiec z niepotrzebnych node'ow
            {
                tempBest = tempQ.top();
                tempQ.pop();
                delete[] tempBest->order;

                for(int i=0;i<cityamount;++i)       // zwolnij pamiec
                    delete[] tempBest->reducedMatrix[i];
                delete[] tempBest->reducedMatrix;
            }
            asd *= 2;
        }

        for(int i=0;i<cityamount;++i)           // dla kazdego nieodwiedzonego miasta
            if(best->reducedMatrix[best->city][i] < 9999)
            {
                Node* child = new Node(best, i); // utworz nowego node'a
                q.push(child);                  // dodaj go do kolejki
            }

        for(int i=0;i<cityamount;++i)           // skoro wszystkie nieodwiedzone miasta sa w kolejce
            delete[] best->reducedMatrix[i];    // usun obecnie rozwazane node'a z pamieci
        delete[] best->reducedMatrix;
        delete[] best->order;
    }
}

Node::Node(Node* prev, int citynumber)
{
    //Node* node = new Node;                      // utworzenie nowego node'a

    level = prev->level+1;                // zapisanie poziomu w drzewie

    order = new int[level+1];       // ustawienie wskaznika na poprzedniego this'a

    for(int i=0;i<level;++i)              // zapisanie w tablicy dotychczas odwiedzonych miast
        order[i] = prev->order[i];

    order[level] = citynumber+1;

    city = citynumber;                    // ustawienie numeru miasta this'a

    reducedMatrix = new int *[cityamount];// utworzenie tablicy

    for(int i=0;i<cityamount;++i)
        reducedMatrix[i]=new int[cityamount];

    for(int i=0;i<cityamount;++i)               // skopiowanie zredukowanej tablicy z prev do this
        for(int j=0;j<cityamount;++j)
            reducedMatrix[i][j] = prev->reducedMatrix[i][j];

    for(int i=0;i<cityamount;++i)               // zabezpieczenie przed powrotem do odwiedzonego miasta
    {
        reducedMatrix[prev->city][i] = 9999;
        reducedMatrix[i][city] = 9999;
    }

    reducedMatrix[city][0] = 9999;

    this->cost = prev->cost + prev->reducedMatrix[prev->city][this->city] + reduce(this->reducedMatrix);
                                                // policzenie kosztu dla this'a
}

int reduce(int** a)                             // funkcja redukujaca tablice odleglosci
{                                               // zwraca rowniez koszt redukcji
    int reducecost = 0;                         // deklaracja kosztu
    int temp;                                   // zmienna pomocnicza
    for(int i=0;i<cityamount;++i)
    {
        temp=9999;
        for(int j=0;j<cityamount;++j)
            if(a[i][j]<temp)
                temp = a[i][j];                 // dla kazdego wiersza znajdz najmniejsza wartosc
        if(temp!=0&&temp!=9999)                 // jezeli komorka w wierszu nie jest 0 ani 9999
        {
            reducecost += temp;                 // dodaj znaleziona wartosc do kosztu redukcji
            for(int j=0;j<cityamount;++j)       // i zredukuj kazda komorke w wierszu o ta wartosc
                if(a[i][j]!=0 && a[i][j]!=9999) // o ile nie jest to 0 badz 9999
                    a[i][j] -= temp;
        }
    }
                                                // analogicznie dla kolumn
    for(int i=0;i<cityamount;++i)
    {
        temp=9999;
        for(int j=0;j<cityamount;++j)
            if(a[j][i]<temp)
                temp = a[j][i];
        if(temp!=0 && temp!=9999)
        {
            reducecost += temp;
            for(int j=0;j<cityamount;++j)
                if(a[j][i]!=0 && a[j][i]!=9999)
                    a[j][i] -= temp;
        }
    }

    return reducecost;                          // zwroc koszt redukcji
}


void loadData()
{
    std::fstream file;
    file.open("1BNB.txt",std::ios::in);
    if(file.good())                             // zabezpieczenie
        file>>cityamount;
    else
        return;
    distances = new int *[cityamount];          // tablica przechowujaca odleglosci miedzy miastami.
    for(int i=0;i<cityamount;++i)               // dwuwymiarowa tablica dynamiczna
        distances[i]=new int[cityamount];
    for(int i=0;i<cityamount;++i)               // zapelnianie tablicy danymi z pliku
        for(int j=0;j<cityamount;++j)
            file>>distances[i][j];
    file.close();
}
