#pragma once
struct Node
{
    int* order;                         // tablica przechowujaca kolejnosc dotychczas odwiedzonych miast
    int lowerBound;                     // koszt, dolna granica calego poddrzewa
    int reduce();                       // funckja zwracajaca minimalny koszt przejscia poddrzewa
    int cost;                           // dotychczasowy koszt przejscia
    int level;                          // ilosc miast dotychczas odwiedzonych
    Node(Node* previous, int city);     // konstruktor bazujacy na dotychczasowym koszcie i kolejnosci odwiedzanych miast
    Node();
    ~Node();
    bool isAlreadyInOrder(int city);    // sprawdza, czy dane miasto juz zostalo odwiedzone
};
void executeBnB();
void clearQueueAndFreeMemory();
void bnbloadData();
void greedyAlgorithm(Node*);
