#include <iostream>


struct asta {
    double lunghezza;
    double altezza;
};

struct device {

    asta astaBase;
    asta astaGiunto;
    float angoloBase;
    float angoloGiunto;

};

asta *asta_init(double, double);

device *device_init(double, double, float, float);

void motoAngolo (float, float, device *);