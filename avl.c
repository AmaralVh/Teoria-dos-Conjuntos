#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "avl.h"

// Estrutura de um no do avl:
struct no_t {
    no *esq, *dir;
    item *info;
    int fb; // Fator de balanceamento
};


// Funcao que cria arvore avl:
avl *avl_criar() {
    avl *p = (avl *)malloc(sizeof(avl));

    p->raiz = NULL;

    return p;
}

// Rotacao EE:
no *rotacao_EE(no *desb) {
    no *aux = desb->dir;
    desb->dir = aux->esq;
    aux->esq = desb;

    return aux;
}

// Rotacao DD:
no *rotacao_DD (no *desb){
    no *aux = desb->esq;
    desb->esq = aux->dir;
    aux->dir = desb;

    return aux;
}

// Rotacao ED (esquerda e direita):
no *rotacao_ED(no *desb){
    desb->esq = rotacao_EE(desb->esq);
    return rotacao_DD(desb);
}

// Rotacao DE (direita e esquerda):
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

// Funcao que realiza o balanceamento para a esquerda (utilizada na remocao):
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

// Funcao que realiza o balanceamento para a direita (utilizada na remocao):
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

// Funcao que busca o maior da esquerda e troca com a raiz:
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
        if(raiz->dir == NULL) {
            aux = raiz;
            raiz = raiz->esq;
            apagar_item(&(aux->info));
            *h = 1;
        } else if(raiz->esq == NULL) {
            aux = raiz;
            raiz = raiz->dir;
            apagar_item(&(aux->info));
            *h = 1;
        } else {
            // Funcao para remover no com dois filhos:
            raiz->esq = busca_e_remove(raiz->esq, raiz, h);
            if(*h == 1) {
                raiz = balanceamento_para_esquerda(raiz, h);
            }
        }
    }
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

// Funcao recursiva de imprimir avl:
void avl_imprimir(no *p){
    if(p != NULL){
        printf("%d(", get_valor(p->info));
        // Chamando recursivamente para impressao:
        avl_imprimir(p->esq);
        printf(",");
        avl_imprimir(p->dir);
        printf(")");
    }
    // Note que o percurso e pre-ordem/em profundidade.
    // Note tambem que colocamos parenteses e virgula para indicar 
    // relacionamento dos filhos com seu respectivo pai.
}


// Verificando se esta vazia:
bool esta_vazia(avl *p){
    assert(p != NULL);

    if(p->raiz == NULL)
        return true;

    return false;
}

// Funcao recursiva que deleta avl:
void deletar_AVL(no *p){ 
    if(p != NULL){
        deletar_AVL(p->esq);
        deletar_AVL(p->dir);
        apagar_item(&(p->info)); // Apaga o item (conteudo)
        free(p); // Libera o no da memoria
    }
}

// Funcao que retorna a informacao de um no:
int retorna_info(no *p) {
    return get_valor(p->info);
}

// Funcao que retorna o filho esquerdo de um no:
no *retorna_filho_esq(no *p) {
    return p->esq;
}

// Funcao que retorna o filho direito de um no:
no *retorna_filho_dir(no *p) {
    return p->dir;
}