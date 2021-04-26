#include "sistemaAstePerno.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

// inizializzazione di un asta


bool SAP_controlloAste (double lunghezza, double altezza) 
{
     //controllo dimensioni
    if (altezza >= lunghezza)
    {
        cout << "Errore l'altezza dell'asta non può essere superiore alla lunghezza" << endl;
        return false;
    }
    return true;
}

bool SAP_controlloAngoli (float angBase, float angGiunto) {
    if (angBase > 90 || angBase < 45)
    {
        cout << "Errore: l'angolo base deve essere compreso tra 45 e 90 gradi" << endl;
        return false;
    }
    if (angGiunto < 0 || angGiunto > 90)
    {
        cout << "Errore: l'angolo di giunzione deve essere compreso tra 0 e 90 gradi" << endl;
        return false;
    }
    return true;

}

asta *SAP_asta_init(double lunghezza, double altezza)
{
    
    if (!SAP_controlloAste(lunghezza, altezza)) {
        return NULL;
    }

    asta *brc = new asta; //alloco memoria

    brc->lunghezza = lunghezza;
    brc->altezza = altezza;
    brc->x = altezza / 2;
    brc->y = lunghezza - altezza;

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

    //posso togliere il controllo per far muovere completamente le 2 aste rispetto al centro di rotazione
    if (!SAP_controlloAngoli(angBase,angGiunto))
    {
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
    
    float sommaAngGiunto = angGiunto + puntatoreDispositivo->angoloGiunto;
    
    if (SAP_controlloAngoli(sommaAngBase, sommaAngGiunto)) {

    puntatoreDispositivo->angoloBase = sommaAngBase;
    puntatoreDispositivo->angoloGiunto = sommaAngGiunto;
    
    }

}

//salvataggio SVG in un file
void SAP_salvaSVG(string SVG)
{

    ofstream sistemaAstePerno("sistemaAstePerno.svg");
    if (!sistemaAstePerno)
    {
        cout << "Errore: non è stato possibile aprire il file corretto.";
        return;
    }

    sistemaAstePerno << SVG;
    sistemaAstePerno.close();
}


void SAP_disegnaDevice(device *dispositivo)
{
    double canvasW = 800;
    double canvasH = 600;
    string SVG = "";
    SVG += "<svg width=\"" + to_string(canvasW) + "\" height=\"" + to_string(canvasH) + "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    SVG += "<g>\n<title>Sistema 2 aste con perno</title>\n";
    double angBase = 90 - dispositivo->angoloBase;
    double angGiunto = -dispositivo->angoloGiunto;

    double altezza = dispositivo->astaBase.altezza;
    double lunghezza = dispositivo->astaBase.lunghezza;
    double x_base = altezza / 2;
    double y_base = lunghezza - x_base;

    double centroSVGx = canvasW / 2;
    double centroSVGy = canvasH / 2;
    double x_giunto = centroSVGx + (sin(angBase * M_PI / 180) * dispositivo->astaGiunto.lunghezza) - sin(angBase * M_PI / 180) * dispositivo->astaGiunto.altezza;
    double y_giunto = canvasH - ((centroSVGy + (cos(angBase * M_PI / 180) * dispositivo->astaGiunto.lunghezza) - dispositivo->astaBase.lunghezza)) - (sin(angBase * M_PI / 180) * dispositivo->astaGiunto.altezza / (1 + cos(angBase * M_PI / 180)));

    SVG += "<rect transform=\"translate(" + to_string(centroSVGx) + "," + to_string(centroSVGy) + ")rotate(" + to_string(angBase) + "," + to_string(x_base) + ",";
    SVG += to_string(y_base) + ")\" id=\"svg_1\" height=\"" + to_string(lunghezza) + "\" width=\"" + to_string(altezza);
    SVG += "\" y=\"0\" x=\"0\" stroke=\"#000\" fill=\"red\"/>\n";
    SVG += "<rect transform=\"translate(" + to_string(x_giunto) + "," + to_string(y_giunto) + ")rotate(" + to_string(angGiunto) + "," + to_string(x_base) + ",";
    SVG += to_string(x_base) + ")\" id=\"svg_2\" height=\"" + to_string(lunghezza) + "\" width=\"" + to_string(altezza);
    SVG += "\" y=\"0\" x=\"0\" stroke=\"#000\" fill=\"green\" style=\"fill-opacity: 0.5\"/>\n";

    SVG += "</g>\n</svg>\n";
    SAP_parse(SVG);
    SAP_salvaSVG(SVG);
}

//dato SVG questa funzione prende la sotto-stringa che parte da transform fino ad un valore.
string SAP_estraiValore(string svg, string startingValue, string endingValue)
{
    size_t find1 = svg.find(startingValue) + startingValue.size();
    size_t find2 = svg.find(endingValue, find1);
    string element = svg.substr(find1, find2 - find1);
    return element;
}

device *SAP_parse(string SVG)
{

    double angBase, angGiunto, lunghezza, altezza;
    string astaBase = SAP_estraiValore(SVG, "<rect ", "/>");
    SVG = SVG.replace(SVG.find("<rect "), sizeof(astaBase), astaBase);
    string astaGiunto = SAP_estraiValore(SVG, "<rect ", "/>");

    angBase = 90 - stod(SAP_estraiValore(astaBase, "rotate(", ","));
    lunghezza = stod(SAP_estraiValore(astaBase, "height=\"", "\""));
    altezza = stod(SAP_estraiValore(astaBase, "width=\"", "\""));

    angGiunto = -stod(SAP_estraiValore(astaGiunto, "rotate(", ","));

    //ci andranno in controlli degli angoli all'interno dei limiti imposti
    //-------------------------------------------------------------------------------
    if (angBase > 90 || angBase < 45)
    {
        cout << "Errore: l'angolo base deve essere compreso tra 45 e 90 gradi" << endl;
        return NULL;
    }
    else if (angGiunto<0, angGiunto> 90)
    {
        cout << "Errore: l'angolo di giunzione deve essere compreso tra 0 e 90 gradi" << endl;
        return NULL;
    }
    //-------------------------------------------------------------------------------

    return SAP_device_init(lunghezza, altezza, angBase, angGiunto);
}