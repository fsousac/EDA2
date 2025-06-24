#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node
{
    int v;
    link next;
};

typedef struct
{
    int V;
    link *adj;
    int *type;
} *Graph;

int verde = 0, vermelha = 0, *pre;

Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->adj = malloc(V * sizeof(link));
    G->type = malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
        G->adj[i] = NULL;
    return G;
}

link NEW(int v, link next)
{
    link x = malloc(sizeof(*x));
    x->v = v;
    x->next = next;
    return x;
}

void GRAPHInsertE(Graph G, int v, int w)
{
    if (w == 0)
        return; // não insere galho inexistente
    G->adj[v] = NEW(w, G->adj[v]);
}

void dfs(Graph G, int v)
{
    pre[v] = 1;
    if (G->type[v] == 1)
        verde++;
    else if (G->type[v] == 2)
        vermelha++;
    for (link l = G->adj[v]; l; l = l->next)
        if (!pre[l->v])
            dfs(G, l->v);
}

int main()
{
    int N;
    scanf("%d", &N);
    Graph G = GRAPHinit(N);

    for (int i = 0; i < N; i++)
    {
        int tipo, L, R;
        scanf("%d %d %d", &tipo, &L, &R);
        G->type[i] = tipo;
        if (L != 0)
            GRAPHInsertE(G, i, L - 1);
        if (R != 0)
            GRAPHInsertE(G, i, R - 1);
    }

    for (int i = 0; i < N; i++)
    {
        if (G->type[i] == 0)
        {
            verde = 0;
            vermelha = 0;
            pre = calloc(N, sizeof(int));
            dfs(G, i);

            free(pre);
            printf("%d %d %d\n", i + 1, verde, vermelha);
        }
    }
    return 0;
}
