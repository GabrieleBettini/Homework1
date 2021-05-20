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

void menu (int n) {

    cout <<"Quante macchine vuoi creare?" << endl;
    cin >> n;


}


void MPC_calcoloAngoli(device * SAP, GuidaPrismatica * guida)
{
    double base = guida->lunghezza - guida->corsa;
    
    double angBase =  (180/M_PI)*acos(base / (2 * (SAP->astaBase.lunghezza - SAP->astaBase.altezza)));

    double angGiunto = 180 - 2 * angBase;
    SAP_setAngolo(SAP, angBase,180 - angGiunto);

}

meccPrendiCarta *mecPC(float posx, float posy,float lungh, float corsa,double dimh, double diml )
                       
{
    meccPrendiCarta * p = new meccPrendiCarta;

    GuidaPrismatica *guida = guida_init(posx, posy, lungh, corsa, dimh, dimh);
    double ptoIniX = canvasW / 2 - guida->lunghezza / 2 - guida->guida->dim_x / 2 + guida->corsa;

    device *SAP = SAP_device_init(diml, dimh, 0, 0, ptoIniX, posy);
   
    MPC_calcoloAngoli(SAP,guida);

    p->dispositivo = SAP;
    p->guidaP = guida;

    cout << "posX: " << posx << endl;
    cout << "posY: " << posy << endl;
    cout << "lungh: " << lungh << endl;
    cout << "corsa: " << corsa << endl;
    cout << "dimh: " << dimh << endl;
    cout << "diml: " << diml << endl;
    cout << "ptoIniX: " << ptoIniX << endl;
    return p;
    
    
}


void MecPC_salvaSVG (meccPrendiCarta * mecPC, string nomeFile) {

    string SVG = "";
    SVG += "<svg width=\"" + to_string(1000) + "\" height=\"" + to_string(1000) + "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    SVG += "<g>\n<title>Meccanismo prendi carta</title>\n";

    SVG += SAP_disegnaDaStringa(mecPC->dispositivo);

    SVG += guida_to_SVGstring(mecPC->guidaP);

    SVG += "</g>\n</svg>\n";
    ofstream meccPrendiCarta(nomeFile + ".svg");

    meccPrendiCarta << SVG;
    meccPrendiCarta.close();

}

meccPrendiCarta *datiMecPC()
{

    double lunghezza;

    float posx, posy, lunghezzaG, corsa, dimx, dimy;

    GuidaPrismatica *guida;
    guida = new GuidaPrismatica;



    do
    {
        cout << "Inserire lunghezza bracci:" << endl;
        cin >> lunghezza;
    } while (!SAP_controlloAste(lunghezza, dimx));

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
        cin >> corsa;
    } while (!guida_controlla_integrita(guida));
    do
    {

        cout << "Specificare la dimensione orizzontale e verticale delle cerniere e della guida: ";
        cin >> dimx >> dimy;
    } while (!guida_controlla_integrita(guida));

    meccPrendiCarta *creaMecPc = mecPC(posx, posy, lunghezzaG , corsa, dimx, lunghezza );

    return creaMecPc;
}
