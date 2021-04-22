#include "manovella.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;


// definisco le dimensioni del braccio e degli angoli dei bracci
device * device_init (double diml, double dimh, float ang1, float ang2) {

    device * brc = new device;

    brc -> dim_l = diml;
    brc -> dim_h = dimh;

    device * ang = new device;

    ang -> ang1 = angolo1;
    ang -> ang2 = angolo2;


    //ritorno le dimensioni del braccio e degli angoli dei bracci
    return brc,ang;
}

