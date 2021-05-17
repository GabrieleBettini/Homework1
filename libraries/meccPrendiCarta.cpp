#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <math.h>
#include "meccPrendiCarta.h"

using namespace std;

#define angBaseIni 90
#define angGiuntoIni 90

double canvasW = 1000;
double canvasH = 800;

meccPrendiCarta *mecPC(double diml, double dimh,
                       float posx, float posy, float lungh, float corsa)
{
    /*     double pluto =  -guida->lunghezza/2 + guida->corsa - guida->guida->dim_x/2;
 */

    GuidaPrismatica *guida = guida_init(500, 500, 300, 0, 30, 50);

    double pippo = canvasW / 2 - 300 / 2 - guida->guida->dim_x/2 + guida->corsa;
    double angBase = acos((M_PI/2)-((guida->lunghezza - guida->corsa ) / (285*2)));
    double angGiunto = 180 - 2 * angBase;
    cout << " prova " << (guida->lunghezza-guida->corsa)/600<< endl;
    /* SAP_disegnaDevice (SAP); */

    device *SAP = SAP_device_init(300, 30, angBase, angGiunto, pippo, 200);

    cout << " angolo giunto: " << angGiunto << " angolo base: " << angBase << endl;

    SAP_stampaDatiDevice(SAP);
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

   
}

double MPC_calcoloAngoli(double lunghezza, double corsa)
{
    double angBase = acos(corsa / (2 * lunghezza)) * (M_PI / 180);
    double angGiunto = 180 - 2 * angBase;
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

    /*  do
    {
        cout << "Inserisci posizione X iniziale dispositivo:" << endl;
        cin >> posx;
        cout << "Inserisci posizione Y iniziale dispositivo:" << endl;
        cin >> posy;
    } while (!SAP_controlloPosizioneDevice(posx, posy, canvasW, canvasH)); */

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

    meccPrendiCarta *creaMecPc = mecPC(lunghezza, altezza, posx, posy, l, c);

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