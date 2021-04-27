#include <iostream>
#include "../libraries/sistemaAstePerno.h"

using namespace std;



int main()
{
    cout << "Sistema formato da 2 aste di dimensioni uguali che possono ruotare ognuna con un proprio centro di rotazione." << endl;
    cout << "Angolo di rotazione dell' asta di base compreso tra i valori 0 - 360." << endl;
    cout << "angolo di rotazione dell' asta di giunzione compreso tra i valori 0 - 360" << endl << endl;
    device *dispositivo = SAP_inserisciDatiMenu();
    SAP_stampaDatiDevice(dispositivo);
    SAP_menu(dispositivo);
    

    return 0;
}