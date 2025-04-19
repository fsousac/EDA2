#include <stdio.h>

typedef struct STNode *link;
#define Item int
#define NULLITEM NULL
enum tipo
{
    RED,
    BLACK
}; // Define que tipo só pode assumir RED ou BLACK
#define RED 0
#define BLACK 1

struct STNode
{
    Item item;
    link l, r;
    int N;
    int color;
};

link h, z;

link NEW(Item item, link l, link r, int N)
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

int STCount()
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

link insertR(link r, Item item)
{
    if (r == z)
        return NEW(item, z, z, 1);
    int k = Key(item), t = Key(r->item);
    if (less(k, t))
        r->l = insertR(r->l, item);
    else
        r->r = insertR(r->r, item);
    (r->N)++;

    if (isRed(r->r) && !isRed(r->l))
        r = rotateL(r);
    if (isRed(r->l) && isRed(r->l->l))
        r = rotateR(r);
    if (isRed(r->l) && isRed(r->r))
        flipColors(r);
    r->N = r->l->N + r->r->N + 1;
    return r;
}

// Wrapper
void STinsert(Item item)
{
    h = insertR(h, item);
}

Item seachR(link r, int k)
{
    if (r == z)
        return NULLITEM;
    int t = Key(r->item);
    if (eq(k, t))
        return r->item;
    if (less(k, t))
        return searchR(r->l, k);
    return searchR(r->r, k);
}

// Wrapper
Item STsearch(int k)
{
    return searchR(h, k);
}