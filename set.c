#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"
#include "set.h"
#include "avl.h"


struct set {
    avl *conjunto;
};

//criando conjunto
SET *set_criar(void) {
    SET *A = (SET *) malloc(sizeof(SET));

    A->conjunto = avl_criar();

    return A;
}

// verificando se pertence
bool set_pertence(SET *A, int elemento) {
    if(A->conjunto == NULL) {
        exit(1);
    }

    // A verificacao de pertencimento se resume a uma busca na arvore:
    return avl_busca(A->conjunto->raiz, elemento);
}

//inserindo elemento
bool set_inserir (SET *s, int elemento) {
    item *x = criar_item(elemento);
    int flag = 0;
    no *p = avl_insere(s->conjunto->raiz, x, &flag);

    if(p == NULL) {
        return false;
    }

    s->conjunto->raiz = p;
    return true;
}

// removendo elemento
bool set_remover(SET *s, int elemento) {
    int flag = 0;
    int achou = 1;
    s->conjunto->raiz = avl_remove(s->conjunto->raiz, elemento, &flag, &achou);

    if(achou == 1) {
        return true;
    }
    return false;
}

//apagando conjunto
void set_apagar(SET **s) {
    deletar_AVL((*s)->conjunto->raiz);
    free((*s)->conjunto);
    (*s)->conjunto = NULL;
    free(*s);
    *s = NULL;
}

// imprimindo conjunto
void set_imprimir(SET *s) {
    //printf("Conjunto: ");
    avl_imprimir(s->conjunto->raiz);
}


void set_percorre(no *p, SET *conjunto_b, SET *conjunto_c, int operacao){

    if(p != NULL){
        switch (operacao) {
            case 0:
                if(set_pertence(conjunto_b, retorna_info(p))) {
                    set_inserir(conjunto_c, retorna_info(p));
                }
                break;
            
            case 1:
                if(!set_pertence(conjunto_b, retorna_info(p))) {
                    set_inserir(conjunto_c, retorna_info(p));
                }
                break;
            case 2:
                set_inserir(conjunto_c, retorna_info(p));
        }

        // percorrendo recursivamente:
        set_percorre(retorna_filho_esq(p), conjunto_b, conjunto_c, operacao);
                
        set_percorre(retorna_filho_dir(p), conjunto_b, conjunto_c, operacao);
    }
}


// verificando interseccoes entre conjuntos
SET *set_interseccao(SET *A, SET *B) {
    // Conjunto C = interseccao
    SET *C = set_criar();
    set_percorre(A->conjunto->raiz, B, C, 0);

    if (C->conjunto->raiz == NULL)
        printf(" Vazio \n");

    return C;
}


// unindo conjuntos
SET *set_uniao(SET *A, SET *B) {

    SET *C = set_criar();

    set_percorre(A->conjunto->raiz, A, C, 2);
    set_percorre(B->conjunto->raiz, A, C, 1);
    printf("Acabei de percorrer e preencher a uniao.\n");

    return C;
}
  