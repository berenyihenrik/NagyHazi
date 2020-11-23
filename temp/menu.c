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
            printf("Mi a járat azonosítója?");
            char *jaratszam = (char*)malloc(7 * sizeof(char));
            getchar();
            gets(jaratszam);


            int jarat = 0;

            while (jarat < *jaratokMeret) {
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

