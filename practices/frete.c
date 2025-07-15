#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

int *pq, *qp, PQN, PQsize;

void PQinit(int n)
{
    PQN = n;
    PQsize = 0;
    pq = malloc((n + 1) * sizeof(int));
    qp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        qp[i] = -1;
}

int PQempty()
{
    return PQsize == 0;
}

void exch(int i, int j)
{
    int t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void fixUp(int k, int *dist)
{
    while (k > 1 && dist[pq[k / 2]] > dist[pq[k]])
    {
        exch(k, k / 2);
        k = k / 2;
    }
}

void fixDown(int k, int *dist)
{
    int j;
    while (2 * k <= PQsize)
    {
        j = 2 * k;
        if (j < PQsize && dist[pq[j]] > dist[pq[j + 1]])
            j++;
        if (dist[pq[k]] <= dist[pq[j]])
            break;
        exch(k, j);
        k = j;
    }
}

void PQinsert(int v, int *dist)
{
    pq[++PQsize] = v;
    qp[v] = PQsize;
    fixUp(PQsize, dist);
}

int PQdelmin(int *dist)
{
    int min = pq[1];
    exch(1, PQsize--);
    fixDown(1, dist);
    qp[min] = -1;
    return min;
}

void PQdec(int v, int *dist)
{
    fixUp(qp[v], dist);
}

void PQfree()
{
    free(pq);
    free(qp);
}
void GRAPHcptD2(Graph G, int s, int *pa, int *dist)
{
    int *mature = malloc(sizeof(int) * (G->V + 1));
    for (int v = 1; v <= G->V; v++)
        pa[v] = -1, mature[v] = 0, dist[v] = INT_MAX;
    pa[s] = s, dist[s] = 0;
    PQinit(G->V);
    for (int v = 1; v <= G->V; v++)
        PQinsert(v, dist);

    while (!PQempty())
    {
        int y = PQdelmin(dist);
        if (dist[y] == INT_MAX)
            break;
        // atualização de dist[] e pa[]:
        for (link a = G->adj[y]; a != NULL; a = a->next)
        {
            int w = a->v;
            if (mature[w])
                continue;
            if (dist[y] + a->c < dist[w])
            {
                dist[w] = dist[y] + a->c;
                PQdec(w, dist);
                pa[w] = y;
            }
        }
        mature[y] = 1;
    }
    PQfree();
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    Graph G = GRAPHinit(N);
    for (int i = 0; i < M; i++)
    {
        int v, w, c;
        scanf("%d %d %d", &v, &w, &c);
        GRAPHInsertE(G, EDGE(v, w, c));
    }

    int *pa = malloc(sizeof(int) * (G->V + 1));
    int *dist = malloc(sizeof(int) * (G->V + 1));
    GRAPHcptD2(G, 1, pa, dist);
    printf("%d\n", dist[N]);

    return 0;
}