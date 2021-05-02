#include <iostream>
#include <string.h> 
#include <fstream>
#include <vector>
#include "meccPrendiCarta.h"

using namespace std;

meccPrendiCarta *mecPC (double diml, double dimh, float angBase, float angGiunto,
                        float posx, float posy, float lungh, float corsa, float dimx, float dimy) 
{
    meccPrendiCarta *MPC = new meccPrendiCarta;

    asta *braccioBase = SAP_asta_init(diml, dimh);
    asta *braccioGiunto = SAP_asta_init(diml, dimh);

    if (braccioBase == NULL || braccioGiunto == NULL)
    {
        return NULL;
    }

    MPC->dispositivo->angoloBase = angBase;
    MPC->dispositivo->angoloGiunto = angGiunto;
    MPC->dispositivo->astaBase = *braccioBase;
    MPC->dispositivo->astaGiunto = *braccioGiunto;
    MPC->dispositivo->astaBase.posizioneX = posx;
    MPC->dispositivo->astaBase.posizioneY = posy;

    MPC->guidaP->pos_x = posx;
    MPC->guidaP->pos_y = posy;
    MPC->guidaP->lunghezza = lungh;
    MPC->guidaP->corsa = corsa;
    MPC->guidaP->incastri = grect_init( dimx, dimy ); 
    MPC->guidaP->guida = grect_init( dimx, dimy );
    MPC->guidaP->spessore = dimy/3;
    MPC->guidaP->alpha = 0;

    
}

bool MPC_posizioneRotazione (float percCorsa, device *dispositivo) 
{
    if (percCorsa >= 95) 
    {
        dispositivo->angoloBase = 45;
        dispositivo->angoloGiunto = 90;
        return true;
    }
    return false;
}

