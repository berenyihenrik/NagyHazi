#include "foglalaskezeles.h"

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
