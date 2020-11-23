#ifndef JARATKEZELES_H
#define JARATKEZELES_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "datumkezeles.h"

typedef struct Jarat{
    char azonosito[7];
    Datum datum;
    char honnan[50];
    char hova[50];
    int ferohely;
    char *foglaltUlesek;
}Jarat;

typedef struct Foglalas {
    char azonosito[7];
    char nev[50];
    char ulohely[3];
    int menu;
}Foglalas;

typedef enum Menu{
    normal,
    vega,
    laktozmentes
}Menu;

void jaratKeres(Jarat *jaratok, int meret, char *honnan, char *hova, Datum datum_kezdo, Datum datum_vegso);

Foglalas* jaratFoglal(Jarat* jaratok, Foglalas* foglalasok, Foglalas foglalas, int jarat, int* foglalasokMeret);

Foglalas* jaratTorol(Foglalas* foglalasok, char* nev, int* foglalasokMeret);

void foglaltsagiTerkep(char* jaratszam); //még nem ellenõrzi az eddig lefoglalt helyeket, csupa üres helyeket fog printelni

void Osszesit(Jarat* jaratok, Foglalas* foglalasok, int jaratokMeret, int foglalasokMeret);

#endif