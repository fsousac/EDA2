#include <stdio.h>
#include <stdlib.h>

// HT = HashTable = Tabela Hash
//  para um vetor o intervalo fechado é [0,262143]
#define HTSIZE 5000
#define HTNULL -1
#define hash(v) (v % HTSIZE)

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
    lista_st *pLE;
    int count;
} HT_st;

void HTinit(HT_st *HT)
{
    HT->pLE = malloc(sizeof(lista_st) * HTSIZE);
    HT->count = 0;

    // elemento vazio da tabela hash será o -1
    for (int i = 0; i < HTSIZE; i++)
        LEinit(&HT->pLE[i]);
}

void HTinsert(HT_st *HT, int x)
{
    int hashv = hash(x);
    LEinsert(&HT->pLE[hashv], x);
    HT->count++;
}

int HTsearch(HT_st *HT, int x)
{
    int hashv = hash(x);

    return LEsearch(&HT->pLE[hashv], x);
}

int main()
{
    int N = -1;
    while (1)
    {
        scanf("%d", &N);
        if (N == 0)
            break;
        HT_st hashtable;
        HTinit(&hashtable);
        for (int i = 0; i < N; i++)
        {
            int pato;
            scanf("%d", &pato);
            HTinsert(&hashtable, pato);
        }
        lista_st mf = {NULL, 0};
        for (int i = 0; i < HTSIZE; i++)
        {
            if (hashtable.pLE[i].head == NULL)
                continue;
            if (hashtable.pLE[i].count > mf.count)
            {
                mf.count = hashtable.pLE[i].count;
                mf.head = hashtable.pLE[i].head;
            }
        }
        printf("%d\n", mf.head->value);
    }

    printf("\n");
    return 0;
}