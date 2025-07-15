#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define INT_MAX __INT_MAX__
static int *queue, ini, fim, size;

void QUEUEinit(int n)
{
    ini = fim = 0;
    size = n;
    queue = malloc(sizeof(int) * n);
}

int QUEUEempty()
{
    return ini == fim;
}

void QUEUEput(int v)
{
    queue[fim++] = v;
    if (fim == size)
        fim = 0;
}

int QUEUEget()
{
    int v = queue[ini++];
    if (ini == size)
        ini = 0;
    return v;
}

int GRAPHcptBF(Graph G, int s, int *pa, int *dist)
{
    int onqueue[1000];
    for (int v = 0; v < G->V; v++)
        pa[v] = -1, dist[v] = INT_MAX, onqueue[v] = false;
    pa[s] = s;
    dist[s] = 0;
    QUEUEinit(G->E);
    QUEUEput(s);
    onqueue[s] = true;
    int V = G->V;
    QUEUEput(V);
    int k = 0;
    while (1)
    {
        int v = QUEUEget();
        if (v < V)
        {
            for (link a = G->adj[v]; a != NULL; a = a->next)
            {
                if (dist[v] + a->c < dist[a->v])
                {
                    dist[a->v] = dist[v] + a->c;
                    pa[a->v] = v;
                    if (onqueue[a->v] == false)
                    {
                        QUEUEput(a->v);
                        onqueue[a->v] = true;
                    }
                }
            }
        }
        else
        {
            if (QUEUEempty())
                return true;
            if (++k >= G->V)
                return false;
            QUEUEput(V);
            for (int t = 0; t < G->V; t++)
                onqueue[t] = false;
        }
    }
}