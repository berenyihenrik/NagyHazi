#include "validacio.h"
#include "fajlkezeles.h"
#include "debugmalloc.h"

bool datumValidacio(Datum datum) {
    if(datum.ev < 2020) {
        return true;
    } else if(datum.honap < 1 || datum.honap > 12) {
        return true;
    } else if(datum.nap < 1 || datum.nap > 31) {
        return true;
    }
    return false;
}

char* inputValidacio(char* input) {
    while(strcmp(input,  "") == 0) {
        printf("Hibás input, kérlek írd be újra.\n");
        input = beolvas(stdin, '\n');
    }
    return input;
}

bool ulohelyValidacio(int ules, int foglalt[], int meret) {
    for(int i = 0; i < meret; i++) {
       if(foglalt[i] == ules) {
           return true;
       }
    }
    return false;
}