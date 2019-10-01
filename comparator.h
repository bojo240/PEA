#pragma once
#include "bnb.h"

struct comparator                                   // objekt do porownywania node'ow w kolejce priorytetowej
{
    bool operator()(const Node* first, const Node* second) const
    {
        return first->lowerBound > second->lowerBound;          // zwraca wynik w postaci bool, porownuje czy koszt pierwszego
    }                                               // przekazanego node'a jest wiekszy niz drugiego
};

