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
  Datum idopont;
  char honnan[50];
  char hova[50];
  int ferohely;
}Jarat;


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


void jaratKeres(Jarat *jaratok, int meret, char *honnan, char *hova, Datum idopont_kezdo, Datum idopont_vegso) {
    int talalatok = 0;
    for(int i = 0; i < meret;i++) {
        if(strcmp(jaratok[i].honnan, honnan) == 0 && strcmp(jaratok[i].hova, hova) == 0) {
            if(datumOsszehasonlit(jaratok[i].idopont, idopont_kezdo)) {
                if(!datumOsszehasonlit(jaratok[i].idopont, idopont_vegso)) {
                    printf("%s %d %d %d %s %s %d\n", jaratok[i].azonosito, jaratok[i].idopont.ev, jaratok[i].idopont.honap, jaratok[i].idopont.nap, jaratok[i].honnan, jaratok[i].hova, jaratok[i].ferohely);
                    talalatok++;
                }
            }
        }
    }
    if(talalatok == 0) {
        printf("Nem található járat a megadott keresési feltételek szerint.");
    }
}



int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif


    FILE* fp;
    fp = fopen("jaratok.txt", "r");
    Jarat tempJarat;

    int i = 0;
    int jaratokMeret = 1;
    Jarat* jaratok = (Jarat*)malloc(jaratokMeret * sizeof(*jaratok));

    while(fscanf(fp,"%[^#]#%d/%d/%d#%[^#]#%[^#]#%d\n", tempJarat.azonosito, &(tempJarat.idopont.ev), &(tempJarat.idopont.honap), &(tempJarat.idopont.nap), tempJarat.honnan, tempJarat.hova, &(tempJarat.ferohely)) != EOF) {
        jaratok = (Jarat*)realloc(jaratok, jaratokMeret * sizeof(*jaratok));
        jaratok[i] = tempJarat;
        i++;
        jaratokMeret++;
    }
    jaratokMeret--;

  /*  for(int j = 0; j < jaratokMeret; j++) {
        printf("%s %d %d %d %s %s %d\n", jaratok[j].azonosito, jaratok[j].idopont.ev, jaratok[j].idopont.honap, jaratok[j].idopont.nap, jaratok[j].honnan, jaratok[j].hova, jaratok[j].ferohely);
    }*/

  Datum ido1 = {2019, 12, 20};
  Datum ido2 = {2021, 12, 21};

  //jaratKeres(jaratok, jaratokMeret, "Budapest", "New York city", ido1, ido2);








    /* menü */

    int menupont = 0;


    while(menupont != 5) {
        printf("Válassz egyet az alábbi menüpontok közül:\n");
        printf("1.: Járat keresése\n");
        printf("2.: Repülõjegy foglalása\n");
        printf("3.: Foglalás törlése\n");
        printf("4.: Összesítés\n");
        printf("5.: Kilépés\n");
        scanf("%d",&menupont);

        if(menupont == 1) {
            fflush(stdin);
            printf("Honnan kíván utazni?");
            char honnan[50];
            gets(honnan);
            printf("Hova kíván utazni?");
            char hova[50];
            gets(hova);

            printf("Mi legyen az indulási dátum?");
            Datum idopont_kezdo;
            scanf("%d/%d/%d", &(idopont_kezdo.ev), &(idopont_kezdo.honap), &(idopont_kezdo.nap));
            while(hibaKeres(idopont_kezdo)) {
                printf("Hibás Dátum formátum, kérlek próbáld újra\n");
                scanf("%d/%d/%d", &(idopont_kezdo.ev), &(idopont_kezdo.honap), &(idopont_kezdo.nap));
            }
            Datum idopont_vegso;
            printf("Mi legyen a végsõ dátum?");
            scanf("%d/%d/%d", &(idopont_vegso.ev), &(idopont_vegso.honap), &(idopont_vegso.nap));
            while(hibaKeres(idopont_vegso)) {
                printf("Hibás Dátum formátum, kérlek próbáld újra\n");
                scanf("%d/%d/%d", &(idopont_vegso.ev), &(idopont_vegso.honap), &(idopont_vegso.nap));
            }
            jaratKeres(jaratok, jaratokMeret, honnan, hova, idopont_kezdo, idopont_vegso);
        }


    }

    fclose(fp);
    free(jaratok);
    return 0;
}
