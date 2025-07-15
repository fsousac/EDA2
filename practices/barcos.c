
#include <stdio.h>
#include <stdlib.h>

#define INT_MAX __INT_MAX__

typedef struct node *link;
struct node
{
    int v;
    int c;
    link next;
};

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
    int c;
} Edge;

Edge EDGE(int v, int w, int c)
{
    Edge e;
    e.v = v;
    e.w = w;
    e.c = c;
    return e;
};

link NEW(int v, int c, link next)
{
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->v = v;
    x->c = c;
    x->next = next;
    return x;
}

Graph GRAPHinit(int totalV)
{
    Graph G = malloc(sizeof(*G));
    G->V = totalV;
    G->E = 0;
    G->adj = malloc((totalV + 1) * sizeof(link));
    for (int v = 1; v <= totalV; v++)
    {
        G->adj[v] = NULL;
    }
    return G;
};

void GRAPHInsertE(Graph G, Edge e)
{
    int v = e.v, w = e.w, c = e.c;
    G->adj[v] = NEW(w, c, G->adj[v]);
    G->adj[w] = NEW(v, c, G->adj[w]);
    G->E++;
}

int *pa, *mature, *dist;

void GRAPHcptD1(Graph G, int s, int d)
{
    for (int v = 1; v < G->V + 1; v++)
    {
        pa[v] = -1;
        mature[v] = 0;
        dist[v] = INT_MAX;
    }

    pa[s] = s;
    dist[s] = 0;

    while (1)
    {
        int min = INT_MAX;
        int y = -1;

        // encontra o vértice mais próximo ainda não processado
        for (int v = 1; v < G->V + 1; v++)
        {
            if (!mature[v] && ((min == INT_MAX && dist[v] < min) || (dist[v] > min && dist[v] < INT_MAX)))
            {
                min = dist[v];
                y = v;
            }
        }

        if (y == -1)
            break; // nenhum vértice restante acessível

        mature[y] = 1;

        // relaxamento das arestas de y
        for (link l = G->adj[y]; l != NULL; l = l->next)
        {
            int w = l->v;
            int custo = l->c;
            if (w == pa[y])
                continue;

            if (dist[y] != 0 && dist[y] < custo)
                custo = dist[y];

            if (dist[w] == INT_MAX)
            {
                dist[w] = custo;
                pa[w] = y;
            }
            else if (custo > dist[w])
            {
                dist[w] = custo;
                pa[w] = y;
            }
        }
    }
}

int main()
{
    int N, B;
    scanf("%d %d", &N, &B);
    Graph G = GRAPHinit(N);
    pa = malloc(sizeof(int) * (G->V + 1));
    mature = malloc(sizeof(int) * (G->V + 1));
    dist = malloc(sizeof(int) * (G->V + 1));
    for (int i = 0; i < B; i++)
    {
        int v, w, p;
        scanf("%d %d %d", &v, &w, &p);
        GRAPHInsertE(G, EDGE(v, w, p));
    }
    int c;
    scanf("%d", &c);
    int lastD = -1;
    for (int i = 0; i < c; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        if (x != lastD)
        {
            GRAPHcptD1(G, x, y);
            lastD = x;
        }
        // for (int i = 1; i < G->V + 1; i++)
        // {
        //     printf("%d ", dist[i]);
        // }
        // printf("\n");
        printf("%d\n", dist[y]);
    }

    return 0;
}