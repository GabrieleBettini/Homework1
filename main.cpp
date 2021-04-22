#include <iostream>
#include "manovella.h"

using namespace std;

void printDevice(device *dispositivo)
{
    cout << "Angolo base: " << dispositivo->angoloBase << endl;
    cout << "Angolo giunto: " << dispositivo->angoloGiunto << endl;
    cout << "Lunghezza brccio base: " << dispositivo->astaBase.lunghezza << endl;
    cout << "Altezza braccio base: " << dispositivo->astaBase.altezza << endl;
    cout << "Lunghezza brccio giunto: " << dispositivo->astaGiunto.lunghezza << endl;
    cout << "Altezza braccio giunto: " << dispositivo->astaGiunto.altezza << endl;
    cout << "-------------------------------------------------" << endl;
}

int main()
{

    //creazione del dispositivo con misure assegnate
    device *dispositivo = device_init(20, 5, 45, 90);

    printDevice(dispositivo);
    motoAngolo (30, -20, dispositivo);
    printDevice(dispositivo);
    return 0;
}