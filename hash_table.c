#include <stdio.h>
#include <stdlib.h>

// HT = HashTable = Tabela Hash
//  para um vetor o intervalo fechado é [0,262143]
#define HTSIZE 140000
#define HTNULL -1

typedef struct no
{
    int value;
    struct no *prox;
} no;

typedef struct lista_st
{
    no *head;
    int count;
} lista_st;

void LEinit(lista_st *lista)
{
    lista->head = NULL;
    lista->count = 0;
}

void LEinsert(lista_st *lista, int value)
{
    no *l = malloc(sizeof(no));
    l->value = value;
    l->prox = lista->head;
    lista->head = l;
    lista->count++;
}

int LEsearch(lista_st *lista, int x)
{
    no *aux = lista->head;
    while (aux != NULL)
    {
        if (aux->value == x)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

typedef struct HT_st
{
    lista_st *ht;
    int count;
} HT_st;

int hash(int value)
{
    return value % HTSIZE;
}

void HTinit(HT_st *HT)
{
    HT->ht = malloc(sizeof(lista_st) * HTSIZE);
    HT->count = 0;

    // elemento vazio da tabela hash será o -1
    for (int i = 0; i < HTSIZE; i++)
        LEinit(&HT->ht[i]);
}

void HTinsert(HT_st *HT, int x)
{
    int hashv = hash(x);
    LEinsert(&HT->ht[hashv], x);
    HT->count++;
}

int HTsearch(HT_st *HT, int x)
{
    int hashv = hash(x);

    return LEsearch(&HT->ht[hashv], x);
}