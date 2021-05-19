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

meccPrendiCarta *mecPC(double diml, double dimh,float posx, float posy, float lungh, float corsa)
                       
{
    meccPrendiCarta * p = new meccPrendiCarta;

    GuidaPrismatica *guida = guida_init(500, 500, 200, 0, 30, 50);
    double ptoIniX = canvasW / 2 - guida->lunghezza / 2 - guida->guida->dim_x / 2 + guida->corsa;

    device *SAP = SAP_device_init(300, 30, 0, 0, ptoIniX, 215);
   
    MPC_calcoloAngoli(SAP,guida);

    p->dispositivo = SAP;
    p->guidaP = guida;

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
