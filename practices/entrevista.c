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

Edge EDGE(int v, int w)
{
    Edge e;
    e.v = v;
    e.w = w;
    return e;
};

int **MATRIXinit(int r, int c, int val)
{
    int **m = malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++)
    {
        m[i] = malloc(c * sizeof(int));
        for (int j = 0; j < c; j++)
            m[i][j] = val;
    }
    return m;
}

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

int main()
{
    int N;
    scanf("%d", &N);

    Graph G = GRAPHinit(N);
    int friend = -1;
    for (int i = 0; i < N; i++)
    {
        char c;
        scanf("%c", &c);

        for (int j = 0; j < N; j++)
        {
            scanf("%c", &c);
            if (c == '1')
            {
                GRAPHInsertE(G, EDGE(i, j));
            }
        }
    }
    int E;
    scanf("%d", &E);
    for (int i = 0; i < E; i++)
    {
        int q, part;
        scanf("%d", &q);
        int *cand = malloc(sizeof(int) * q);
        for (int k = 0; k < q; k++)
        {
            scanf("%d", &part);
            cand[k] = part - 1;
        }
        char res = 'N';
        for (int j = 0; j < q; j++)
        {
            for (int k = 0; k < q; k++)
            {
                if (res == 'N' && G->adj[cand[j]][cand[k]] == 1)
                {
                    res = 'S';
                    break;
                }
            }
        }
        printf("%c\n", res);
    }

    return 0;
}