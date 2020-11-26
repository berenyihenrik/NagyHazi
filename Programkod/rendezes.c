#include "rendezes.h"
#include "debugmalloc.h"

Foglalas* rendezes(Jarat* jaratok, int jaratokMeret, Foglalas* foglalasok, int foglalasokMeret) {
    int jarat = 0;
    int i = 0;
    Foglalas* ujfoglalas = (Foglalas*)malloc(foglalasokMeret * sizeof(Foglalas));
    while(jarat < jaratokMeret) {
        for(int foglalas = 0; foglalas < foglalasokMeret; foglalas++) {
            if(strcmp(jaratok[jarat].azonosito, foglalasok[foglalas].azonosito) == 0) {
                ujfoglalas[i] = foglalasok[foglalas];
                i++;
            }
        }
        jarat++;
    }
    free(foglalasok);
    return ujfoglalas;
}
