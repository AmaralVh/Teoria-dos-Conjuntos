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

// remodelando caso rotacao EE
no *rotacao_EE(no *desb) {
    no *aux = desb->dir;
    desb->dir = aux->esq;
    aux->esq = desb;

    return aux;
}

// remodelando caso a rotacao DD
no *rotacao_DD (no *desb){
    no *aux = desb->esq;
    desb->esq = aux->dir;
    aux->dir = desb;

    return aux;
}
// remodelando caso haja 2 rotacao 
// caso ED
no *rotacao_ED(no *desb){
    desb->esq = rotacao_EE(desb->esq);
    return rotacao_DD(desb);
}

// caso DE
no *rotacao_DE(no *desb){
    desb->dir = rotacao_DD(desb->dir);
    return rotacao_EE(desb);
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
                                raiz->esq->fb = 1;
                                raiz->dir->fb = 0;
                                raiz->fb = 0;
                            } else if(raiz->fb == 1) {
                                raiz->esq->fb = 0;
                                raiz->dir->fb = -1;
                                raiz->fb = 0;
                            } else { // raiz->fb == 0
                                raiz->esq->fb = 0;
                                raiz->dir->fb = 0;
                                raiz->fb = 0;
                            }
                        }
                        *flag = 0;
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
            // FALTA FAZER AS ROTACOES PARA ESSE CASO AQUI ............
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