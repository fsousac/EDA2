#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

typedef struct node
{
    int v;
    link next;
} node;

typedef struct
{
    link *adj;
    int V;
} Graph;

Graph *GRAPHinit(int V)
{
    Graph *G = malloc(sizeof(Graph));
    G->V = V;
    G->adj = malloc(V * sizeof(node *));
    for (int i = 0; i < V; i++)
        G->adj[i] = NULL;
    return G;
}

void GRAPHInsertE(Graph *G, int v, int w)
{
    node *n = malloc(sizeof(node));
    n->v = w;
    n->next = G->adj[v];
    G->adj[v] = n;
}

int main()
{
    int N, M, J;
    scanf("%d %d %d", &N, &M, &J);

    Graph *G = GRAPHinit(N);
    for (int i = 0; i < N; i++)
    {
        int A;
        scanf("%d", &A);
        for (int j = 0; j < A; j++)
        {
            int viz;
            scanf("%d", &viz);
            GRAPHInsertE(G, i, viz);
        }
    }

    char *pre = calloc(N, sizeof(char));
    for (int i = 0; i < M; i++)
    {
        int ido;
        scanf("%d", &ido);
        pre[ido] = 1;
        for (node *n = G->adj[ido]; n; n = n->next)
            pre[n->v] = 1;
    }

    for (int i = 0; i < J; i++)
    {
        int foi;
        scanf("%d", &foi);
        if (pre[foi])
            printf("Eu vou estar la\n");
        else
            printf("Nao vou estar la\n");
    }
    return 0;
}