#ifndef DATUMKEZELES_H
#define DATUMKEZELES_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Datum {
    int ev;
    int honap;
    int nap;
}Datum;

Datum datumBeolvas(void);

bool datumOsszehasonlit(Datum datum1, Datum datum2);

#endif