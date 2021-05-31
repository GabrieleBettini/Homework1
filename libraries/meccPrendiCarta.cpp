#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <math.h>
#include "meccPrendiCarta.h"

using namespace std;

double canvasW = 1000;
double canvasH = 800;

void MPC_calcoloAngoli(device *SAP, GuidaPrismatica *guida)
{
    double base = guida->lunghezza - guida->corsa;

    double angBase = (180 / M_PI) * acos(base / (2 * (SAP->astaBase.lunghezza - SAP->astaBase.altezza)));

    double angGiunto = 180 - 2 * angBase;
    SAP_setAngolo(SAP, angBase, 180 - angGiunto);
}

meccPrendiCarta *mecPC(double posx, double posy, float lungh, float corsa, double dimh, double diml)

{
    meccPrendiCarta *p = new meccPrendiCarta;

    GuidaPrismatica *guida = guida_init(posx, posy, lungh, corsa, dimh, dimh);
    double ptoIniX = posx - guida->lunghezza / 2 - guida->guida->dim_x / 2 + guida->corsa;
    cout << "ptoIniX " << ptoIniX << endl;
    double ptoIniY = posy - diml + dimh / 2;

    device *SAP = SAP_device_init(diml, dimh, 0, 0, ptoIniX, ptoIniY);

    MPC_calcoloAngoli(SAP, guida);

    p->dispositivo = SAP;
    p->guidaP = guida;

    return p;
}

void MecPC_salvaSVG(meccPrendiCarta **mecPC,int arrSize, string nomeFile )
{
    
    string SVG = "";
    SVG += "<svg width=\"" + to_string(canvasW) + "\" height=\"" + to_string(canvasH) + "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    SVG += "<g>\n<title>Meccanismo prendi carta</title>\n";
    for (int i = 0; i < arrSize; i++)
    {

        SVG += SAP_disegnaDaStringa(mecPC[i]->dispositivo);

        SVG += guida_to_SVGstring(mecPC[i]->guidaP);
    }
    SVG += "</g>\n</svg>\n";
    ofstream meccPrendiCarta(nomeFile + ".svg");

    meccPrendiCarta << SVG;
    meccPrendiCarta.close();
}

void datiMecPC()
{

    double lunghezza;

    float posx, posy, lunghezzaG, corsa, dimx, dimy;

    GuidaPrismatica *guida;
    guida = new GuidaPrismatica;

    int n;
    do
    {
        cout << "Inserisci il numero di machine che vuoi creare" << endl;
        cin >> n;
    } while (n < 1);


    do
    {
        cout << "Specificare le 2 coordinate (x,y) della posizione centrale della guida prismatica: ";
        cin >> posx >> posy;

    } while (!guida_controlla_integrita(guida));
    do
    {

        cout << "Specificare la lunghezza della guida prismatica: ";
        cin >> lunghezzaG;
    } while (!guida_controlla_integrita(guida));
    do
    {

        cout << "Spceficiare il valore della corsa della guida prismatica: ";
        cin >> corsa; //variabile corsa mi diventa un array per cambiare la corsa delle machine
    } while (!guida_controlla_integrita(guida));
    do
    {

        cout << "Specificare la dimensione orizzontale e verticale delle cerniere e della guida: ";
        cin >> dimx >> dimy;
    } while (!guida_controlla_integrita(guida));
    do
    {
        cout << "Inserire lunghezza bracci:" << endl;
        cin >> lunghezza; //variabile lunghezza mi diventa un array per cambiare la corsa delle machine
    } while (!SAP_controlloAste(lunghezza, dimx));

    cout << "il valore di n " << n << endl;
    meccPrendiCarta **arr;          // notare doppio asterisco
    arr = new meccPrendiCarta *[n]; // notare asterisco dopo meccPrendiCarta

    for (int i = 0; i < n; i++)
    {
        arr[i] = mecPC(posx + i * (lunghezzaG + dimx), posy, lunghezzaG, corsa, dimx, lunghezza);

    }


    MecPC_salvaSVG(arr, n,  "Machine");

    for (int i = 0; i < n; i++)
    {
        delete arr[i];
    }

    // poi elimino tutto l'array
    delete[] arr;
}
