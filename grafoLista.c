#include <stdio.h>
#include <stdlib.h>

struct node
{
    int v;
    link next;
};
typedef struct node *link;

struct graph
{
    int V;
    int E;
    link *adj;
};
typedef struct graph *Graph;

typedef struct
{
    int v;
    int w;
} Edge;

Edge EDGE(int, int);

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
    {
        G->adj[v] = NULL;
    }
    return G;
};

void GRAPHInsertE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    G->adj[v] = NEW(w, G->adj[v]);
    G->adj[w] = NEW(v, G->adj[v]);
    G->E++;
}
void GRAPHRemoveE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    G->adj[v] = G->adj[w]->next;
    G->adj[w] = G->adj[v]->next;
}

int GRAPHEdges(Edge a[], Graph G)
{
    int v, E = 0;
    link t;
    for (v = 0; v < G->V; v++)
    {
        for (t = G->adj[v]; t != NULL; t = t->next)
        {
            if (v < t->v)
            {
                a[E++] = EDGE(v, t->v);
            }
        }
    }
    return E;
}
Graph GRAPHCopy(Graph);
void GRAPHDestroy(Graph);