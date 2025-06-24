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
    int v;
    int w;
} Edge;

Edge EDGE(int v, int w)
{
    Edge e = {v, w};
    return e;
}

typedef struct graph *Graph;

struct graph
{
    int V;
    int E;
    link *adj;
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
}

void GRAPHInsertE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    G->adj[v] = NEW(w, G->adj[v]);
    G->E++;
}

// Employee satisfaction logic
int *salario;
int *chefe;
int *insatisfeito;

int checkInsatisfeito(Graph G, int u)
{
    for (link t = G->adj[u]; t != NULL; t = t->next)
    {
        if (salario[t->v] > salario[u])
        {
            insatisfeito[u] = 1;
            return 1;
        }
    }
    insatisfeito[u] = 0;
    return 0;
}

int totalInsatisfeitos(Graph G, int n)
{
    int total = 0;
    for (int i = 1; i <= n; i++)
    {
        total += checkInsatisfeito(G, i);
    }
    return total;
}

void atualizaSalario(Graph G, int func, int novoSalario)
{
    salario[func] = novoSalario;

    int ch = chefe[func];
    insatisfeito[ch] = checkInsatisfeito(G, ch);

    insatisfeito[func] = checkInsatisfeito(G, func);
}

int main()
{
    int n, a;
    scanf("%d", &n);
    Graph G = GRAPHinit(n + 1);

    salario = malloc((n + 1) * sizeof(int));
    chefe = malloc((n + 1) * sizeof(int));
    insatisfeito = calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++)
    {
        int c, s;
        scanf("%d %d", &c, &s);
        chefe[i] = c;
        salario[i] = s;
        if (i != 1)
            GRAPHInsertE(G, EDGE(c, i));
    }

    printf("%d\n", totalInsatisfeitos(G, n));

    scanf("%d", &a);
    for (int i = 0; i < a; i++)
    {
        int id, novoSalario;
        scanf("%d %d", &id, &novoSalario);
        atualizaSalario(G, id, novoSalario);

        printf("%d\n", totalInsatisfeitos(G, n));
    }
    return 0;
}
