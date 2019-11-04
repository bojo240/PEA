#include <iostream>
#include <conio.h>
#include "bf.h"
#include "bnb.h"
#include "comparator.h"
#include <fstream>

//program napisany w standardzie -std=c++11

int main()
{
    char choice = 3;
    while(choice!=0)
    {
        std::cout<<"1. Brute Force.\n2. Branch & Bound.\n3. Pomiar BF.\n4. Pomiar BNB.\n5. Koniec.\n\n";
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
            case '3':
                pomiar();
                break;

            case '5':
                return 0;


            default:
                break;
        }
    }
    getch();
}

