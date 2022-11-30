#ifndef AVL_H
#define AVL_H

#include <stdbool.h>
#include "item.h"
#include "set.h"

typedef struct no_t no;

typedef struct avl_t
{
    no *raiz;
} avl;

avl *avl_criar();

no *avl_insere(no *raiz, item *x, int *flag);

no *avl_remove(no *raiz, int x, int *h, int *achou);

bool avl_busca(no *raiz, int chave);

void avl_imprimir(no *p);

void avl_percorre(no *p, SET *conjunto_b, SET *conjunto_c, int operacao);

bool esta_vazia(avl *p);

void deletar_AVL(no *p);

#endif