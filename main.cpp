#include <iostream>
#include "sistemaAstePerno.h"

using namespace std;

void SAP_printDevice(device *dispositivo)
{

    cout << "Angolo base: " << dispositivo->angoloBase << endl;
    cout << "Angolo giunto: " << dispositivo->angoloGiunto << endl;
    cout << "Lunghezza brccio base: " << dispositivo->astaBase.lunghezza << endl;
    cout << "Altezza braccio base: " << dispositivo->astaBase.altezza << endl;
    cout << "Lunghezza brccio giunto: " << dispositivo->astaGiunto.lunghezza << endl;
    cout << "Altezza braccio giunto: " << dispositivo->astaGiunto.altezza << endl;
    cout << "-------------------------------------------------" << endl;
}

device *inserisciDati()
{   
    double lunghezza;
    double altezza;
    float angoloBase_rot;
    float angoloGiunto_rot;

    do
    {
    cout << "Inserire lunghezza bracci:" << endl;
    cin >> lunghezza;
    cout << "Inserire altezza bracci:" << endl;
    cin >> altezza;
    }while (!SAP_controlloAste(lunghezza,altezza));

    do
    {
    cout << "Inserire rotazione angolo di base:" << endl;
    cin >> angoloBase_rot;
    cout << "Inserire rotazione angolo al giunto:" << endl;
    cin >> angoloGiunto_rot;
    } while (!SAP_controlloAngoli(angoloBase_rot,angoloGiunto_rot));
    
    //creazione del dispositivo con misure assegnate
    device *dispositivo = SAP_device_init(lunghezza, altezza, angoloBase_rot, angoloGiunto_rot);
    
    return dispositivo;
}

void menu(device *dispositivo) 
{   

    double lunghezza;
    double altezza;
    float angoloBase_rot;
    float angoloGiunto_rot;
    char scelta;

    do
    {
    SAP_disegnaDevice(dispositivo);
    
    cout << "1. Modifica misura lunghezza aste" <<endl;
    cout << "2. Modifica misura altezza aste" <<endl;
    cout << "3. Modifica angolo di base" <<endl;
    cout << "4. Modifica angolo di giunzione" <<endl;
    cout << "5. Esci" <<endl;
    //aggiungo altre opzioni, ex. sposta angolo base...
    cin >> scelta;

    switch (scelta)
    {
    case '1' :
        cout << "Inserisci nuovo valore lunghezza aste" << endl;
        cin >> lunghezza;
        
        if (SAP_controlloAste(lunghezza, dispositivo->astaBase.altezza)) 
        {
            dispositivo->astaBase.lunghezza = lunghezza;
        }

        break;
    case '2' :
        cout << "Inserisci nuovo valore altezza aste" << endl;
        cin >> altezza;

        if (SAP_controlloAste(dispositivo->astaBase.lunghezza, altezza)) 
        {
            dispositivo->astaBase.altezza = altezza;
        }

        break;
    case '3' :
        cout << "Inserisci nuovo valore angolo di base" << endl;
        cin >> angoloBase_rot;

        if (SAP_controlloAngoli(angoloBase_rot, dispositivo->angoloGiunto))
        {
            dispositivo->angoloBase = angoloBase_rot;
        }

        break;
    case '4' :
        cout << "Inserisci nuovo valore angolo di giunzione" << endl;
        cin >> angoloGiunto_rot;

        if (SAP_controlloAngoli(dispositivo->angoloBase, angoloGiunto_rot))
        {
            dispositivo->angoloGiunto = angoloGiunto_rot; 
        }

        break;
    case '5' :
        delete dispositivo;
        return;
    default :
        cout << "Errore: scelta non contemplata" <<endl;
        break; 
    }
    }while (scelta!='5');
    
}

int main()
{
    cout << "Breve descrizione del programma" <<endl;
    device *dispositivo = inserisciDati();
    menu(dispositivo);

/*     SAP_motoAngolo(-angoloBase_rot, -angoloGiunto_rot, dispositivo);
 */    /*SAP_printDevice(dispositivo);*/
    /* SAP_printDevice(dispositivo); */
/*     SAP_disegnaDevice(dispositivo);
 */
    return 0;
}