#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int dado;
    struct no *esq, *dir;
} no;

typedef struct stack_node
{
    struct no *data;
    struct stack_node *next;
} stack_node;

void push(stack_node **top, struct no *node)
{
    stack_node *new_node = (stack_node *)malloc(sizeof(stack_node));
    new_node->data = node;
    new_node->next = *top;
    *top = new_node;
}

struct no *pop(stack_node **top)
{
    if (*top == NULL)
    {
        return NULL;
    }
    stack_node *temp = *top;
    struct no *popped = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped;
}

int isEmpty(stack_node *top)
{
    return top == NULL;
}

void em_ordem(no *raiz)
{
    stack_node *stack = NULL;
    no *current = raiz;
    int first = 1;

    while (current != NULL || !isEmpty(stack))
    {
        while (current != NULL)
        {
            push(&stack, current);
            current = current->esq;
        }

        current = pop(&stack);
        if (first)
        {
            printf("%d", current->dado);
            first = 0;
        }
        else
        {
            printf(" %d", current->dado);
        }

        current = current->dir;
    }
}

// no *criar_no(int dado)
// {
//     no *novo = (no *)malloc(sizeof(no));
//     novo->dado = dado;
//     novo->esq = novo->dir = NULL;
//     return novo;
// }

// void liberar_arvore(no *raiz)
// {
//     if (raiz == NULL)
//         return;
//     liberar_arvore(raiz->esq);
//     liberar_arvore(raiz->dir);
//     free(raiz);
// }

// int main()
// {
//     // Construindo a árvore do exemplo
//     no *raiz = criar_no(2);
//     raiz->esq = criar_no(5);
//     raiz->esq->esq = criar_no(3);
//     raiz->esq->dir = criar_no(8);
//     raiz->esq->dir->esq = criar_no(4);
//     raiz->dir = criar_no(7);
//     raiz->dir->esq = criar_no(1);
//     raiz->dir->esq->dir = criar_no(9);
//     raiz->dir->dir = criar_no(6);

//     // Executando o percurso em ordem
//     em_ordem(raiz);
//     printf("\n"); // Adiciona quebra de linha após a saída

//     // Libera memória alocada
//     liberar_arvore(raiz);

//     return 0;
// }