# Tecniche di Programmazione Avanzata - Homework1

Creare un programma C++ che produca un disegno SVG di un dispositivo meccanico. Succesivamente integrato con un altro dispositvo.

## Dispositivo

Sistema aste con perni di rotazioni.
Costituito da 2 aste di dimensioni uguali ognuna con un proprio centro di rotazione.
![](prototipo.svg)

### Parametri

* lunghezza dell'asta
* altezza dell'asta
* angolo di rotazione dell' asta di base
* angolo di rotazione dell' asta di giunzione

### Valori vincolati

* lunghezza dell'asta sempre maggiore della sua altezza
* angolo di rotazione dell' asta di base compreso tra i valori 45 - 90
* angolo di rotazione dell' asta di giunzione compreso tra i valori 0 - 90
* centro di rotazione asta di base:
````````````````````````````````````````````````````````````````````````````````````
    $ double x_base = altezza / 2 
   
    $ double y_base = lunghezza - x_base
````````````````````````````````````````````````````````````````````````````````````
* centro di rotazione asta di giunzione:
````````````````````````````````````````````````````````````````````````````````````
    $ double x_giunto = centroSVGx + (sin(angBase * M_PI / 180) * dispositivo->astaGiunto.lunghezza) - sin(angBase * M_PI / 180) * dispositivo->astaGiunto.altezza;

    $ double y_giunto = canvasH - ((centroSVGy + (cos(angBase * M_PI / 180) * dispositivo->astaGiunto.lunghezza) -  dispositivo->astaBase.lunghezza)) - (sin(angBase * M_PI / 180) * dispositivo->astaGiunto.altezza / (1 + cos(angBase * M_PI / 180)));

````````````````````````````````````````````````````````````````````````````````````

### Integrazione con un altro dispositivo