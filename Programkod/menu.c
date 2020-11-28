#include "debugmalloc.h"
#include "validacio.h"
#include "jaratkezeles.h"
#include "menu.h"
#include <stdio.h>

void menu(Jarat* jaratok, int* jaratokMeret, Foglalas** foglalasok, int* foglalasokMeret) {
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
            char* honnan = inputValidacio(beolvas(stdin, '\n'));
            printf("Hova kíván utazni?");
            char* hova= inputValidacio(beolvas(stdin, '\n'));
            /* Dátumok beolvasása */
            printf("Mi legyen az indulási dátum?");
            Datum datum_kezdo = datumBeolvas();
            while(datumValidacio(datum_kezdo)) {
                printf("Hibás Dátum formátum, kérlek próbáld újra\n");
                printf("Mi legyen az indulási dátum?");
                datum_kezdo = datumBeolvas();
            }
            printf("Mi legyen a végsõ dátum?");
            Datum datum_vegso = datumBeolvas();
            while(datumValidacio(datum_vegso)) {
                printf("Hibás Dátum formátum, kérlek próbáld újra\n");
                printf("Mi legyen a végsõ dátum?");
                datum_vegso = datumBeolvas();
            }

            /* Járat keresése */
            jaratKeres(jaratok, *jaratokMeret, honnan, hova, datum_kezdo, datum_vegso);
            free(honnan);
            free(hova);
        }

        /* Repülõjegy foglalása menüpont */
        else if(menupont == 2) {
            Foglalas foglalas;
            printf("Mi a járat azonosítója?");
            scanf("%s",foglalas.azonosito);

            int jarat = 0;

            while (jarat < *jaratokMeret) {
                if (strcmp(jaratok[jarat].azonosito, foglalas.azonosito) == 0) {
                    printf("Milyen névre legyen a foglalás?");
                    getchar();
                    foglalas.nev = inputValidacio(beolvas(stdin, '\n'));

                    printf("Kérlek válassz ülõhelyet!\n");
                    foglaltsagiTerkep(jaratok, *jaratokMeret, foglalas.azonosito);
                    printf("Választott ülõhely:");
                    scanf("%s", foglalas.ulohely);

                    while(ulohelyValidacio(ulohelySzam(foglalas.ulohely), jaratok[jarat].foglaltUlesek, (90 - jaratok[jarat].ferohely))) {
                        printf("Ez az ülõhely már foglalt,, kérlek írd be újra.\n");
                        scanf("%s", foglalas.ulohely);
                    }

                    printf("Válassz az alábbi menük közül:\n");
                    printf("1.: Normál\n");
                    printf("2.: Vega\n");
                    printf("3.: Laktózmentes\n");
                    printf("Választott étel sorszáma:");

                    scanf("%d", &(foglalas.menu));
                    while(foglalas.menu != normal && foglalas.menu != vega && foglalas.menu != laktozmentes) {
                        printf("Nem létezõ menü, kérlek írd be újra.\n");
                        scanf("%d", &(foglalas.menu));
                    }

                    *foglalasok = jaratFoglal(jaratok, *foglalasok, foglalas, jarat, foglalasokMeret);
                    break;
                }
                jarat++;
            }
            if(jarat == *jaratokMeret) {
                printf("Hibás vagy nem létezõ azonosító.\n");
            }
        }

        /* Foglalás törlése menüpont */
        else if(menupont == 3) {
            char *nev;
            printf("Milyen néven van a foglalás?");
            getchar();
            nev = inputValidacio(beolvas(stdin, '\n'));
            *foglalasok = jaratTorol(*foglalasok, nev, foglalasokMeret);
            free(nev);
        }

        /* Összesítés menüpont */
        else if(menupont == 4) {
            printf("Összesítés.\n");
            printf("Járatszám\tNormál\t\tVegán\t""Laktózmentes\n");
            Osszesit(jaratok, *foglalasok, *jaratokMeret, *foglalasokMeret);
        }

        /* Minden más érték az 5-öt kivéve => nem létezõ menüpont */
        else if(menupont != 5) {
            printf("Nem létezõ menüpont.\n");
        }
    }
}