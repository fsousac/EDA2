#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

typedef struct
{
    int v;
    int w;
} Edge;

struct node
{
    int v;
    link next;
};

struct graph
{
    int V;
    int E;
    link *adj;
};

typedef struct graph *Graph;

Edge EDGE(int v, int w)
{
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

link NEW(int v, link next)
{
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->v = v;
    x->next = next;
    return x;
}

Graph GRAPHinit(int totalV)
{
    Graph G = malloc(sizeof(*G));
    G->V = totalV;
    G->E = 0;
    G->adj = malloc(totalV * sizeof(link));
    for (int v = 0; v < totalV; v++)
        G->adj[v] = NULL;
    return G;
}

// Insere aresta direcionada de v para w
void GRAPHInsertE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    G->adj[v] = NEW(w, G->adj[v]);
    G->E++;
}

// Remove aresta direcionada de v para w
void GRAPHRemoveE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    link *t = &G->adj[v];
    while (*t && (*t)->v != w)
        t = &(*t)->next;
    if (*t)
    {
        link toRemove = *t;
        *t = toRemove->next;
        free(toRemove);
        G->E--;
    }
}

// Retorna todas as arestas direcionadas do grafo
int GRAPHEdges(Edge a[], Graph G)
{
    int v, E = 0;
    link t;
    for (v = 0; v < G->V; v++)
    {
        for (t = G->adj[v]; t != NULL; t = t->next)
        {
            a[E++] = EDGE(v, t->v);
        }
    }
    return E;
}