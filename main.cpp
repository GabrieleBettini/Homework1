#include <iostream>
#include "sistemaAstePerno.h"

using namespace std;

void SAP_printDevice(device *dispositivo)
{   
    cout << "Inserire lunghezza"

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
    device *dispositivo = SAP_device_init(100, 20, 20, 60);

    SAP_printDevice(dispositivo);
    /* SAP_motoAngolo(30, -20, dispositivo);*/
    SAP_printDevice(dispositivo);
    SAP_drawDevice(dispositivo);

    return 0;

}