#include <iostream>
#include "sistemaAstePerno.h"

using namespace std;



int main()
{
    cout << "Sistema formato da 2 aste di dimensioni uguali che possono ruotare ognuna con un proprio centro di rotazione." << endl;
    cout << "Angolo di rotazione dell' asta di base compreso tra i valori 45 - 90." << endl;
    cout << "angolo di rotazione dell' asta di giunzione compreso tra i valori 0 - 90" << endl;
    device *dispositivo = inserisciDati();
    SAP_printDevice(dispositivo);
    menu(dispositivo);
    SAP_disegnaDevice(dispositivo);
    SAP_salvaSVG("");
    /*     SAP_motoAngolo(-angoloBase_rot, -angoloGiunto_rot, dispositivo);
 */
    /* SAP_printDevice(dispositivo); */
    /*     SAP_disegnaDevice(dispositivo);
 */

    return 0;
}