/*CONSTANTINESCU Daria - 311CB*/
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

THeap* InitHeap(int nrMax, TFCmp comp) {
    THeap* h = (THeap*) malloc(sizeof(struct Heap));
    if (h == NULL) {
        return NULL;
    }

    h->v = malloc(nrMax * sizeof(TSatelit *));
    if (h->v == NULL) {
		free(h);
		return NULL;
	}

    h->nrMax = nrMax;
    h->nrElem = 0;
    h->comp = comp;

    return h;
}

void Swap(TSatelit **a, TSatelit **b) {
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}

void InserareHeap(THeap *h, TSatelit *elem) {
    if (h->nrElem == h->nrMax)
        return;

    int i = h->nrElem++;
    h->v[i] = elem;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (h->comp(h->v[i], h->v[p]) >= 0)
            break;

        Swap(&h->v[i], &h->v[p]);
        i = p;
    }
}

TSatelit *ExtragereHeap(THeap *h) {
    if (h->nrElem == 0)
        return NULL;

    TSatelit *min = h->v[0];
    h->v[0] = h->v[--h->nrElem];

    int i = 0;
    while (1) {
        int st = 2 * i + 1;
        int dr = 2 * i + 2;
        int minP = i;

        if (st < h->nrElem && h->comp(h->v[st], h->v[minP]) < 0)
            minP = st;

        if (dr < h->nrElem && h->comp(h->v[dr], h->v[minP]) < 0)
            minP = dr;

        if (minP == i)
            break;

        Swap(&h->v[i], &h->v[minP]);
        i = minP;
    }

    return min;
}

TSatelit *CreeazaSatelit(int frecv, const char *nume, TSatelit *st, TSatelit *dr) {
    TSatelit *s = malloc(sizeof(TSatelit));
    if (s == NULL) return NULL;

    s->frecventa = frecv;
    s->st = st;
    s->dr = dr;

    if (st == 0 && dr == 0) {

        if (strlen(nume) > 15) {
            free(s);
            return NULL;
        }

        s->nume = strdup(nume);
        if (s->nume == NULL) {
            free(s);
            return NULL;
        }

    } else {

        int lun = strlen(st->nume) + strlen(dr->nume) + 1;

        s->nume = malloc(lun);
        if (s->nume == NULL) {
            free(s);
            return NULL;
        }

        strcpy(s->nume, st->nume);
        strcat(s->nume, dr->nume);

    }

    return s;
}

TSatelit *ConstruiesteArbore(THeap *h) {
    while (h->nrElem > 1) {
        TSatelit *s1 = ExtragereHeap(h);
        TSatelit *s2 = ExtragereHeap(h);

        int frecvNoua = s1->frecventa + s2->frecventa;

        TSatelit *satNou = CreeazaSatelit(frecvNoua, NULL, s1, s2);
        if (satNou == NULL) {
            FreeArbore(s1);
            FreeArbore(s2);
            continue;
        }
        InserareHeap(h, satNou);
    }

    return ExtragereHeap(h);
}

void DecodificaMesaje(char *cod, TSatelit *radacina, FILE *fout) {
    int poz = 0;
    int l = strlen(cod);

    while (poz < l) {

        TSatelit *sCur = radacina;
        while (sCur->st != NULL || sCur->dr != NULL) {

            if (poz >= l) {
                fprintf(fout, "\n");
                return;
            }

            if (cod[poz] == '0') {
                sCur = sCur->st;
            } else {
                sCur = sCur->dr;
            }

            poz++;
        }
        fprintf(fout, "%s ", sCur->nume);
    }
    fprintf(fout, "\n");
}

int CautareCod(TSatelit *sCur, const char *nume, char *cod, int nivel) {
    if (sCur == NULL) return 0;

    if (strcmp(sCur->nume, nume) == 0) {
        cod[nivel] = '\0';
        return 1;
    }

    cod[nivel] = '0';
    if (CautareCod(sCur->st, nume, cod, nivel + 1)) {
        return 1;
    }

    cod[nivel] = '1';
    if (CautareCod(sCur->dr, nume, cod, nivel + 1)) {
        return 1;
    }

    return 0;
}

int GasesteCale(TSatelit *sCur, const char *nume, TSatelit **cale, int nivel) {
    if (sCur == NULL) return 0;

    cale[nivel] = sCur;

    if (strcmp(sCur->nume, nume) == 0) {
        return 1;
    }

    if (GasesteCale(sCur->st, nume, cale, nivel + 1) ||
        GasesteCale(sCur->dr, nume, cale, nivel + 1)) {
        return 1;
    }

    return 0;
}

TSatelit *CautaParinte(TSatelit *radacina, char **nume_sateliti, int nr) {
    TSatelit *cale[100][100]; 
    memset(cale, 0, sizeof(cale));
    int lungime_cale[100];

    for (int i = 0; i < nr; i++) {
        if (GasesteCale(radacina, nume_sateliti[i], cale[i], 0) == 0) {
            return NULL;
        }

        int j = 0;
        while (cale[i][j]) j++;
        lungime_cale[i] = j;
    }

    int minim = 999;
    for (int i = 0; i < nr; i++)
        if (lungime_cale[i] < minim)
            minim = lungime_cale[i];

    TSatelit *comun = NULL;
    for (int i = 0; i < minim; i++) {

        TSatelit *sCur = cale[0][i];
        int ok = 1;

        for (int j = 1; j < nr; j++) {
            if (cale[j][i] != sCur) {
                ok = 0;
                break;
            }
        }

        if (ok)
            comun = cale[0][i];
         else 
            break;
        
    }

    return comun;
}


void AfisareNiveluri(TSatelit *rad, FILE *fout) {
    if (rad == NULL) return;

    TSatelit **aux = malloc(1000 * sizeof(TSatelit *));
    int inc = 0, sf = 0;
    aux[sf++] = rad;

    while (inc < sf) {
        int nivel = sf - inc;

        for (int i = 0; i < nivel; i++) {

            TSatelit *sCur = aux[inc++];

            fprintf(fout, "%d-%s ", sCur->frecventa, sCur->nume);

            if (sCur->st != NULL) 
                aux[sf++] = sCur->st;
            
            if (sCur->dr != NULL)
                aux[sf++] = sCur->dr;
        }
        fprintf(fout, "\n");
    }

    free(aux);
}

void FreeHeap(THeap *h) {
    if (h == NULL) return;

    for (int i = 0; i < h->nrElem; i++) {
        if (h->v[i]) {
            free(h->v[i]->nume);
            free(h->v[i]);
        }
    }

    free(h->v);
    free(h);
}

void FreeArbore(TSatelit *rad) {
    if (rad == NULL) return;
    FreeArbore(rad->st);
    FreeArbore(rad->dr);
    free(rad->nume);
    free(rad);
}


