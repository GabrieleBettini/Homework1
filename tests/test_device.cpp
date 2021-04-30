
#define CATCH_CONFIG_MAIN
#include "catch2.hpp"

#include "catch2.hpp"
#include "../libraries/sistemaAstePerno.h"

using namespace std;

TEST_CASE("Inizializzazione corretta di un puntatore ad un dispositivo", "[SistemaAstePerno:inizializzazione]")
{
    device *dispositivo = SAP_device_init(300, 20, 90, 45, 1200, 800);

    REQUIRE(dispositivo != NULL);
    REQUIRE(dispositivo->astaBase.lunghezza == 300);
    REQUIRE(dispositivo->astaBase.altezza == 20);

    REQUIRE(dispositivo->astaGiunto.lunghezza == 300);
    REQUIRE(dispositivo->astaGiunto.altezza == 20);

    REQUIRE(dispositivo->angoloBase == 90);
    REQUIRE(dispositivo->angoloGiunto == 45);
}

TEST_CASE("Inizializzazione sbagliata di un dispositivo", "[SistemaAstePerno:inizializzazione]")
{
    device *dispositivo = SAP_device_init(-200, -30, 90, 45, 1000, -500);

    REQUIRE(dispositivo == NULL);

    SAP_distruggiDispositivo(dispositivo);
}


