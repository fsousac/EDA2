#include <stdio.h>
#include <stdlib.h>

typedef struct STNode *link;
#define NULLITEM -1
typedef enum tipo
{
    RED,
    BLACK
} tipo; // Define que tipo só pode assumir RED ou BLACK
#define RED 0
#define BLACK 1
#define less(A, B) ((A) < (B))
#define eq(A, B) ((A) == (B))
#define isRed(A) (A->color == RED)

struct STNode
{
    unsigned int item;
    link l, r;
    unsigned int N;
    tipo color;
};

link h, z;

link NEW(unsigned int item, link l, link r, unsigned int N)
{
    link x = malloc(sizeof(*x));
    x->item = item; // Equivalente a x.item = item
    x->l = l;
    x->r = r;
    x->N = N;
    x->color = RED; // Sempre tentamos aglutinar os nós na 2-3
    return x;
}

void STinit()
{
    h = (z = NEW(NULLITEM, 0, 0, 0));
    z->color = BLACK;
}

unsigned int STCount()
{
    return h->N;
}

void flipColors(link h)
{
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

link rotateRight(link r)
{
    link x = r->l;
    r->l = x->r;
    x->r = r;
    x->color = r->color;
    r->color = RED;
    x->N = r->N;
    r->N = 1 + r->l->N + r->r->N;
    return x;
}

link rotateLeft(link r)
{
    link x = r->r;
    r->r = x->l;
    x->l = r;
    x->color = r->color;
    r->color = RED;
    x->N = r->N;
    r->N = 1 + r->l->N + r->r->N;
    return x;
}

link insertR(link r, unsigned int item)
{
    if (r == z)
        return NEW(item, z, z, 1);
    unsigned int k = item, t = r->item;
    if (less(k, t))
        r->l = insertR(r->l, item);
    else
        r->r = insertR(r->r, item);
    (r->N)++;

    if (isRed(r->r) && !isRed(r->l))
        r = rotateLeft(r);
    if (isRed(r->l) && isRed(r->l->l))
        r = rotateRight(r);
    if (isRed(r->l) && isRed(r->r))
        flipColors(r);
    r->N = r->l->N + r->r->N + 1;
    return r;
}

// Wrapper
void STinsert(unsigned int item)
{
    h = insertR(h, item);
}

unsigned int searchR(link r, unsigned int k)
{
    if (r == z)
        return NULLITEM;
    unsigned int t = r->item;
    if (eq(k, t))
        return r->item;
    if (less(k, t))
        return searchR(r->l, k);
    return searchR(r->r, k);
}

// Wrapper
unsigned int STsearch(unsigned int k)
{
    return searchR(h, k);
}

int main()
{
    unsigned int ant, atual, prox, PTR1, PTR2;
    int count = 0;
    STinit();
    while (scanf("%llx %llx %llx", &atual, &ant, &prox) != EOF)
    {
        STinsert(atual);
        count++;
        if (count == 1)
        {
            PTR1 = atual;
            PTR2 = prox;
        }
        else if (count == 2)
        {
            if (ant != PTR1 || atual != PTR2)
                printf("insana\n");
            else
                printf("sana\n");
        }
        printf("%d\n", NULL);
        printf("%d %d %d\n", ant, atual, prox);
    }

    return 0;
}
