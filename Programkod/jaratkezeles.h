#ifndef JARATKEZELES_H
#define JARATKEZELES_H

#include "datumkezeles.h"

typedef struct Jarat{
    char azonosito[7];
    Datum datum;
    char *honnan;
    char *hova;
    int ferohely;
    int* foglaltUlesek;
}Jarat;

typedef struct Foglalas {
    char azonosito[7];
    char* nev;
    char ulohely[3];
    int menu;
}Foglalas;

typedef enum Menu{
    normal = 1,
    vega,
    laktozmentes
}Menu;

void jaratKeres(Jarat *jaratok, int meret, char *honnan, char *hova, Datum datum_kezdo, Datum datum_vegso);

Foglalas* jaratFoglal(Jarat* jaratok, Foglalas* foglalasok, Foglalas foglalas, int jarat, int* foglalasokMeret);

Foglalas* jaratTorol(Foglalas* foglalasok, char* nev, int* foglalasokMeret);

void foglaltsagiTerkep(Jarat* jaratok,int jaratokMeret, char* jaratszam);

void Osszesit(Jarat* jaratok, Foglalas* foglalasok, int jaratokMeret, int foglalasokMeret);

int ulohelySzam(char* ulohely);

#endif