#ifndef FAJLKEZELES_H
#define FAJLKEZELES_H
#include "jaratkezeles.h"


char* beolvas(FILE* stream,char elvalaszto);

Jarat* jaratokBeolvas();

void jaratRogzit(Jarat* jaratok, int jaratokMeret);

Foglalas* foglalasokBeolvas(Jarat* jaratok, Foglalas* foglalasok, int* foglalasokMeret, int jaratokMeret);

void foglalasokRogzit(Foglalas* foglalasok, int foglalasokMeret);

#endif
