#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    printf("Estou em avl_insere.\n");
    if (raiz != NULL) { // Arvore nao vazia.
        printf("Arvore nao eh vazia.\n");
        if (get_valor(x) < get_valor(raiz->info)) {
            raiz->esq = avl_insere(raiz->esq, x, flag); // Chama a insercao para a esquerda (elemento menor que raiz).
            if(*flag == 1) {
                switch(raiz->fb) {
                    case 1: // Caso em que o fator de balanceamento ficaria 2.
                        if(raiz->esq->fb == 1) { // Sinais iguais.
                            raiz = rotacao_DD(raiz);
                            raiz->dir->fb = 0;
                            raiz->fb = 0;
                        } else { // Sinais diferentes.
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
        } else if (get_valor(x) > get_valor(raiz->info)) { 
            raiz->dir = avl_insere(raiz->dir, x, flag); // Chama a insercao para a direita (elemento maior que raiz).
            if(*flag == 1) {
                switch(raiz->fb) {
                    case 1:
                        raiz->fb = 0;
                        *flag = 0;
                        break;
                    case 0:
                        raiz->fb = -1;
                        *flag = 1;
                        break;
                    case -1: // Caso em que o fator de balanceamento ficaria -2.
                        if(raiz->dir->fb == -1) { // Sinais iguais.
                            raiz = rotacao_EE(raiz);
                            raiz->esq->fb = 0;
                            raiz->fb = 0;
                        } else { // Sinais diferentes.
                            raiz = rotacao_DE(raiz);
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
                }
            }
        } else { // Achou um elemento existente igual ao que se quer inserir.
            printf("Elemento ja existe no conjunto!\n");
        }
    } else { // Arvore vazia, entao insere elemento na raiz.
        printf("Arvore eh vazia.\n");
        raiz = (no *)malloc(sizeof(no));
        raiz->info = x;
        printf("Valor da raiz agora eh %d\n", get_valor(raiz->info));
        raiz->dir = NULL;
        raiz->esq = NULL;
        raiz->fb = 0;
        *flag = 1;
        printf("Elemento inserido: %d\n", get_valor(raiz->info));
    }

    return raiz;
}

// Funcao de inserir elemento:
void avl_inserir(avl *p, item *x) {
    printf("Estou em avl_inserir.\n");
    int flag = 0;
    p->raiz = avl_insere(p->raiz, x, &flag);
}

void avl_imprimir(no *p){
    if(p != NULL){
        printf("%d ", get_valor(p->info));
        // chamando recursivamente para impressao
        avl_imprimir(p->esq);
        avl_imprimir(p->dir);
    }

}

//verificando se esta vazia
bool esta_vazia(avl *p){
    assert(p != NULL);

    if(p->raiz == NULL)
        return true;

    return false;
}

void deletar_AVL(no *p){ // FALAR COM ISAAC SOBRE O APAGAR_ITEM()
    if(p != NULL){
        deletar_AVL(p->esq);
        deletar_AVL(p->dir);
        apagar_item(&(p->info)); // Apaga o item (conteudo)
        free(p); // Libera o no da memoria
    }
}