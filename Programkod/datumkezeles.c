#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#ifdef _WIN32
    #include <windows.h>
#endif

//#include "debugmalloc.h"

typedef struct Datum {
    int ev;
    int honap;
    int nap;
}Datum;

typedef struct Jarat {
  char azonosito[7];
  Datum datum;
  char honnan[50];
  char hova[50];
  int ferohely;
  char *foglaltUlesek;
}Jarat;

typedef enum Menu{
    normal,
    vega,
    laktozmentes
}Menu;

typedef struct Foglalas {
    char azonosito[7];
    char nev[50];
    char ulohely[3];
    int menu;
}Foglalas;

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

bool hibaKeres(Datum datum) {
    if(datum.ev < 2020) {
        return true;
    } else if(datum.honap < 1 || datum.honap > 12) {
        return true;
    } else if(datum.nap < 1 || datum.nap > 31) {
        return true;
    }
    return false;
}


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


Foglalas* jaratFoglal(Jarat* jaratok, Foglalas* foglalasok, Foglalas foglalas, int jarat, int* foglalasokMeret) {
    if (jaratok[jarat].foglaltUlesek == NULL) {
        jaratok[jarat].foglaltUlesek = (char*)malloc(((96 - jaratok[jarat].ferohely) + 1) * sizeof(char));
    } else {
        jaratok[jarat].foglaltUlesek = realloc(jaratok[jarat].foglaltUlesek,((96 - jaratok[jarat].ferohely) + 1) * sizeof(char));
    }
    jaratok[jarat].ferohely--;

    Foglalas *ujfoglalas;
    if((*foglalasokMeret) == 0) {
        (*foglalasokMeret)++;
        ujfoglalas = (Foglalas*)malloc((*foglalasokMeret) * sizeof(Foglalas));
        ujfoglalas[(*foglalasokMeret) - 1] = foglalas;
    }
    else {
        (*foglalasokMeret)++;
        ujfoglalas = realloc(foglalasok, (*foglalasokMeret) * sizeof(Foglalas));
        ujfoglalas[(*foglalasokMeret) - 1] = foglalas;
    }
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
            foglalasok[*foglalasokMeret-1] = tmpFoglalas;
            (*foglalasokMeret)--;
            foglalasok = realloc(foglalasok, (*foglalasokMeret) * sizeof(char));
            return foglalasok;
        }
    }
    printf("Ezen a néven nem található foglalás.\n");
    return foglalasok;
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

