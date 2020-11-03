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
  int *foglaltUlesek;
}Jarat;

typedef enum Menu{
    normal,
    vega,
    laktozmentes
}Menu;

typedef struct Foglalas {
    char azonosito[7];
    char nev[50];
    int ulohely;
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

void jaratFoglal(char* jaratszam) {

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
    while(fscanf(fp,"%[^#]#%[^#]#%d#%d\n", tempFoglalas.azonosito, tempFoglalas.nev, &(tempFoglalas.ulohely), &(tempFoglalas.menu)) != EOF) {
        foglalasokMeret++;
        if(foglalasokMeret == 1) {
            foglalasok = (Foglalas*)malloc(foglalasokMeret * sizeof(*foglalasok));
        } else {
            foglalasok = (Foglalas*)realloc(foglalasok, foglalasokMeret * sizeof(*foglalasok));
        }
        foglalasok[i] = tempFoglalas;
        for(int j = 0; j < jaratokMeret; j++) {
            if(strcmp(jaratok[j].azonosito, foglalasok[i].azonosito) == 0) {
                if(jaratok[j].foglaltUlesek == NULL) {
                    jaratok[j].foglaltUlesek = (int*)malloc(((96-jaratok[j].ferohely)+1) * sizeof(int));
                } else {
                    jaratok[j].foglaltUlesek = realloc(jaratok[j].foglaltUlesek,((96-jaratok[j].ferohely)+1) * sizeof(int));
                }
                jaratok[j].ferohely--;
            }
        }
        i++;
    }
    fclose(fp);


    //printf("%s %d %d %d %s %s %d\n", jaratok[0].azonosito, jaratok[0].datum.ev, jaratok[0].datum.honap, jaratok[0].datum.nap, jaratok[0].honnan, jaratok[0].hova, jaratok[0].ferohely);










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
            fflush(stdin);
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
            Datum datum_vegso = datumBeolvas();
            printf("Mi legyen a végsõ dátum?");
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
            printf("Ez a repülõjegy foglalása menüpont.\n");
        }

        /* Foglalás törlése menüpont */
        else if(menupont == 3) {
            printf("Foglalás törlése.\n");
        }

        /* Összesítés menüpont */
        else if(menupont == 4) {
            printf("Összesítés.\n");
        }

        /* Minden más érték az 5-öt kivéve => nem létezõ menüpont */
        else if(menupont != 5) {
            printf("Nem létezõ menüpont.\n");
        }

    }






    free(jaratok);
    free(foglalasok);
    return 0;
}
