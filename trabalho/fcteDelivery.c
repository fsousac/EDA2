#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXORDERS 5000

typedef struct
{
    int v;
    int w;
    int c;
} Edge;

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

Edge EDGE(int v, int w, int c)
{
    Edge e;
    e.v = v;
    e.w = w;
    e.c = c;
    return e;
};

typedef struct graph *Graph;

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
}

// Insere aresta dirigida de v para w
void GRAPHInsertE(Graph G, Edge e)
{
    int v = e.v, w = e.w, c = e.c;
    G->adj[v] = NEW(w, c, G->adj[v]);
    G->E++;
}

// Lista encadeada de pedidos
typedef struct Order *OrderLink;

struct Order
{
    int destination;
    OrderLink next;
};

typedef struct
{
    int count;
    OrderLink head;
} OrderList;

OrderList initOrderList(int n)
{
    OrderList *qOrders = malloc(sizeof(*qOrders) * (n + 1));
    for (int i = 0; i <= n; i++)
    {
        qOrders[i].count = 0;
        qOrders[i].head = NULL;
    }
    return *qOrders;
}

void addOrder(OrderList *qOrders, int r, int d)
{
    OrderLink newOrder = malloc(sizeof(*newOrder));
    newOrder->destination = d;
    newOrder->next = qOrders[r].head;
    qOrders[r].head = newOrder;
}

int removeOrder(OrderList *qOrders, int r, int d)
{
    OrderLink *p = &qOrders[r].head;
    while (*p)
    {
        if ((*p)->destination == d)
        {
            OrderLink tmp = *p;
            *p = (*p)->next;
            free(tmp);
            qOrders[r].count--;
            return 1; // sucesso
        }
        p = &(*p)->next;
    }
    return 0; // não encontrado
}

int hasOrder(OrderList *qOrders, int r)
{
    return qOrders[r].count > 0;
}

// DJIKSTRA

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

void GRAPHcptD2(Graph G, OrderList *o, int s, int *pa, int *dist)
{
    int mature[G->V + 1];
    for (int v = 0; v < G->V; ++v)
        pa[v] = -1, mature[v] = 0, dist[v] = INT_MAX;
    pa[s] = s, dist[s] = 0;
    PQinit(G->V + 1);
    for (int v = 1; v <= G->V; ++v)
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

// Iteractive functions

void refuel(int *tank, int *station)
{
    printf("a\n");
    int temp;
    scanf("%d", &temp);
    if (*station == tankMax)
    {
        *station = temp;
        *tank = tankMax;
    }
    else
    {
        *tank += *station - temp;
        *station = temp;
    }
}

int nearestRestaurant(OrderList *o, int *dist, int nodes)
{
    int km = INT_MAX, next = 0;
    for (int i = 1; i <= nodes; i++)
    {
        if (o[i].count > 0 && dist[i] < km)
        {
            km = dist[i];
            next = i;
        }
    }

    return next;
}

int nodes, streets, home, tankMax, startTank, bagSize, fuelNodes;
int main()
{
    // int N, M, H, T, I, C, P;
    scanf("%d %d %d %d %d %d %d", &nodes, &streets, &home, &tankMax, &startTank, &bagSize, &fuelNodes);
    int *gasStations = malloc(sizeof(int) * (nodes + 1));
    for (int i = 1; i <= nodes; i++)
        gasStations[i] = -1;

    for (int i = 0; i < fuelNodes; i++)
    {
        int temp;
        scanf("%d", &temp);
        gasStations[temp] = tankMax;
    }

    Graph G = GRAPHinit(nodes);

    for (int i = 0; i < streets; i++)
    {
        int v, w, c;
        scanf("%d %d %d", &v, &w, &c);
        GRAPHInsertE(G, EDGE(v, w, c));
    }

    int qRest;
    scanf("%d", &qRest);

    OrderList *qOrders = malloc((nodes + 1) * sizeof(*qOrders));
    for (int i = 1; i <= nodes; i++)
    {
        qOrders[i].count = 0;
        qOrders[i].head = NULL;
    }

    for (int i = 0; i < qRest; i++)
    {
        int node, orders;
        scanf("%d %d", &node, &orders);
        qOrders[node].count = orders;
        for (int k = 0; k < orders; k++)
        {
            int destiny;
            scanf("%d", &destiny);
            addOrder(qOrders, node, destiny);
        }
    }
    int cNode = home;
    int cTank = tankMax;
    int cBag = 0;
    int *pa = malloc((nodes + 1) * sizeof(int));
    int *dist = malloc((nodes + 1) * sizeof(int));
    GRAPHcptD2(G, qOrders, home, pa, dist);
    while (1)
    {
        if (gasStations[cNode] > 0 && cTank < tankMax)
        {
            refuel(cTank, gasStations[cNode]);
        }
        if (cBag == 0)
        {
            int destination = nearestRestaurant(qOrders, dist, nodes);
        }
    }

    return 0;
}