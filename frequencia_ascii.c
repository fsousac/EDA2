#include <stdio.h>
#include <stdlib.h>

// HT = HashTable = Tabela Hash
#define HTSIZE 137
#define NULLITEM -1
#define hash(v, m) (v % m)
#define hashtwo(v) (v % 97 + 1)
#define MaxCol 10

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
    int *ht;
    int count;
} HT_st;

void HTinit(HT_st *HT)
{
    HT->ht = malloc(sizeof(int) * HTSIZE);
    HT->count = 0;

    // elemento vazio da tabela hash será o -1
    for (int i = 0; i < HTSIZE; i++)
        HT->ht[i] = NULLITEM;
}

void HTinsert(HT_st *HT, int x)
{
    int h = hash(x, HTSIZE);
    int h2 = hashtwo(x);
    int c, hn = -1;
    for (c = MaxCol; c > 0; c--, h = (h + h2) % HTSIZE)
    {
        if (eq(HT->ht[h], NULLITEM))
            hn = h;
        else if (eq(HT->ht[h], x))
        {
            hn = h;
            break;
        }
    }

    if (hn == -1)
        return 0;
    HT->ht[hn] = x;
    return 1;
}

int HTsearch(HT_st *HT, int x)
{
    int hashv = hash(x, HTSIZE);

    return LEsearch(&HT->ht[hashv], x);
}

int main()
{
    char *text = malloc(sizeof(char) * 1000);
    while ((scanf("%s", text)) != EOF)
    {
        HT_st hashtable;
        HTinit(&hashtable);
        for (int i = 0; text[i] != '\0'; i++)
        {
            HTinsert(&hashtable, text[i]);
        }
        for (int k = 1; k <= 1000; k++)
        {
            for (int i = 0; i < HTSIZE; i++)
            {
                if (hashtable.ht[i].head == NULL || hashtable.ht[i].count != k)
                    continue;
                printf("%d %d\n", hashtable.ht[i].head->value, hashtable.ht[i].count);
            }
        }
        printf("\n");
    }

    return 0;
}
