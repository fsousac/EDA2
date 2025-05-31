#include <stdio.h>
#include <stdlib.h>

// HT = HashTable = Tabela Hash
//  para um vetor o intervalo fechado é [0,262143]
#define HTSIZE 140007
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
int main()
{
    int S, F, E;
    scanf("%d %d %d", &S, &F, &E);
    int vote, cValid = 0, cInvalid = 0;
    HT_st hashtable;
    HTinit(&hashtable);
    while ((scanf("%d", &vote)) != EOF)
    {
        if (vote >= 0)
            cValid++;
        else
            cInvalid++;
        HTinsert(&hashtable, vote);
    }

    printf("%d %d\n", cValid, cInvalid);
    // Verifica presidente
    int presV[2] = {0, 0}, presC[2] = {0, 0};
    for (int i = 0; i < 100; i++)
    {
        if (hashtable.ht[i].head == NULL)
            continue;
        if (hashtable.ht[i].count > presC[0])
        {
            presC[0] = hashtable.ht[i].count;
            presV[0] = hashtable.ht[i].head->value;
        }
        else if (hashtable.ht[i].count > presC[1])
        {
            presC[1] = hashtable.ht[i].count;
            presV[1] = hashtable.ht[i].head->value;
        }
    }
    if (presC[0] == presC[1])
        printf("Segundo turno\n");
    else
        printf("%d\n", presV[0]);

    // // Verifica Senador
    // int *senV = calloc(S, sizeof(int));
    // int *senC = calloc(S, sizeof(int));
    // for (int i = 100; i < 1000; i++)
    // {
    //     if (hashtable->ht[i].head == NULL)
    //         continue;
    //     for (int k = 0; k < S; k++)
    //     {
    //         if (hashtable->ht[i].count > senC[k])
    //         {
    //             senC[k] = hashtable->ht[i].count;
    //             break;
    //         }
    //     }
    // }

    return 0;
}