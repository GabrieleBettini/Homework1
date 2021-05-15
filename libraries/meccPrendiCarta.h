#include "sistemaAstePerno.h"    
#include "external/guida.h"

struct meccPrendiCarta
{
    device * dispositivo;
    GuidaPrismatica * guidaP;

    
};

meccPrendiCarta *mecPC(double, double,
                       float, float, float, float);

meccPrendiCarta *datiMecPC();