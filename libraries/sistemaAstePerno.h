#include <iostream>
#include <string>

using namespace std;

extern double canvasWidth;
extern double canvasHeight;  

struct asta
{
    double lunghezza;
    double altezza;

    //posizione perno all'interno dell'asta
    double rotX;
    double rotY;

    double posizioneX;
    double posizioneY;
};

struct device
{

    asta astaBase;
    asta astaGiunto;
    float angoloBase;
    float angoloGiunto;
};

asta *SAP_asta_init(double, double);

device *SAP_device_init(double, double, float, float, double, double);

bool SAP_controlloAste(double, double);

bool SAP_controlloAngoli(float, float);

void SAP_setAngolo(device *, float, float);

void SAP_salvaSVG(string SVG);

string SAP_disegnaDaStringa(device *);

void SAP_disegnaDevice(device *);

void SAP_distruggiDispositivo(device *);

string SAP_estraiValore(string, string, string);

device *SAP_parse(string);

device *SAP_inserisciDatiMenu();

device *SAP_caricaSVG(string );

void SAP_menu(device *);

void SAP_stampaDatiDevice(device *);

bool SAP_controlloPosizioneDevice(double, double, double, double);

device *SAP_inserisciDati();
