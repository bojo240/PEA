#pragma once
#include "bnb.h"

struct comparator                                   // objekt do porownywania node'ow w kolejce priorytetowej
{
    bool operator()(const Node* first, const Node* second) const
    {
        if(first->lowerBound != second->lowerBound)
            return first->lowerBound > second->lowerBound;          // zwraca wynik w postaci bool, porownuje czy koszt pierwszego
        else
            return first->level < second->level;
    }                         // przekazanego node'a jest wiekszy niz drugiego, dzieki temu jest w stanie ustalic kolejnosc

};

