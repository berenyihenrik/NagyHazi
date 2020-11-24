#include "debugmalloc.h"
#include "menu.h"


void menu(Jarat* jaratok, int* jaratokMeret, Foglalas* foglalasok, int* foglalasokMeret) {
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
            char *honnan = beolvas(stdin, '\n');
            printf("Hova kíván utazni?");
            char *hova= beolvas(stdin, '\n');

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
            jaratKeres(jaratok, *jaratokMeret, honnan, hova, datum_kezdo, datum_vegso);
        }

            /* Repülõjegy foglalása menüpont */
        else if(menupont == 2) {
            Foglalas foglalas;
            printf("Mi a járat azonosítója?");
            char jaratszam[7];
            scanf("%s",foglalas.azonosito);


            int jarat = 0;

            while (jarat < *jaratokMeret) {
                if (strcmp(jaratok[jarat].azonosito, foglalas.azonosito) == 0) {
                    printf("Milyen névre legyen a foglalás?");
                    getchar();
                    foglalas.nev = beolvas(stdin, '\n');

                    printf("Kérlek válassz ülõhelyet!\n");
                    foglaltsagiTerkep(foglalas.azonosito);
                    printf("Választott ülõhely:");

                    //getchar();
                    scanf("%s", foglalas.ulohely);
                    printf("Válassz az alábbi menük közül:\n");
                    printf("1.: Normál\n");
                    printf("2.: Vega\n");
                    printf("3.: Laktózmentes\n");
                    printf("Választott étel sorszáma:");

                    scanf("%d", &(foglalas.menu));

                    printf("\n%s %s %s %d\n",foglalas.azonosito, foglalas.nev,foglalas.ulohely,foglalas.menu);


                    foglalasok = jaratFoglal(jaratok, foglalasok, foglalas, jarat, foglalasokMeret);
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
            foglalasok = jaratTorol(foglalasok, nev, foglalasokMeret);
            free(nev);
        }

            /* Összesítés menüpont */
        else if(menupont == 4) {
            printf("Összesítés.\n");
            printf("Járatszám    Normál    Vegán    Laktózmentes\n");
            Osszesit(jaratok, foglalasok, *jaratokMeret, *foglalasokMeret);
        }

            /* Minden más érték az 5-öt kivéve => nem létezõ menüpont */
        else if(menupont != 5) {
            printf("Nem létezõ menüpont.\n");
        }

    }
}

