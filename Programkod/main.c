#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    /* menü */

    printf("Válassz egyet az alábbi menüpontok közül:\n");
    printf("1.: Járat keresése\n");
    printf("2.: Repülõjegy foglalása\n");
    printf("3.: Foglalás törlése\n");
    printf("4.: Összesítés\n");
    printf("5.: Kilépés\n");








    int menupont;
    scanf("%d",&menupont);

    while(menupont != 5) {
        printf("Válassz egyet az alábbi menüpontok közül:\n");
        printf("1.: Járat keresése\n");
        printf("2.: Repülõjegy foglalása\n");
        printf("3.: Foglalás törlése\n");
        printf("4.: Összesítés\n");
        printf("5.: Kilépés\n");
        int menupont;
        scanf("%d",&menupont);
    }


    return 0;
}
