#include "manovella.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

using namespace std;

// inizializzazione di un asta
asta *asta_init(double lunghezza, double altezza)
{
    //controllo dimensioni
    if (altezza > lunghezza)
    {
        cout << "Errore l'altezza dell'asta non può essere superiore alla lunghezza" << endl;
        return NULL;
    }

    asta *brc = new asta; //alloco memoria

    brc->lunghezza = lunghezza;
    brc->altezza = altezza;
    return brc;
}

device *device_init(double diml, double dimh, float angBase, float angGiunto)
{
    //creazione braccio richiamando la funzione di inizializzazione dell'asta
    //i due bracci di dimensioni uguali
    asta *braccioBase = asta_init(diml, dimh);
    asta *braccioGiunto = asta_init(diml, dimh);

    //controllo se braccio base e giunto siano stati creati o che non ci sia stato errore
    if (braccioBase == NULL || braccioGiunto == NULL)
    {
        return NULL;
    }

    if (angBase > 90 || angBase < 45)
    {
        cout << "Errore: l'angolo base deve essere compreso tra 45 e 90 gradi" << endl;
        return NULL;
    }
    if (angGiunto < 0 || angGiunto > 90)
    {
        cout << "Errore: l'angolo di giunzione deve essere compreso tra 0 e 90 gradi" << endl;
        return NULL;
    }
    //alloco memoria per dispositivo
    device *dispositivo = new device;
    //inizializzo il device
    dispositivo->angoloBase = angBase;
    dispositivo->angoloGiunto = angGiunto;
    dispositivo->astaBase = *braccioBase;
    dispositivo->astaGiunto = *braccioGiunto;

    return dispositivo;
}

//modifica angoli aste
void motoAngolo(float angBase, float angGiunto, device *puntatoreDispositivo)
{
    float sommaAngBase = angBase + puntatoreDispositivo->angoloBase;
    if (sommaAngBase > 90 || sommaAngBase < 45)
    {
        cout << "Errore: l'angolo base deve essere compreso tra 45 e 90 gradi" << endl;
        return;
    }
    float sommaAngGiunto = angGiunto + puntatoreDispositivo->angoloGiunto;
    if (sommaAngGiunto < 0 || sommaAngGiunto > 90)
    {
        cout << "Errore: l'angolo di giunzione deve essere compreso tra 0 e 90 gradi" << endl;
        return;
    }
    puntatoreDispositivo->angoloBase = sommaAngBase;
    puntatoreDispositivo->angoloGiunto = sommaAngGiunto;
}