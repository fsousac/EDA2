#include <stdlib.h>
#include <stdio.h>

#define hash(v, m) ((v) % (m))
// 2ª hash garante coprimalidade se M for primo
#define hashtwo(v) (((v) % (M - 1)) + 1)
#define MaxCol 10

typedef struct
{
    int key;
    int value;
} Item;
#define NULLITEM (Item){-1, 0}

extern int eq(int a, int b);
extern int Key(Item x);
extern void error(void);

Item *ht;     // tabela de itens
Item z;       // tombstone (deleção suave)
int M = 1007; // capacidade atual

void STinit(int M)
{
    ht = malloc(M * sizeof(Item));
    for (int i = 0; i < M; i++)
        ht[i] = NULLITEM;
    // definição de z como tombstone deve ser feita antes de usar HTremove
    // por exemplo: z = /* um Item cujo Key é distinto de qualquer chave válida */;
}

int HTinsert(Item ni)
{
    int k = Key(ni);
    int h = hash(k, M);
    int h2 = hashtwo(k);
    int c;
    int first = -1;

    for (c = MaxCol; c > 0; c--, h = (h + h2) % M)
    {
        Item cur = ht[h];
        if (eq(Key(cur), Key(NULLITEM)))
        {
            // encontrou vaga livre: escolha-a (se não houver tombstone antes)
            if (first < 0)
                first = h;
            break;
        }
        if (eq(Key(cur), Key(z)))
        {
            // tombstone: pode reutilizar, mas continue procurando chave existente
            if (first < 0)
                first = h;
            continue;
        }
        if (eq(Key(cur), k))
        {
            // já existe: insere sobre ela
            first = h;
            break;
        }
    }

    if (first < 0)
        return 0; // falha por excesso de colisões

    ht[first] = ni;
    return 1;
}

void STinsert(Item ni)
{
    if (!HTinsert(ni))
        error();
}

Item HTsearch(int k)
{
    int h = hash(k, M);
    int h2 = hashtwo(k);
    int c = MaxCol;

    while (c-- > 0)
    {
        Item cur = ht[h];
        if (eq(Key(cur), k))
            return cur;
        if (eq(Key(cur), Key(NULLITEM)))
            break; // chegou em área nunca usada
        h = (h + h2) % M;
    }
    return NULLITEM;
}

void HTremove(int k)
{
    int h = hash(k, M);
    int h2 = hashtwo(k);
    int c = MaxCol;

    while (c-- > 0)
    {
        Item cur = ht[h];
        if (eq(Key(cur), k))
        {
            ht[h] = z; // marca tombstone
            return;
        }
        if (eq(Key(cur), Key(NULLITEM)))
            return; // não encontrado
        h = (h + h2) % M;
    }
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
