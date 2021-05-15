#include <iostream>
#include "../libraries/meccPrendiCarta.h"


int main () 
{
    mecPC(100,10,30,30,60,60);

    meccPrendiCarta * mecPC = datiMecPC();

    cout << "CIAO" << endl;
    
    return 0;
}