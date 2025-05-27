#include <stdio.h>
#include <stdlib.h>

struct graph
{
    int V;
    int E;
    int **adj;
};
typedef struct
{
    int v;
    int w;
} Edge;

Edge EDGE(int, int);

typedef struct graph *Graph;

Graph GRAPHinit(int totalV)
{
    Graph G = malloc(sizeof(*G));
    G->V = totalV;
    G->E = 0;
    G->adj = MATRIXinit(totalV, totalV, 0);
    return G;
}
void GRAPHInsertE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    if (G->adj[v][w] == 0)
        G->E++;
    G->adj[v][w] = 1;
    G->adj[w][v] = 1;
}
void GRAPHRemoveE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    if (G->adj[v][w] == 1)
        G->E--;
    G->adj[v][w] = 0;
    G->adj[w][v] = 0;
}
int GRAPHEdges(Edge a[], Graph G)
{
    int v, w, E = 0;
    for (v = 0; v < G->V; v++)
    {
        for (w = v + 1; w < G->V; w++)
        {
            if (G->adj[v][w] == 1)
            {
                a[E++] = EDGE(v, w);
            }
        }
    }
    return E;
}
Graph GRAPHCopy(Graph);
void GRAPHDestroy(Graph);