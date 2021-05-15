#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "meccPrendiCarta.h"

using namespace std;

#define angBaseIni 90
#define angGiuntoIni 90

double canvasW = 2400;
double canvasH = 800;

meccPrendiCarta *mecPC(double diml, double dimh,
                       float posx, float posy, float lungh, float corsa)
{
    device *SAP = SAP_device_init(300, 30, 90, 60, 200, 200);

    SAP_stampaDatiDevice(SAP);
    /* SAP_disegnaDevice (SAP); */

    GuidaPrismatica *guida = guida_init(100, 200, 300, 200, 30, 50);

    /*  guida_to_SVG(guida,"./guidaSVG", false); */
    string SVG = "";
    SVG += "<svg width=\"" + to_string(1000) + "\" height=\"" + to_string(1000) + "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    SVG += "<g>\n<title>Meccanismo prendi carta</title>\n";

    SVG += SAP_disegnaDaStringa(SAP);

    SVG += guida_to_SVGstring(guida);

    SVG += "</g>\n</svg>\n";
    ofstream meccPrendiCarta("meccPrendiCarta.svg");

    meccPrendiCarta << SVG;
    meccPrendiCarta.close();

    /* meccPrendiCarta *MPC = new meccPrendiCarta;

    asta *braccioGiunto = SAP_asta_init(diml, dimh);
    asta *braccioBase = SAP_asta_init(diml, dimh);

    if (braccioBase == NULL || braccioGiunto == NULL)
    {
        return NULL;
    }

    MPC->dispositivo->angoloBase = angBaseIni;
    MPC->dispositivo->angoloGiunto = angGiuntoIni;
    MPC->dispositivo->astaBase = *braccioBase;
    MPC->dispositivo->astaGiunto = *braccioGiunto;
    MPC->dispositivo->astaBase.posizioneX = posx;
    MPC->dispositivo->astaBase.posizioneY = posy;

    MPC->guidaP->pos_x = posx;
    MPC->guidaP->pos_y = posy;
    MPC->guidaP->lunghezza = lungh;
    MPC->guidaP->corsa = corsa;
    MPC->guidaP->incastri = grect_init(dimh, dimh);
    MPC->guidaP->guida = grect_init(dimh, dimh);
    MPC->guidaP->spessore = dimh / 3;
    MPC->guidaP->alpha = 0; */
}

meccPrendiCarta *datiMecPC()
{

    double lunghezza;
    double altezza;

    float angoloBase_rot;
    float angoloGiunto_rot;

    /* double posizioneIniX;
    double posizioneIniY;
 */
    float posx, posy, l, c, dimx, dimy;

    GuidaPrismatica *guida;
    guida = new GuidaPrismatica;
    
    do
    {
        cout << "Inserisci posizione X iniziale dispositivo:" << endl;
        cin >> posx;
        cout << "Inserisci posizione Y iniziale dispositivo:" << endl;
        cin >> posy;
    } while (!SAP_controlloPosizioneDevice(posx, posy, canvasW, canvasH));

    do
    {
        cout << "Inserire lunghezza bracci:" << endl;
        cin >> lunghezza;
        cout << "Inserire altezza bracci:" << endl;
        cin >> altezza;
    } while (!SAP_controlloAste(lunghezza, altezza));


    do
    {
        cout << "Specificare le 2 coordinate (x,y) della posizione centrale della guida prismatica: ";
        cin >> posx >> posy;

    } while (!guida_controlla_integrita(guida));
    do
    {

        cout << "Specificare la lunghezza della guida prismatica: ";
        cin >> l;
    } while (!guida_controlla_integrita(guida));
    do
    {

        cout << "Spceficiare il valore della corsa della guida prismatica: ";
        cin >> c;
    } while (!guida_controlla_integrita(guida));
    do
    {

        cout << "Specificare la dimensione orizzontale e verticale delle cerniere e della guida: ";
        cin >> dimx >> dimy;
    } while (!guida_controlla_integrita(guida));

    meccPrendiCarta *creaMecPc = mecPC(lunghezza, altezza, posx, posy,l, c);

    /* meccPrendiCarta *creaMecPc = SAP_inserisciDatiMenu();       //perché non va bene??? */
    return creaMecPc;
}

// funzione che determina la posizione della guida in percentuale alla sua corsa
float liv_determinacorsa(GuidaPrismatica *guida, float perc)
{
    float res;
    float corsa_utile = guida->lunghezza - guida->incastri->dim_x - guida->guida->dim_x / 2;
    res = guida->incastri->dim_x / 2 + perc * corsa_utile / 100;
    return res;
}

// funzione che, presa la posizione della guida, muove il SAP in posizione attiva
bool MPC_posRotazione(float corsa, device *dispositivo)
{
    GuidaPrismatica *guida;
    float percCorsa = liv_determinacorsa(guida, corsa);

    // non sono convinto sia corretta la scrittura
    if (percCorsa >= 95)
    {
        dispositivo->angoloBase = 45;
        dispositivo->angoloGiunto = 90;
        return true;
    }
    else
    {
        dispositivo->angoloBase = angBaseIni;
        dispositivo->angoloGiunto = angGiuntoIni;
    }
}

// funzione che limita l'esistenza degli angoli
// MI SERVE?????
bool MPC_limitiAngoli(float angBase, float angGiunto)
{
    if (angBase < 45 || angBase > 90)
    {
        return false;
    }
    if (angGiunto < 0 || angGiunto > 90)
    {
        return false;
    }
    return true;
}

/* creare la machine che quando la posizione della guida si trova dal 95% (o 100% meglio???) della corsa, SAP inizia a ruotare per andare in posizone
e dopo inizia a trascinare un foglio */