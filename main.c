/*CONSTANTINESCU Daria - 311CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int ComparareSateliti(void *a, void *b) {
    TSatelit *s1 = (TSatelit *)a;
    TSatelit *s2 = (TSatelit *)b;

    if (s1->frecventa != s2->frecventa)
        return s1->frecventa - s2->frecventa;

    return strcmp(s1->nume, s2->nume);
}

void transform_linie(char *linie) {
    char *p = linie + strlen(linie) - 1; // p este pointer catre finalul liniei
    while (p >= linie && (*p == ' ' || *p == '\n' || *p == '\r')) {
       *p = '\0';
       p--;
    }
 }

int main(int argc, char *argv[]) {
    if(argc != 4) {
        return 1;
    }
    
    FILE *fin, *fout;
    int nrtask = atoi(&argv[1][2]);

    fin = fopen(argv[2], "r");
    if(fin == NULL) {
        return 1;
    }

    fout = fopen(argv[3], "w");
    if(fout == NULL) {
        fclose(fin);
        return 1;
    }

    char linie[256];
    int nr_sat;
    fgets(linie, sizeof(linie), fin);
    transform_linie(linie);
    nr_sat = atoi(linie);

    THeap *heap = InitHeap(nr_sat, ComparareSateliti);
    
    for (int i = 0; i < nr_sat; i++) {
        int frecv;
        char nume[MAX_NUME];

        fgets(linie, sizeof(linie), fin);
        transform_linie(linie);
       
        sscanf(linie, "%d %s", &frecv, nume);

        TSatelit *s = CreeazaSatelit(frecv, nume, NULL, NULL);
        InserareHeap(heap, s);
    }

    TSatelit *radacina = ConstruiesteArbore(heap);
    if(nrtask == 1) {
    AfisareNiveluri(radacina, fout);
    }

    if(nrtask == 2) {
        fgets(linie, sizeof(linie), fin);
        transform_linie(linie);
        int nr_codif = atoi(linie);
        char cod[1001];

        for (int i = 0; i < nr_codif; i++) {
            fgets(cod, sizeof(cod), fin);
            transform_linie(cod);
            
            DecodificaMesaje(cod, radacina, fout);
        }
    }

    if(nrtask == 3) {
        fgets(linie, sizeof(linie), fin);
        transform_linie(linie);
        int nr_sat = atoi(linie);
        for (int i = 0; i < nr_sat; i++) {
            fgets(linie, sizeof(linie), fin);
            transform_linie(linie);

            char cod[1000];
            if (CautareCod(radacina, linie, cod, 0)) {
            fprintf(fout, "%s", cod);
            }
        }
    }

    if(nrtask == 4) {
        fgets(linie, sizeof(linie), fin);
        transform_linie(linie);
        int nr_sat = atoi(linie);

        char **sat = malloc(nr_sat * sizeof(char *));
        for(int i = 0; i < nr_sat; i++) {
            fgets(linie, sizeof(linie), fin);
            transform_linie(linie);
            sat[i] = strdup(linie);
        }

        TSatelit *comun = CautaParinte(radacina, sat, nr_sat);
        if (comun) {
            fprintf(fout, "%s\n", comun->nume); 
        }

        for (int i = 0; i < nr_sat; i++) {
            free(sat[i]);
        }
        free(sat);
    }

    FreeArbore(radacina);
    FreeHeap(heap);


    return 0;
}

