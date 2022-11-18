#ifndef AVL_H
#define AVL_H

#include "item.h"

typedef struct no_t no;

typedef struct avl_t {
    no *raiz;
} avl;


avl *avl_criar();


#endif