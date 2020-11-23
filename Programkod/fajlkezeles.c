#include "fajlkezeles.h"

char* beolvas(FILE* stream, char elvalaszto) {
    int meret = 0;
    char beolvasott = 0;
    char *tempSzoveg = NULL;
    char *Szoveg = NULL;

    beolvasott = getc(stream);

    if(beolvasott == elvalaszto) {
        meret++;
        Szoveg = (char *) malloc(meret * sizeof(char));
        Szoveg[0] = '\0';
    } else {
        int i = 2;
        while (beolvasott != elvalaszto) {
            meret++;
            tempSzoveg = (char *) malloc(meret * sizeof(char));
            if (i != 2) {
                for (int j = 0; j < meret - 1; j++) {
                    tempSzoveg[j] = Szoveg[j];
                }
            }
            free(Szoveg);
            Szoveg = (char *) malloc(meret * sizeof(char));
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
        tempJarat.hova = beolvas(fp,'\n');

        tempJarat.foglaltUlesek = NULL;
        jaratok = (Jarat*)realloc(jaratok, *jaratokMeret * sizeof(*jaratok));
        jaratok[i] = tempJarat;
        tempJarat.honnan = (char *) malloc(50 * sizeof(char));
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
        fprintf(fp, "%s#%d/%d/%d#%s#%s\n", jaratok[jarat].azonosito, jaratok[jarat].datum.ev, jaratok[jarat].datum.honap, jaratok[jarat].datum.nap, jaratok[jarat].honnan, jaratok[jarat].hova);
    }
    fclose(fp);
}
