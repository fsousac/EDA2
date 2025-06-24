#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005

typedef struct node *link;

struct node
{
    int v;
    link next;
};

link adj[MAXN];
int salario[MAXN];
int chefe[MAXN];
int insatisfeito[MAXN];
int n, a;

void addEdge(int u, int v)
{
    link novo = malloc(sizeof(*novo));
    novo->v = v;
    novo->next = adj[u];
    adj[u] = novo;
}

int checkInsatisfeito(int u)
{
    for (link t = adj[u]; t != NULL; t = t->next)
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

int totalInsatisfeitos()
{
    int total = 0;
    for (int i = 1; i <= n; i++)
    {
        total += checkInsatisfeito(i);
    }
    return total;
}

void atualizaSalario(int func, int novoSalario)
{
    salario[func] = novoSalario;

    // Atualiza o chefe do funcionario
    int ch = chefe[func];
    insatisfeito[ch] = checkInsatisfeito(ch);

    // Atualiza o proprio funcionario
    insatisfeito[func] = checkInsatisfeito(func);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int c, s;
        scanf("%d %d", &c, &s);
        chefe[i] = c;
        salario[i] = s;
        if (i != 1) // o chefe de 1 é ele mesmo, n precisa adicionar aresta
            addEdge(c, i);
    }

    printf("%d\n", totalInsatisfeitos());

    scanf("%d", &a);
    for (int i = 0; i < a; i++)
    {
        int id, novoSalario;
        scanf("%d %d", &id, &novoSalario);
        atualizaSalario(id, novoSalario);

        printf("%d\n", totalInsatisfeitos());
    }

    return 0;
}
