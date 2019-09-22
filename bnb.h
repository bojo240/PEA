#pragma once

struct Node
{
    int* order;                                     // tablica przechowujaca kolejnosc dotychczas odwiedzonych miast
    int** reducedMatrix;                            // tablica 2-wymiarowa na zredukowana macierz
    int cost;                                       // koszt, dolna granica
    int city;                                       // okresla jednoznacznie miasto
    int level;                                      // poziom w 'drzewie', zrobiony domyslnie jako 0;
};

void executeBnB();

void bnbloadData();
