#include <stdio.h>
#include <stdlib.h>
#define size 1000000

int *pre, *st;

typedef struct node *link;
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

typedef struct Edge
{
    int v;
    int w;
} Edge;

Edge EDGE(int v, int w)
{
    Edge e = {v, w};
    return e;
};

link NEW(int v, link next)
{
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->v = v;
    x->next = next;
    return x;
}

typedef struct
{
    Edge data[size];
    int ini, fim;
} Queue;

Queue queue;

void QUEUEinit()
{
    queue.ini = queue.fim = 0;
}

int QUEUEempty()
{
    return queue.ini == queue.fim;
}

void QUEUEpush(Edge e)
{
    queue.data[queue.fim++] = e;
    if (queue.fim == size)
        queue.fim = 0; // circular
}

Edge QUEUEget()
{
    Edge e = queue.data[queue.ini++];
    if (queue.ini == size)
        queue.ini = 0; // circular
    return e;
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

void bfs(Graph G, Edge e)
{
    QUEUEinit();
    QUEUEpush(e);
    int cnt = 0;
    pre[e.w] = cnt++;
    while (!QUEUEempty())
    {
        int w = QUEUEget().w;
        for (link l = G->adj[w]; l != NULL; l = l->next)
        {
            if (pre[l->v] == -1)
            {
                QUEUEpush(EDGE(w, l->v));
                pre[l->v] = cnt++; // Para não visitar o mesmo vértice várias vezes
            }
        }
    }
}

int GraphSearch(Graph G)
{
    for (int i = 0; i < G->V; i++)
    {
        pre[i] = -1;
        st[i] = -1;
    }

    int cc = 0;

    for (int i = 0; i < G->V; i++)
    {
        if (pre[i] == -1)
        {
            cc++;
            bfs(G, EDGE(i, i));
        }
    }
    return cc;
}

int main()
{
    int N;
    scanf("%d", &N);
    Graph G = GRAPHinit(N);
    pre = malloc(sizeof(int) * N);
    st = malloc(sizeof(int) * N);
    int v, w;
    while (scanf("%d %d", &v, &w) != EOF)
    {
        GRAPHInsertE(G, EDGE(v, w));
    }
    printf("%d\n", GraphSearch(G));

    return 0;
}