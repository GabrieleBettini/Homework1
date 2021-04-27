#include "sistemaAstePerno.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

double canvasWidth = 1200;
double canvasHeight = 800;

void SAP_stampaDatiDevice(device *dispositivo)
{
    cout << "-------------------------------------------------" << endl;
    cout << "Larghezza del canvas: " << canvasWidth << endl;
    cout << "Altezza del canvas: " << canvasWidth << endl;
    cout << "Posizione X iniziale dispositivo: " << dispositivo->astaBase.posizioneX << endl;
    cout << "Posizione Y iniziale dispositivo: " << dispositivo->astaBase.posizioneY << endl;
    cout << "Lunghezza brccio base: " << dispositivo->astaBase.lunghezza << endl;
    cout << "Altezza braccio base: " << dispositivo->astaBase.altezza << endl;
    cout << "Angolo base: " << dispositivo->angoloBase << endl;
    cout << "Lunghezza brccio giunto: " << dispositivo->astaGiunto.lunghezza << endl;
    cout << "Altezza braccio giunto: " << dispositivo->astaGiunto.altezza << endl;
    cout << "Angolo giunto: " << dispositivo->angoloGiunto << endl;
    cout << "-------------------------------------------------" << endl;
}

//modifica angoli aste
//funzione non utilizzata nel mio device
void SAP_motoAngolo(float angBase, float angGiunto, device *puntatoreDispositivo)
{
    float sommaAngBase = angBase + puntatoreDispositivo->angoloBase;

    float sommaAngGiunto = angGiunto + puntatoreDispositivo->angoloGiunto;

    if (SAP_controlloAngoli(sommaAngBase, sommaAngGiunto))
    {

        puntatoreDispositivo->angoloBase = sommaAngBase;
        puntatoreDispositivo->angoloGiunto = sommaAngGiunto;
    }
}

void SAP_distruggiDispositivo(device *dispositivo)
{

    if (dispositivo == NULL)
        return;

    delete dispositivo;
}

// inizializzazione di un asta

bool SAP_controlloAste(double lunghezza, double altezza)
{
    //controllo dimensioni
    if (altezza >= lunghezza)
    {
        cout << "Errore l'altezza dell'asta non può essere superiore alla lunghezza" << endl;
        return false;
    }
    else if (altezza <= 0 || lunghezza <= 0)
    {
        cout << "I valori dell'asta non possono essere negativi" << endl;
        return false;
    }
    return true;
}

bool SAP_controlloAngoli(float angBase, float angGiunto)
{
    if (angBase < 0 || angBase > 360)
    {
        cout << "Errore: l'angolo base deve essere compreso tra 0 e 360 gradi" << endl;
        return false;
    }
    if (angGiunto < 0 || angGiunto > 360)
    {
        cout << "Errore: l'angolo di giunzione deve essere compreso tra 0 e 360 gradi" << endl;
        return false;
    }
    return true;
}

asta *SAP_asta_init(double lunghezza, double altezza)
{

    if (!SAP_controlloAste(lunghezza, altezza))
    {
        return NULL;
    }

    asta *brc = new asta; //alloco memoria

    brc->lunghezza = lunghezza;
    brc->altezza = altezza;
    brc->rotX = altezza / 2;
    brc->rotY = lunghezza - altezza;

    return brc;
}

device *SAP_device_init(double diml, double dimh, float angBase, float angGiunto, double puntoIniX, double puntoIniY)
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

    //mi serve questo controllo???
    if (!SAP_controlloAngoli(angBase, angGiunto))
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
    dispositivo->astaBase.posizioneX = puntoIniX;
    dispositivo->astaBase.posizioneY = puntoIniY;

    return dispositivo;
}

//salvataggio SVG in un file // da vedere da matteo cosa c'è di diverso
void SAP_salvaSVG(string SVG)
{

    ofstream sistemaAstePerno("sistemaAstePerno.svg");
    if (!sistemaAstePerno || !sistemaAstePerno.is_open())
    {
        cout << "Errore: non è stato possibile salvare il file corretto.";
        return;
    }

    sistemaAstePerno << SVG;
    sistemaAstePerno.close();
}

