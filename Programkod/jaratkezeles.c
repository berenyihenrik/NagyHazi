#include "debugmalloc.h"
#include "jaratkezeles.h"

void jaratKeres(Jarat *jaratok, int meret, char *honnan, char *hova, Datum datum_kezdo, Datum datum_vegso) {
    int talalatok = 0;
    for(int i = 0; i < meret;i++) {
        if(strstr(jaratok[i].honnan, honnan) != 0 && strstr(jaratok[i].hova, hova) != NULL) {
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

Foglalas* jaratFoglal(Jarat* jaratok, Foglalas* foglalasok, Foglalas foglalas, int jarat, int* foglalasokMeret) {
    /*if (jaratok[jarat].foglaltUlesek == NULL) {
        jaratok[jarat].foglaltUlesek = (char*)malloc(((96 - jaratok[jarat].ferohely) + 1) * sizeof(char));
    } else {
        jaratok[jarat].foglaltUlesek = realloc(jaratok[jarat].foglaltUlesek,((96 - jaratok[jarat].ferohely) + 1) * sizeof(char));
    }
    jaratok[jarat].ferohely--;*/


    Foglalas *ujfoglalas;
    (*foglalasokMeret)++;
    ujfoglalas = (Foglalas*)realloc(foglalasok, (*foglalasokMeret) * sizeof(*foglalasok));
    ujfoglalas[(*foglalasokMeret) - 1] = foglalas;

    return ujfoglalas;
}

Foglalas* jaratTorol(Foglalas* foglalasok, char* nev, int* foglalasokMeret) {
    for(int foglalas = 0; foglalas < *foglalasokMeret; foglalas++) {
        if(strcmp(foglalasok[foglalas].nev, nev) == 0) {
            /*if(foglalas != (*foglalasokMeret-1) {
            }*/
            Foglalas tmpFoglalas;
            tmpFoglalas = foglalasok[foglalas];
            foglalasok[foglalas] = foglalasok[(*foglalasokMeret)-1];
            foglalasok[(*foglalasokMeret)-1] = tmpFoglalas;
            (*foglalasokMeret)--;
            free(tmpFoglalas.nev);
            foglalasok = (Foglalas*)realloc(foglalasok, (*foglalasokMeret) * sizeof(Foglalas));
            return foglalasok;
        }
    }
    printf("Ezen a néven nem található foglalás.\n");
    return foglalasok;
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