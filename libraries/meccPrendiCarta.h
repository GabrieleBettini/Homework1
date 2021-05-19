#include "sistemaAstePerno.h"    
#include "external/guida.h"

struct meccPrendiCarta
{
    device * dispositivo;
    GuidaPrismatica * guidaP;

    
};
void MPC_calcoloAngoli(device *, GuidaPrismatica *);

meccPrendiCarta *mecPC(double, double,float, float, float, float);
                       

meccPrendiCarta *datiMecPC();

void MecPC_salvaSVG (meccPrendiCarta *, string);