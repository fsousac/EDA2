#include <stdlib.h>
#include <stdio.h>

#define hash(v, m) ((v) % (m))
#define MaxCol 10

typedef struct
{
    int key;
    int value;
} Item;
#define NULLITEM (Item){-1, 0}
#define Key(A) ((A).key)
#define eq(A, B) ((A) == (B))
extern void error(void);

Item *ht;          // tabela de itens
Item z = NULLITEM; // tombstone (deleção suave)
int M;

void STinit(int HTSIZE)
{
    M = HTSIZE;
    ht = malloc(HTSIZE * sizeof(Item));
    for (int i = 0; i < HTSIZE; i++)
        ht[i] = NULLITEM;
    // definição de z como tombstone deve ser feita antes de usar HTremove
    // por exemplo: z = /* um Item cujo Key é distinto de qualquer chave válida */;
}

int HTinsert(Item ni)
{
    int h = hash(Key(ni), M);
    int c = MaxCol;

    while (c && !eq(Key(ht[h]), Key(NULLITEM)))
    {
        c--;
        h = (h + 1) % M;
    }
    if (!c)
        return 0;
    ht[h] = ni;
    return 1;
}

void STinsert(Item ni)
{
    if (!HTinsert(ni))
        STgrow(M + 1);
}

Item HTsearch(int k)
{
    int h = hash(k, M);
    int c = MaxCol;

    while (c && !eq(k, Key(ht[h])))
    {
        c--;
        h = (h + 1) % M;
    }

    if (!c)
        return NULLITEM;
    return ht[h];
}

void HTremove(int k)
{
    int h = hash(k, M);
    int c = MaxCol;
    while (c && !eq(Key(ht[h]), k))
    {
        c--;
        h = (h + 1) % M;
    }
    if (!c)
        return;
    ht[h] = NULLITEM;
}

void STgrow(int newMax)
{
    Item *oldHt = ht;
    int oldM = M;

    ht = malloc(newMax * sizeof(Item));
    M = newMax;
    for (int i = 0; i < M; i++)
        ht[i] = NULLITEM;

    // re-insere apenas itens válidos (não nulos e não tombstones)
    for (int i = 0; i < oldM; i++)
    {
        Item cur = oldHt[i];
        if (!eq(Key(cur), Key(NULLITEM)) && !eq(Key(cur), Key(z)))
            HTinsert(cur);
    }
    free(oldHt);
}

int main()
{
    STinit(1007);
    STinsert((Item){10, 100});
    STinsert((Item){111, 200});
    Item result = HTsearch(10);
    printf("%d\n", result.key);
    return 0;
}
