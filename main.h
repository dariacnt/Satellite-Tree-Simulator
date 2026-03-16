/*CONSTANTINESCU Daria - 311CB*/
#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>   
#include <stdlib.h>  
#include <stddef.h>   
#define MAX_NUME 16

typedef struct Satelit {
    int frecventa;
    char *nume;
    struct Satelit *st, *dr;
} TSatelit;

typedef int (*TFCmp)(void*, void*);

typedef struct Heap {
    int nrMax, nrElem;
    TSatelit **v;
    TFCmp comp;
} THeap;

THeap *InitHeap(int nrMax, TFCmp comp);
void InserareHeap(THeap *h, TSatelit *elem);
TSatelit *ExtragereHeap(THeap *h);
int ComparareSateliti(void *a, void *b);
TSatelit *CreeazaSatelit(int frecv, const char *nume, TSatelit *st, TSatelit *dr);
TSatelit *ConstruiesteArbore(THeap *heap);
void AfisareNiveluri(TSatelit *rad, FILE *fout);
void FreeArbore(TSatelit *rad);
void DecodificaMesaje(char *cod, TSatelit *radacina, FILE *fout);
int CautareCod(TSatelit *nod, const char *nume, char *cod, int nivel);
int GasesteCale(TSatelit *nod, const char *nume, TSatelit **cale, int nivel) ;
TSatelit *CautaParinte(TSatelit *radacina, char **nume_sateliti, int nr);
void FreeHeap(THeap *heap);
#endif
