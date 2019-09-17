#include <iostream>
#include <conio.h>
#include "bf.h"
#include "bnb.h"
#include "comparator.h"
#include <fstream>

int main()
{
    char choice = 3;
    while(choice!=0)
    {
        std::cout<<"1. Brute Force.\n2. Branch & Bound.\n\n";
        std::cout<<"Twoj wybor:";
        choice = getche();
        std::cout<<"\n";
        switch(choice)
        {
            case '1':
                executeBF();
                break;
            case '2':
                executeBnB();
                break;
            default:
                break;
        }
    }
}

