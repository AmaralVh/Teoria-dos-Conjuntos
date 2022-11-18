#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"

struct no_t {
    no *esq, *dir;
    item *info;
    int fb;
};

// Funcao que cria arvore avl:
avl *avl_criar() {
    avl *p = (avl *)malloc(sizeof(avl));

    p->raiz = NULL;

    return p;
}


no *rotacao_EE(no *desb) {
    no *aux = desb->dir;
    desb
}


no *avl_insere(no *raiz, item *x, int *flag) {
    if (raiz != NULL) {
        if (get_valor(x) < raiz->info) {
            raiz->esq = avl_insere(raiz->esq, x, flag);
            if(*flag == 1) {
                switch(raiz->fb) {
                    case 1:
                        if(raiz->esq->fb == 1) {
                            raiz = rotacao_DD(raiz);
                            raiz->dir->fb = 0;
                            raiz->fb = 0;
                        } else {
                            raiz = rotacao_ED(raiz);
                            if(raiz->fb == -1) {

                            } else if(raiz->fb == 1) {

                            } else { // raiz->fb == 0

                            }
                        }
                        break;
                    case 0:
                        raiz->fb = 1;
                        *flag = 1;
                        break;
                    case -1:
                        raiz->fb = 0;
                        *flag = 0;
                        break;
                }
            }
        } else if (get_valor(x) > raiz->info) {
            raiz->dir = avl_insere(raiz->dir, x, flag);
        } else {
            printf("Elemento ja existe no conjunto!\n");
        }
    } else {
        raiz = (no *)malloc(sizeof(no));
        raiz->info = x;
        raiz->dir = NULL;
        raiz->esq = NULL;
        raiz->fb = 0;
    }

    return raiz;
}

// Funcao de inserir elemento:
void avl_inserir(avl *p, item *x) {
    int flag = 0;
    p->raiz = avl_insere(p->raiz, x, &flag);
}