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

typedef struct
{
    int v;
    int capacity;
} gasPump;

// Restaurantes

#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    // int N, M, H, T, I, C, P;
    int nodes, streets, home, tankMax, startTank, bagSize, fuelNodes;
    scanf("%d %d %d %d %d %d %d", &nodes, &streets, &home, &tankMax, &startTank, &bagSize, &fuelNodes);
    gasPump *gasStations = malloc(sizeof(gasPump) * fuelNodes);
    for (int i = 0; i < fuelNodes; i++)
    {
        int temp;
        scanf("%d", &temp);
        gasPump gp;
        gp.v = temp;
        gp.capacity = tankMax;
        gasStations[i] = gp;
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

    return 0;
}