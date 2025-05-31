#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

typedef struct
{
    int v;
    int w;
} Edge;

struct node
{
    int v;
    int salario;
    link next;
};

struct graph
{
    int V;
    int E;
    link *adj;
};

typedef struct graph *Graph;

Edge EDGE(int v, int w)
{
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

link NEW(int v, link next, int salario)
{
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->v = v;
    x->salario = salario;
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
        G->adj[v] = NULL;
    return G;
}

// Insere aresta direcionada de v para w
void GRAPHInsertE(Graph G, Edge e, int salario)
{
    int v = e.v, w = e.w;
    G->adj[v] = NEW(w, G->adj[v], salario);
    G->E++;
}

// Remove aresta direcionada de v para w
void GRAPHRemoveE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    link *t = &G->adj[v];
    while (*t && (*t)->v != w)
        t = &(*t)->next;
    if (*t)
    {
        link toRemove = *t;
        *t = toRemove->next;
        free(toRemove);
        G->E--;
    }
}

// Retorna todas as arestas direcionadas do grafo
int GRAPHEdges(Edge a[], Graph G)
{
    int v, E = 0;
    link t;
    for (v = 0; v < G->V; v++)
    {
        for (t = G->adj[v]; t != NULL; t = t->next)
        {
            a[E++] = EDGE(v, t->v);
        }
    }
    return E;
}

atualizaSalario(int func, int ns)
{
    int in = 0;
    if (ns > salario[func])
    {
        if (!insatisfeito[chefe[func]])
        {
            if (ns > salario[chefe[func]])
            {
                in++;
                insatisfeito[chefe[func]] = 1;
            }
        }
        if (insatisfeito[func])
        {
            salario[func] = ns;
            if (!checkInsatisfeito(func))
                in--;
        }
    }
    else
    {
        // Fazer dps
    }
}

int checkInsatisfeito(int i)
{
    for (link t = G->adj[i]; t != NULL; t = t->next)
    {
        if (salario[t->v] > salario[i])
        {
            insatisfeito[i];
            return 1;
        }
    }
    insatisfeito[i] = 0;
    return 0;
}

Graph G;
int *salario;
int *chefe;
int *insatisfeito;

int main()
{
    int qtdFunc;
    scanf("%d", &qtdFunc);
    // vetor de chefes
    chefe = malloc(sizeof(int) * qtdFunc + 1);
    salario = malloc(sizeof(int) * qtdFunc + 1);
    Graph G = GRAPHinit(qtdFunc);
    for (int i = 1; i <= qtdFunc; i++)
    {
        scanf("%d %d", &chefe[i], &salario[i]);
        GRAPHInsertE(G, EDGE(chefe[i], i), salario[i]);
    }
    free(&qtdFunc);
    // insatisfeitos inicial
    int insa = 0;
    for (int i = 1; i <= qtdFunc; i++)
    {
        insa += checkInsatisfeito(i);
    }
    printf("%d\n", insa);

    int mudancas;
    scanf("%d", &mudancas);
    for (int i = 0; i < mudancas; i++)
    {
        int func, ns;
        scanf("%d %d", &func, &ns);
        insa = atualizaSalario(func, ns);
    }

    return 0;
}
