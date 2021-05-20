#include <iostream>
#include "../libraries/meccPrendiCarta.h"

int main()
{

    // SOLUZIONE CON ARRAY DINAMICO DI PUNTATORI A STRUCT

    meccPrendiCarta **arr; // notare doppio asterisco

    int n = 2;
    arr = new meccPrendiCarta *[n]; // notare asterisco dopo meccPrendiCarta

    /* meccPrendiCarta *d1 = mecPC(100, 10, 30, 30, 60, 60);
    meccPrendiCarta *d2 = mecPC(200, 10, 30, 30, 60, 60); */

    meccPrendiCarta *d1 = datiMecPC();
    meccPrendiCarta *d2 = datiMecPC();

    arr[0] = d1;
    arr[1] = d2;

    for (int i = 0; i < n; i++)
    {
        MecPC_salvaSVG(arr[i], "Machine" + to_string(i));
    }
    // ...

    // elimino un device alla volta
    delete arr[0]; // oppure my_destroy_device(arr[0])  se è definita
    delete arr[1]; // oppure my_destroy_device(arr[1])  se è definita
    // ....

    // poi elimino tutto l'array
    delete[] arr;

    /* int main () 
{
    mecPC(100,10,30,30,60,60);

     meccPrendiCarta * mecPC = datiMecPC();
 
    cout << "CIAO" << endl;*/
    return 0;
}