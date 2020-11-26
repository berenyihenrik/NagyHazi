//#include "debugmalloc.h"
#include "datumkezeles.h"

Datum datumBeolvas(void) {
    Datum datum;
    char datumstring[11];
    scanf("%s", datumstring);
    datum.ev = atoi(strtok(datumstring, "/"));
    datum.honap = atoi(strtok(NULL, "/"));
    datum.nap = atoi(strtok(NULL, "/"));
    return datum;
}

bool datumOsszehasonlit(Datum datum1, Datum datum2) {
    if(datum1.ev < datum2.ev) {
        return false;
    } else if(datum1.ev > datum2.ev) {
        return true;
    }

    if(datum1.ev == datum2.ev) {
        if(datum1.honap < datum2.honap) {
            return false;
        }else if(datum1.honap > datum2.honap) {
            return true;
        }else if(datum1.nap < datum2.nap) {
            return false;
        }else if(datum1.nap > datum2.nap) {
            return true;
        }
    }
    return true;
}