#include "klassa.h"
#include "uczen.h"

using namespace std;

int main()
{
    uczen klasaIIa[25];
    uczen adam(25, "adam\n", "kutas\n", "asd");
    adam.setWiek(25); // nie mozna sie odwolac bezposrednio, bo jest prywatne,
    //natomiast metoda setwiek jest publiczna, jednoczesnie jest
    //metoda tej klasy, wiec ma dostep do pól
    adam.klasa = "asd3"; // mozna sie odwolac bo jest publiczne
    cout << adam.getWiek();
    //cout << adam.klasa;
    asd();
    adam.wyswietl();
    return 0;
}
