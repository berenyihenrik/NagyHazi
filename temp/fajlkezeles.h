#ifndef FAJLKEZELES_H
#define FAJLKEZELES_H
#include "jaratkezeles.h"

char* beolvas(FILE* stream,char elvalaszto);

Jarat* jaratokBeolvas();

void jaratRogzit(Jarat* jaratok, int jaratokMeret);

#endif
