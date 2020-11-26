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

int ulohelySzam(char* ulohely) {
    char sor[4] = "";
    strcpy(sor,(ulohely) + 1);
    int sorszam = atoi(strtok(sor, "\0"));
    int ules;
    switch (ulohely[0]) {
        case 'A':
            ules = 0 + (sorszam-1)*9;
            break;
        case 'B':
            ules = 1 + (sorszam-1)*9;
            break;
        case 'C':
            ules = 2 + (sorszam-1)*9;
            break;
        case 'D':
            ules = 3 + (sorszam-1)*9;
            break;
        case 'E':
            ules = 4 + (sorszam-1)*9;
            break;
        case 'F':
            ules = 5 + (sorszam-1)*9;
            break;
        case 'G':
            ules = 6 + (sorszam-1)*9;
            break;
        case 'H':
            ules = 7 + (sorszam-1)*9;
            break;
        case 'I':
            ules = 8 + (sorszam-1)*9;
            break;
        default:
            ules = 0;
            break;
    }
    return ules;
}

Foglalas* jaratFoglal(Jarat* jaratok, Foglalas* foglalasok, Foglalas foglalas, int jarat, int* foglalasokMeret) {
    if (jaratok[jarat].foglaltUlesek == NULL) {
        jaratok[jarat].foglaltUlesek = (int*) malloc(1 * sizeof(int));
    } else {
        jaratok[jarat].foglaltUlesek = (int*) realloc(jaratok[jarat].foglaltUlesek,((90 - jaratok[jarat].ferohely) + 1) * sizeof(int));
    }
    (jaratok[jarat].ferohely)--;
    jaratok[jarat].foglaltUlesek[(90 - jaratok[jarat].ferohely) - 1] = ulohelySzam(foglalas.ulohely);

    Foglalas *ujfoglalas;
    (*foglalasokMeret)++;
    ujfoglalas = (Foglalas*)realloc(foglalasok, (*foglalasokMeret) * sizeof(*foglalasok));
    ujfoglalas[(*foglalasokMeret) - 1] = foglalas;

    return ujfoglalas;
}

Foglalas* jaratTorol(Foglalas* foglalasok, char* nev, int* foglalasokMeret) {
    for(int foglalas = 0; foglalas < *foglalasokMeret; foglalas++) {
        if(strcmp(foglalasok[foglalas].nev, nev) == 0) {
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

void foglaltsagiTerkep(Jarat* jaratok,int jaratokMeret, char* jaratszam) {
    int jarat = 0;
    char ulesek[90];
    for(int i = 0; i < 90; i++) {
        ulesek[i] = '*';
    }

    while(jarat < jaratokMeret) {
        if(strcmp(jaratok[jarat].azonosito, jaratszam) == 0) {
            for (int i = 0; i < (90 - jaratok[jarat].ferohely); i++) {
                ulesek[jaratok[jarat].foglaltUlesek[i]] = 'x';
            }
        }
        jarat++;
    }

    printf("A B C\tD E F\tG H I\n");
    int ules = 0;
    while(ules < 90) {
        if(ules % 9 == 0 && ules != 0) {
            printf(" %d\n",(ules/9));
        } else if(ules % 3 == 0 && ules != 0) {
            printf(" ");
        }
        printf("%c ", ulesek[ules]);
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
        printf("%s\t\t%d\t\t%d\t\t%d\n", jaratok[jarat].azonosito, norm, veg, lakt);
    }
}