device *SAP_caricaSVG(string nomeFile)
{
    string SVG;
    string SVGfinale;
    ifstream sistemaAstePerno(nomeFile);
    
     if (!sistemaAstePerno || !sistemaAstePerno.is_open())
    {
        cout << "Errore: non è stato possibile aprire il file corretto." << endl;
        return NULL;
    } 
    while (getline(sistemaAstePerno,SVG))
    {
        
    SVGfinale += SVG + "\n" ;
    }
    
    
    sistemaAstePerno.close();

    return SAP_parse(SVGfinale);
}

//funzione per disegnare il device
void SAP_disegnaDevice(device *dispositivo)
{

    string SVG = "";
    SVG += "<svg width=\"" + to_string(canvasWidth) + "\" height=\"" + to_string(canvasHeight) + "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    SVG += "<g>\n<title>Sistema 2 aste con perno</title>\n";
    double angBase = 90 - dispositivo->angoloBase;
    double angGiunto = dispositivo->angoloGiunto;

    double altezza = dispositivo->astaBase.altezza;
    double lunghezza = dispositivo->astaBase.lunghezza;
    double x_base = altezza / 2;
    double y_base = lunghezza - x_base;

    double dispositivoPosX = dispositivo->astaBase.posizioneX;
    double dispositivoPosY = dispositivo->astaBase.posizioneY;

    double rotAstaTotx = y_base + dispositivo->astaGiunto.lunghezza - dispositivo->astaGiunto.altezza;
    double posAstaGiuntoy = dispositivoPosY - dispositivo->astaGiunto.lunghezza + dispositivo->astaGiunto.altezza;

    SVG += "<rect transform=\"translate(" + to_string(dispositivoPosX) + "," + to_string(dispositivoPosY) + ")rotate(" + to_string(angBase) + "," + to_string(x_base) + ",";
    SVG += to_string(y_base) + ")\" id=\"svg_1\" height=\"" + to_string(lunghezza) + "\" width=\"" + to_string(altezza);
    SVG += "\" y=\"0\" x=\"0\" stroke=\"#000\" fill=\"red\"/>\n";
    SVG += "<rect transform=\"translate(" + to_string(dispositivoPosX) + "," + to_string(posAstaGiuntoy) + ")rotate(" + to_string(angBase) + "," + to_string(x_base) + ",";
    SVG += to_string(rotAstaTotx) + ")rotate(" + to_string(angGiunto) + "," + to_string(x_base) + "," + to_string(y_base) + ")\" id=\"svg_2\" height=\"" + to_string(lunghezza) + "\" width=\"" + to_string(altezza);
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

    double angBase, angGiunto, lunghezza, altezza, dispPosX, dispPosY;

    canvasWidth = stod(SAP_estraiValore(SVG, "width=\"", "\""));
    canvasHeight = stod(SAP_estraiValore(SVG, "height=\"", "\""));

    string astaBase = SAP_estraiValore(SVG, "<rect ", "/>");
    SVG = SVG.replace(SVG.find("<rect "), sizeof(astaBase), astaBase);
    string astaGiunto = SAP_estraiValore(SVG, "<rect ", "/>");

    string angGiu = SAP_estraiValore(astaGiunto, "rotate(", "/>");
    dispPosX = stod(SAP_estraiValore(astaBase, "translate(", ","));
    dispPosY = stod(SAP_estraiValore(astaBase, ",", ")"));
    angBase = 90 - stod(SAP_estraiValore(astaBase, "rotate(", ","));
    angGiunto = stod(SAP_estraiValore(angGiu, "rotate(", ","));
    lunghezza = stod(SAP_estraiValore(astaBase, "height=\"", "\""));
    altezza = stod(SAP_estraiValore(astaBase, "width=\"", "\""));

    if (!SAP_controlloAngoli(angBase, angGiunto) || !SAP_controlloAste(lunghezza, altezza) || !SAP_controlloPosizioneDevice(dispPosX, dispPosY, canvasWidth, canvasHeight))
    {
        return NULL;
    }

    return SAP_device_init(lunghezza, altezza, angBase, angGiunto, dispPosX, dispPosY);
}

