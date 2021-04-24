#include <iostream>

struct asta
{
    double lunghezza;
    double altezza;
    
    //posizione perno all'interno dell'asta
    double x; 
    double y;
};

struct device
{

    asta astaBase;
    asta astaGiunto;
    float angoloBase;
    float angoloGiunto;
};

asta *SAP_asta_init(double, double);

device *SAP_device_init(double, double, float, float);

void SAP_motoAngolo(float, float, device *);

void SAP_drawDevice(device *);