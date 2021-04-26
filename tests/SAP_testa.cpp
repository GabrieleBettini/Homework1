
#define CATCH_CONFIG_MAIN

#include "libreries/catch2.hpp"
#include "libreries/sistemaAstePerno.h"

using namespace std;

TEST_CASE ("Inizializzazione corretta di un puntatore ad un dispositivo") 
{
    device* dispositivo = inserisciDati(200,20,55,60);

    REQUIRE (device != NULL);
}