device *SAP_inserisciDatiMenu()
{
    double lunghezza;
    double altezza;
    float angoloBase_rot;
    float angoloGiunto_rot;
    double posizioneIniX;
    double posizioneIniY;

    do
    {
        cout << "Inserisci larghezza del canvas:" << endl;
        cin >> canvasWidth;
        cout << "Inserisci altezza del canvas:" << endl;
        cin >> canvasHeight;

    } while (canvasHeight <= 0 || canvasWidth <= 0);

    do
    {
        cout << "Inserisci posizione X iniziale dispositivo:" << endl;
        cin >> posizioneIniX;
        cout << "Inserisci posizione Y iniziale dispositivo:" << endl;
        cin >> posizioneIniY;
    } while (!SAP_controlloPosizioneDevice(posizioneIniX, posizioneIniY, canvasWidth, canvasHeight));

    do
    {
        cout << "Inserire lunghezza bracci:" << endl;
        cin >> lunghezza;
        cout << "Inserire altezza bracci:" << endl;
        cin >> altezza;
    } while (!SAP_controlloAste(lunghezza, altezza));

    do
    {
        cout << "Inserire rotazione angolo di base:" << endl;
        cin >> angoloBase_rot;
        cout << "Inserire rotazione angolo al giunto:" << endl;
        cin >> angoloGiunto_rot;
    } while (!SAP_controlloAngoli(angoloBase_rot, angoloGiunto_rot));

    //creazione del dispositivo con misure assegnate
    device *dispositivo = SAP_device_init(lunghezza, altezza, angoloBase_rot, angoloGiunto_rot, posizioneIniX, posizioneIniY);

    return dispositivo;
}

//funzione per creare il menu di inserimento dati
void SAP_menu(device *dispositivo)
{

    double lunghezza;
    double altezza;
    float angoloBase_rot;
    float angoloGiunto_rot;
    char scelta;
    string nomeFile = "";
    do
    {
        if (dispositivo != NULL)
        {
            SAP_disegnaDevice(dispositivo);
        }
        cout << "1. Modifica misura lunghezza aste" << endl;
        cout << "2. Modifica misura altezza aste" << endl;
        cout << "3. Modifica angolo di base" << endl;
        cout << "4. Modifica angolo di giunzione" << endl;
        cout << "5. Carica da SVG" << endl;
        cout << "6. Esci" << endl;
        cin >> scelta;

        switch (scelta)
        {
        case '1':
            cout << "Inserisci nuovo valore lunghezza aste" << endl;
            cin >> lunghezza;

            if (SAP_controlloAste(lunghezza, dispositivo->astaBase.altezza))
            {
                dispositivo->astaBase.lunghezza = lunghezza;
            }

            break;
        case '2':
            cout << "Inserisci nuovo valore altezza aste" << endl;
            cin >> altezza;

            if (SAP_controlloAste(dispositivo->astaBase.lunghezza, altezza))
            {
                dispositivo->astaBase.altezza = altezza;
            }

            break;
        case '3':
            cout << "Inserisci nuovo valore angolo di base" << endl;
            cin >> angoloBase_rot;

            if (SAP_controlloAngoli(angoloBase_rot, dispositivo->angoloGiunto))
            {
                dispositivo->angoloBase = angoloBase_rot;
            }

            break;
        case '4':
            cout << "Inserisci nuovo valore angolo di giunzione" << endl;
            cin >> angoloGiunto_rot;

            if (SAP_controlloAngoli(dispositivo->angoloBase, angoloGiunto_rot))
            {
                dispositivo->angoloGiunto = angoloGiunto_rot;
            }

            break;
        case '5':
            cout << "Inserisci il nome o percorso del file da caricare" << endl;
            
            cin >> nomeFile;
            dispositivo = SAP_caricaSVG(nomeFile);
            SAP_stampaDatiDevice(dispositivo);
            break;
        case '6':

            SAP_distruggiDispositivo(dispositivo);
            return;
        default:
            cout << "Errore: scelta non contemplata" << endl;
            break;
        }
    } while (scelta != '5');
}

bool SAP_controlloPosizioneDevice(double posX, double posY, double canvasX, double canvasY)
{
    if (posX > canvasX || posY > canvasY || posX < 0 || posY < 0)
    {
        cout << "Errore: la posizione inserita esce dal canvas" << endl;
        return false;
    }
    if (canvasX <= 0 || canvasY <= 0)
    {
        cout << "Errore: le dimensioni del canvas devono essere positive e maggiori di 0" << endl;
    }
    return true;
}
