#ifdef _WIN32
    #include <windows.h>
#endif

#include "debugmalloc.h"
#include "datumkezeles.h"
#include "jaratkezeles.h"
#include "menu.h"



int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    /* jaratok.txt adatainak beolvasása és tárolása */
    int jaratokMeret = 1;
    Jarat* jaratok = (Jarat*)malloc(jaratokMeret * sizeof(*jaratok));
    jaratok = jaratokBeolvas(jaratok, &jaratokMeret);
    jaratokMeret--;

    /* foglalasok.txt adatainak beolvasása és tárolása */
    int foglalasokMeret = 0;
    Foglalas* foglalasok = (Foglalas*)malloc(0);
    foglalasok = foglalasokBeolvas(jaratok, foglalasok, &foglalasokMeret, jaratokMeret);

    /* Menü */
    menu(jaratok, &jaratokMeret, foglalasok, &foglalasokMeret);

    for(int foglalas = 0; foglalas < foglalasokMeret; foglalas++) {
        printf("%s\n",foglalasok[foglalas].nev);
    }

    /* Adatok elmentése */
    jaratRogzit(jaratok, jaratokMeret);
    foglalasokRogzit(foglalasok, foglalasokMeret);


    /* Felhasznált memóriaterületek felszabadítása */
    for(int jarat = 0; jarat < jaratokMeret; jarat++) {
        free(jaratok[jarat].foglaltUlesek);
        free(jaratok[jarat].honnan);
        free(jaratok[jarat].hova);
    }
    for(int foglalas = 0; foglalas < foglalasokMeret; foglalas++) {
        free(foglalasok[foglalas].nev);
    }
    free(jaratok);
    free(foglalasok);

    return 0;
}
