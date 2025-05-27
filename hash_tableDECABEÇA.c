#include <stdio.h>
#include <stdlib.h>

#define hash(v) (v % M)
#define MaxCol 10

typedef struct noLE
{
    int key;
    struct noLE *prox;
} noLE;

typedef struct LEHead
{
    noLE *head;
    int count;
} LEHead;

typedef struct HT
{
    LEHead *LE;
    int count;
} HT;

HT *h;
noLE z = {-1, NULL};
int M;

int insertLE(LEHead *head, int k)
{
    if (head->count < 10)
    {
        noLE *ni = malloc(sizeof(noLE));
        ni->key = k;
        ni->prox = head;
        head->head = ni;
        head->count++;
        return 1;
    }
    return 0;
}

void LEinit(LEHead *cabeca)
{
    cabeca->head = NULL;
    cabeca->count = 0;
}

void HTinit(int size)
{
    h = malloc(sizeof(HT));
    M = size;
    h->LE = malloc(M * sizeof(LEHead));
    for (int i = 0; i < M; i++)
    {
        LEinit(&h->LE[i]);
    }
    h->count = 0;
}

int HTinsert(int k)
{
    int hashv = hash(k);
    return insertLE(&h->LE[hashv], k);
}

LEHead *HTsearch(int k)
{
    int hashv = hash(k);
    return &h->LE[hashv];
}

int main()
{
    HTinit(1007);
    HTinsert(7);
    HTinsert(7);
    HTinsert(112);
    LEHead *res = HTsearch(7);
    if (res->head == NULL)
        printf("Elemento não inserido\n");
    else
        printf("%d %dx\n", res->head->key, res->count);

    return 0;
}
