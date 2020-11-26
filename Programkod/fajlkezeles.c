#include "debugmalloc.h"
#include "fajlkezeles.h"
#include <stdio.h>

char* beolvas(FILE* stream, char elvalaszto) {
    int meret = 0;
    char beolvasott = 0;
    char *tempSzoveg = NULL;
    char *Szoveg = NULL;

    beolvasott = getc(stream);

    if(beolvasott == elvalaszto) {
        meret++;
        Szoveg = (char*) malloc(meret * sizeof(char));
        Szoveg[0] = '\0';
    } else {
        int i = 2;
        while (beolvasott != elvalaszto) {
            meret++;
            tempSzoveg = (char*) malloc(meret * sizeof(char));
            if (i != 2) {
                for (int j = 0; j < meret - 1; j++) {
                    tempSzoveg[j] = Szoveg[j];
                }
            }
            free(Szoveg);
            Szoveg = (char*) malloc(meret * sizeof(char));
            if (i != 2) {
                for (int j = 0; j < meret - 1; j++) {
                    Szoveg[j] = tempSzoveg[j];
                }
            }
            Szoveg[meret - 1] = beolvasott;
            free(tempSzoveg);

            beolvasott = getc(stream);
            i++;
        }
    }
    Szoveg = (char*)realloc(Szoveg, (meret+1)*sizeof(char*));
    Szoveg[meret] = '\0';
    return Szoveg;
}

Jarat* jaratokBeolvas(Jarat* jaratok, int* jaratokMeret) {
    int i = 0;
    FILE* fp;
    fp = fopen("jaratok.txt", "r");
    Jarat tempJarat;
    tempJarat.ferohely = 0;
    while(fscanf(fp,"%[^#]#%d/%d/%d#", tempJarat.azonosito, &(tempJarat.datum.ev), &(tempJarat.datum.honap), &(tempJarat.datum.nap)) != EOF) {
        tempJarat.honnan = beolvas(fp,'#');
        tempJarat.hova = beolvas(fp,'#');

        tempJarat.foglaltUlesek = NULL;
        fscanf(fp,"%d\n",&(tempJarat.ferohely));

        jaratok = (Jarat*)realloc(jaratok, (*jaratokMeret) * sizeof(*jaratok));

        jaratok[i] = tempJarat;
        i++;
        (*jaratokMeret)++;
    }
    fclose(fp);
    return jaratok;
}

/* Járatok adatainak rögzítése a jaratok.txt fájlba */
void jaratRogzit(Jarat* jaratok, int jaratokMeret) {
    FILE *fp = fopen("jaratok.txt", "w");
    for(int jarat = 0; jarat < jaratokMeret; jarat++) {
        jaratok[jarat].ferohely = 90;
        fprintf(fp, "%s#%d/%d/%d#%s#%s#%d\n", jaratok[jarat].azonosito, jaratok[jarat].datum.ev, jaratok[jarat].datum.honap, jaratok[jarat].datum.nap, jaratok[jarat].honnan, jaratok[jarat].hova, jaratok[jarat].ferohely);
    }
    fclose(fp);
}

Foglalas* foglalasokBeolvas(Jarat* jaratok, Foglalas* foglalasok, int* foglalasokMeret, int jaratokMeret) {
    FILE* fp;
    fp = fopen("foglalasok.txt", "r");
    Foglalas tempFoglalas;

    while(fscanf(fp,"%[^#]#", tempFoglalas.azonosito) != EOF) {
        tempFoglalas.nev = beolvas(fp,'#');
        fscanf(fp,"%[^#]#%d\n", tempFoglalas.ulohely, &(tempFoglalas.menu));
        for(int j = 0; j < jaratokMeret; j++) {
            if(strcmp(jaratok[j].azonosito, tempFoglalas.azonosito) == 0) {
                foglalasok = jaratFoglal(jaratok, foglalasok, tempFoglalas, j, foglalasokMeret);
            }
        }
    }
    fclose(fp);
    return foglalasok;
}

/* Foglalások adatainak rögzítése a foglalasok.txt fájlba */
void foglalasokRogzit(Foglalas* foglalasok, int foglalasokMeret) {
    FILE* fp;
    fp = fopen("foglalasok.txt", "w");
    for (int foglalas = 0; foglalas < foglalasokMeret; foglalas++) {
        fprintf(fp, "%s#%s#%s#%d\n", foglalasok[foglalas].azonosito, foglalasok[foglalas].nev, foglalasok[foglalas].ulohely, foglalasok[foglalas].menu);
    }
    fclose(fp);
}