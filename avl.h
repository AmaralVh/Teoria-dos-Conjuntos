#ifndef AVL_H
#define AVL_H

#include <stdbool.h>
#include "item.h"

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

bool esta_vazia(avl *p);

void deletar_AVL(no *p);

#endif