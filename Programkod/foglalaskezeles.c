#include "datumkezeles.h"
#include "jaratkezeles.h"

void jaratKeres(Jarat *jaratok, int meret, char *honnan, char *hova, Datum datum_kezdo, Datum datum_vegso) {
    int talalatok = 0;
    for(int i = 0; i < meret;i++) {
        if(strcmp(jaratok[i].honnan, honnan) == 0 && strcmp(jaratok[i].hova, hova) == 0) {
            if(datumOsszehasonlit(jaratok[i].datum, datum_kezdo)) {
                if(!datumOsszehasonlit(jaratok[i].datum, datum_vegso)) {
                    printf("%s %d %d %d %s %s %d\n", jaratok[i].azonosito, jaratok[i].datum.ev, jaratok[i].datum.honap, jaratok[i].datum.nap, jaratok[i].honnan, jaratok[i].hova, jaratok[i].ferohely);
                    talalatok++;
                }
            }
        }
    }
    if(talalatok == 0) {
        printf("Nem található járat a megadott keresési feltételek szerint.");
    }
}

void foglaltsagiTerkep(char* jaratszam) {  //még nem ellenõrzi az eddig lefoglalt helyeket, csupa üres helyeket fog printelni
    printf("ABC DEF GHI\n");
    int ules = 0;
    while(ules < 90) {
        if(ules % 9 == 0 && ules != 0) {
            printf(" %d\n",(ules/9));
        } else if(ules % 3 == 0 && ules != 0) {
            printf(" ");
        }
        printf("*");
        ules++;
    }
    printf(" %d\n",(ules/9));
}

void Osszesit(Jarat* jaratok, Foglalas* foglalasok, int jaratokMeret, int foglalasokMeret) {
    for(int jarat = 0; jarat < jaratokMeret; jarat++) {
        int norm = 0;
        int veg = 0;
        int lakt = 0;
        for(int foglalas = 0; foglalas < foglalasokMeret; foglalas++) {
            if(strcmp(jaratok[jarat].azonosito ,foglalasok[foglalas].azonosito) == 0) {
                if(foglalasok[foglalas].menu == normal) {
                    norm++;
                } else if(foglalasok[foglalas].menu == vega) {
                    veg++;
                } else if(foglalasok[foglalas].menu == laktozmentes) {
                    lakt++;
                }
            }
        }
        printf("%s         %d          %d          %d\n", jaratok[jarat].azonosito, norm, veg, lakt);
    }
}