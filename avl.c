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


// Funcao recursiva de insercao de elemento:
no *avl_insere(no *raiz, item *x, int *flag) {
    if (raiz != NULL) { // Arvore nao vazia.
        if (get_valor(x) < get_valor(raiz->info)) {
            raiz->esq = avl_insere(raiz->esq, x, flag); // Chama a insercao para a esquerda (elemento menor que raiz).
            if(*flag == 1) {
                switch(raiz->fb) {
                    case 1: // Caso em que o fator de balanceamento ficaria 2.
                        if(raiz->esq->fb == 1) { // Sinais iguais.
                            raiz = rotacao_DD(raiz); // Ajeitando os fatores de balanceamento apos a rotacao:
                            raiz->dir->fb = 0;
                            raiz->fb = 0;
                        } else { // Sinais diferentes.
                            raiz = rotacao_ED(raiz);
                            if(raiz->fb == -1) { // Ajeitando os fatores de balanceamento apos a rotacao:
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
                            raiz = rotacao_EE(raiz); // Ajeitando os fatores de balanceamento apos a rotacao:
                            raiz->esq->fb = 0;
                            raiz->fb = 0;
                        } else { // Sinais diferentes.
                            raiz = rotacao_DE(raiz);
                            if(raiz->fb == -1) { // Ajeitando os fatores de balanceamento apos a rotacao:
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
            return NULL;
        }
    } else { // Arvore vazia, entao insere elemento na raiz.
        raiz = (no *)malloc(sizeof(no));
        raiz->info = x;
        raiz->dir = NULL;
        raiz->esq = NULL;
        raiz->fb = 0;
        *flag = 1;
    }

    return raiz;
}


no *balanceamento_para_esquerda(no *p, int *h) {
    switch(p->fb) {
        case 1: // Altura foi alterada.
            p->fb = 0;
            break;
        case 0: // Altura nao foi alterada.
            p->fb = -1;
            *h = 0;
            break;
        case -1: // Altura alterada e desbalanceou a arvore.
            if(p->dir->fb  <= 0) { // Sinais iguais.
                p = rotacao_EE(p);
                // Ajeitando os fatores de balanceamento apos a rotacao:
                if(p->fb == 0) { 
                    p->esq->fb = -1;
                    p->fb = 1;
                    *h = 0; // pois a altura nao muda nesse caso de rotacao.
                } else {
                    p->esq->fb = 0;
                    p->fb = 0;
                }
            } else { // Sinais inversos.
                p = rotacao_DE(p);
                // Ajeitando os fatores de balanceamento apos a rotacao:
                if(p->fb == 1) {
                    p->esq->fb = 0;
                    p->dir->fb = -1;

                } else if(p->fb == -1) {
                    p->esq->fb = 1;
                    p->dir->fb = 0;
                } else { // p->fb == 0
                    p->esq->fb = 0;
                    p->dir->fb = 0;
                }
                p->fb = 0;
            }
            break;
    }
    return p;
}

no *balanceamento_para_direita(no *p, int *h) {
    switch(p->fb) {
        case -1: // Altura foi alterada.
            p->fb = 0;
            break;
        case 0: // Altura nao foi alterada.
            p->fb = 1;
            *h = 0;
            break;
        case 1: // Altura alterada e desbalanceou a arvore.
            if(p->esq->fb  >= 0) { // Sinais iguais.
                p = rotacao_DD(p);
                // Ajeitando os fatores de balanceamento apos a rotacao:
                if(p->fb == 0) { 
                    p->dir->fb = 1;
                    p->fb = -1;
                    *h = 0; // pois a altura nao muda nesse caso de rotacao.
                } else {
                    p->dir->fb = 0;
                    p->fb = 0;
                }
            } else { // Sinais inversos.
                p = rotacao_ED(p);
                // Ajeitando os fatores de balanceamento apos a rotacao:
                if(p->fb == 1) {
                    p->esq->fb = 0;
                    p->dir->fb = -1;

                } else if(p->fb == -1) {
                    p->esq->fb = 1;
                    p->dir->fb = 0;
                } else { // p->fb == 0
                    p->esq->fb = 0;
                    p->dir->fb = 0;
                }
                p->fb = 0;
            }
            break;
    }
    return p;
}


no *busca_e_remove(no *p, no *no_chave, int *h) {
    no *aux;

    if(p->dir != NULL) { // Percorre a subarvore ate chegar no elemento mais a direita (maior da subarvore).
        p->dir = busca_e_remove(p->dir, no_chave, h);
        if(*h == 1) {
            p = balanceamento_para_direita(p, h);
        }
    } else {
        // Sobrescreve o valor do 'no_chave' com o valor de 'p', que eh o maior valor da subarvore da esquerda.
        set_valor(no_chave->info, get_valor(p->info));
        aux = p;
        p = p->esq;
        apagar_item(&(aux->info));
        free(aux);
        *h = 1;
    }
    return p;
}


// Funcao recursiva de remocao de elemento:
no *avl_remove(no *raiz, int x, int *h, int *achou) {
    printf("Entrei no avl_remove.\n");
    no *aux;
    if(raiz == NULL) { // Arvore vazia ou fim de uma folha.
        printf("Chave nao foi encontrada.\n");
        *h = 0;
        *achou = 0;
    } else if(x < get_valor(raiz->info)) { // Elemento eh menor que a raiz, entao chama a remocao para a esquerda.
        raiz->esq = avl_remove(raiz->esq, x, h, achou);
        if(*h == 1) {
            raiz = balanceamento_para_esquerda(raiz, h);
        }
    } else if(x > get_valor(raiz->info)) { // Elemento eh maior que a raiz, entao chama a remocao para a direita.
        raiz->dir = avl_remove(raiz->dir, x, h, achou);
        if(*h == 1) {
            raiz = balanceamento_para_direita(raiz, h);
        }
    } else { // Encontrou o elemento na arvore, entao remove.
        printf("Encontrei o elemento %d, vou remover!\n", x);
        if(raiz->dir == NULL) {
            printf("Nao tem filho direito.\n");
            aux = raiz;
            raiz = raiz->esq;
            apagar_item(&(aux->info));
            printf("Apagaou o item de aux\n");
            *h = 1;
        } else if(raiz->esq == NULL) {
            printf("Nao tem filho esquerdo.\n");
            aux = raiz;
            raiz = raiz->dir;
            apagar_item(&(aux->info));
            *h = 1;
        } else {
            printf("Tem filho direito e esquerdo.\n");
            // Funcao para remover no com dois filhos:
            raiz->esq = busca_e_remove(raiz->esq, raiz, h);
            if(*h == 1) {
                raiz = balanceamento_para_esquerda(raiz, h);
            }
        }
    }
    avl_imprimir(raiz);
    return raiz;
}


// Funcao recursiva de busca no avl:
bool avl_busca(no *raiz, int chave) {
    if(raiz == NULL) {
        return false;
    } else if(get_valor(raiz->info) == chave) {
        return true;
    } else if(get_valor(raiz->info) > chave) {
        return avl_busca(raiz->esq, chave);
    } else {
        return avl_busca(raiz->dir, chave);
    }
}



void avl_imprimir(no *p){
    if(p != NULL){
        printf("%d(", get_valor(p->info));
        // chamando recursivamente para impressao
        avl_imprimir(p->esq);
        printf(",");
        avl_imprimir(p->dir);
        printf(")");
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