int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    /* jaratok.txt adatainak beolvasása és tárolása */
    FILE* fp;
    fp = fopen("jaratok.txt", "r");
    Jarat tempJarat;

    int i = 0;
    int jaratokMeret = 1;
    Jarat* jaratok = (Jarat*)malloc(jaratokMeret * sizeof(*jaratok));

    while(fscanf(fp,"%[^#]#%d/%d/%d#%[^#]#%[^#]#%d\n", tempJarat.azonosito, &(tempJarat.datum.ev), &(tempJarat.datum.honap), &(tempJarat.datum.nap), tempJarat.honnan, tempJarat.hova, &(tempJarat.ferohely)) != EOF) {
        tempJarat.foglaltUlesek = NULL;
        jaratok = (Jarat*)realloc(jaratok, jaratokMeret * sizeof(*jaratok));
        jaratok[i] = tempJarat;
        i++;
        jaratokMeret++;
    }
    jaratokMeret--;
    fclose(fp);


    /* foglalasok.txt adatainaka beolvasása és tárolása */
    fp = fopen("foglalasok.txt", "r");
    Foglalas tempFoglalas;

    i = 0;
    int foglalasokMeret = 0;
    Foglalas* foglalasok = NULL;
    while(fscanf(fp,"%[^#]#%[^#]#%[^#]#%d\n", tempFoglalas.azonosito, tempFoglalas.nev, tempFoglalas.ulohely, &(tempFoglalas.menu)) != EOF) {
        for(int j = 0; j < jaratokMeret; j++) {
            if(strcmp(jaratok[j].azonosito, tempFoglalas.azonosito) == 0) {
                foglalasok = jaratFoglal(jaratok, foglalasok, tempFoglalas, j, &foglalasokMeret);
            }
        }
        i++;
    }
    fclose(fp);



    /* Menü */
    int menupont = 0;

    while(menupont != 5) {
        printf("Válassz egyet az alábbi menüpontok közül:\n");
        printf("1.: Járat keresése\n");
        printf("2.: Repülõjegy foglalása\n");
        printf("3.: Foglalás törlése\n");
        printf("4.: Összesítés\n");
        printf("5.: Kilépés\n");
        scanf("%d",&menupont);

        /* Járat keresése menüpont */
        if(menupont == 1) {
            /* Úticélok beolvasása */
            getchar();
            printf("Honnan kíván utazni?");
            char honnan[50];
            gets(honnan);
            printf("Hova kíván utazni?");
            char hova[50];
            gets(hova);

            /* Dátumok beolvasása */
            printf("Mi legyen az indulási dátum?");
            Datum datum_kezdo = datumBeolvas();
            while(hibaKeres(datum_kezdo)) {
                printf("Hibás Dátum formátum, kérlek próbáld újra\n");
                printf("Mi legyen az indulási dátum?");
                datum_kezdo = datumBeolvas();
            }
            printf("Mi legyen a végsõ dátum?");
            Datum datum_vegso = datumBeolvas();
            while(hibaKeres(datum_vegso)) {
                printf("Hibás Dátum formátum, kérlek próbáld újra\n");
                printf("Mi legyen a végsõ dátum?");
                datum_vegso = datumBeolvas();
            }

            /* Járat keresése */
            jaratKeres(jaratok, jaratokMeret, honnan, hova, datum_kezdo, datum_vegso);
        }

        /* Repülõjegy foglalása menüpont */
        else if(menupont == 2) {
            printf("Mi a járat azonosítója?");
            char *jaratszam = (char*)malloc(7 * sizeof(char));
            getchar();
            gets(jaratszam);


            int jarat = 0;

            while (jarat < jaratokMeret) {
                if (strcmp(jaratok[jarat].azonosito, jaratszam) == 0) {
                    char *nev = (char*)malloc(50 * sizeof(char));

                    printf("Milyen névre legyen a foglalás?");
                    gets(nev);

                    printf("Kérlek válassz ülõhelyet!\n");
                    foglaltsagiTerkep(jaratszam);
                    printf("Választott ülõhely:");

                    char *ulohely = (char*)malloc(3 * sizeof(char));
                    getchar();
                    scanf("%s", ulohely);
                    printf("Válassz az alábbi menük közül:\n");
                    printf("1.: Normál\n");
                    printf("2.: Vega\n");
                    printf("3.: Laktózmentes\n");
                    printf("Választott étel sorszáma:");

                    int menu;
                    scanf("%d", &menu);
                    Foglalas foglalas;
                    strcpy(foglalas.azonosito, jaratszam);
                    free(jaratszam);
                    strcpy(foglalas.nev, nev);
                    free(nev);
                    strcpy(foglalas.ulohely, ulohely);
                    free(ulohely);
                    foglalas.menu = menu;

                    foglalasok = jaratFoglal(jaratok, foglalasok, foglalas, jarat, &foglalasokMeret);
                }
                jarat++;
            }
        }

        /* Foglalás törlése menüpont */
        else if(menupont == 3) {
            char *nev = (char*)malloc(50 * sizeof(char));
            printf("Milyen néven van a foglalás?");
            getchar();
            gets(nev);
            foglalasok = jaratTorol(foglalasok, nev, &foglalasokMeret);
            free(nev);
        }

        /* Összesítés menüpont */
        else if(menupont == 4) {
            printf("Összesítés.\n");
            printf("Járatszám    Normál    Vegán    Laktózmentes\n");
            Osszesit(jaratok, foglalasok, jaratokMeret, foglalasokMeret);
        }

        /* Minden más érték az 5-öt kivéve => nem létezõ menüpont */
        else if(menupont != 5) {
            printf("Nem létezõ menüpont.\n");
        }

    }


    /* Járatok adatainak rögzítése a jaratok.txt fájlba */
    fp = fopen("jaratok.txt", "w");
    for(int jarat = 0; jarat < jaratokMeret; jarat++) {
        fprintf(fp, "%s#%d/%d/%d#%s#%s#%d\n", jaratok[jarat].azonosito, jaratok[jarat].datum.ev, jaratok[jarat].datum.honap, jaratok[jarat].datum.nap, jaratok[jarat].honnan, jaratok[jarat].hova, jaratok[jarat].ferohely);
    }
    fclose(fp);

    /* Foglalások adatainak rögzítése a foglalasok.txt fájlba */
    fp = fopen("foglalasok.txt", "w");
    for(int foglalas = 0; foglalas < foglalasokMeret; foglalas++) {
        fprintf(fp, "%s#%s#%s#%d\n", foglalasok[foglalas].azonosito, foglalasok[foglalas].nev, foglalasok[foglalas].ulohely, foglalasok[foglalas].menu);
    }
    fclose(fp);





    /* Felhasznált memóriaterületek felszabadítása */
    for(int jarat = 0; jarat < jaratokMeret; jarat++) {
        free(jaratok[jarat].foglaltUlesek);
    }
    free(jaratok);
    free(foglalasok);
    return 0;
}
