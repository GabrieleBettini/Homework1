#include "sistemaAstePerno.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <math.h>

#define PI 3.14159

using namespace std;

// inizializzazione di un asta
asta *SAP_asta_init(double lunghezza, double altezza)
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
    brc->x = altezza/2;
    brc->y = lunghezza-altezza;
    
    return brc;
}

device *SAP_device_init(double diml, double dimh, float angBase, float angGiunto)
{
    //creazione braccio richiamando la funzione di inizializzazione dell'asta
    //i due bracci di dimensioni uguali
    asta *braccioBase = SAP_asta_init(diml, dimh);
    asta *braccioGiunto = SAP_asta_init(diml, dimh);

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
void SAP_motoAngolo(float angBase, float angGiunto, device *puntatoreDispositivo)
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

void SAP_drawDevice(device *dispositivo) 
{
    string SVG = "";
    SVG += "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    SVG += "<g>\n<title>Sistema 2 aste con perno</title>\n";
    double angBase = 90-dispositivo->angoloBase;
    double angGiunto = -dispositivo->angoloGiunto;

    double altezza = dispositivo->astaBase.altezza;
    double lunghezza = dispositivo->astaBase.lunghezza;
    double x_base = altezza/2;
    double y_base = lunghezza - x_base;

    double centroSVGx = 400;
    double centroSVGy = 300;
    double x_giunto = centroSVGx + (cos(angBase*PI/180)*dispositivo->astaGiunto.lunghezza)-dispositivo->astaGiunto.altezza;
    double y_giunto = abs((sin(angBase*PI/180)*dispositivo->astaGiunto.lunghezza)-dispositivo->astaGiunto.altezza);

    SVG += "<rect transform=\"translate("+to_string(centroSVGx)+","+to_string(centroSVGy)+")rotate("+ to_string(angBase)+","+ to_string(x_base)+",";
    SVG += to_string(y_base)+")\" id=\"svg_1\" height=\""+to_string(lunghezza)+"\" width=\""+to_string(altezza);
    SVG += "\" y=\"0\" x=\"0\" stroke=\"#000\" fill=\"#fff\"/>\n";
    SVG += "<rect transform=\"translate("+to_string(x_giunto)+","+to_string(y_giunto)+")rotate("+ to_string(angGiunto)+","+ to_string(x_base)+",";
    SVG += to_string(y_base)+")\" id=\"svg_2\" height=\""+to_string(lunghezza)+"\" width=\""+to_string(altezza);
    SVG += "\" y=\"0\" x=\"0\" stroke=\"#000\" fill=\"#fff\"/>\n";
    
    SVG += "</g>\n</svg>\n";

    

    cout << SVG << endl;

    cout << x_giunto << endl;

    cout << 90-dispositivo->angoloBase <<endl;
}