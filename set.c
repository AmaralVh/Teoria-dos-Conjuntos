#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"
#include "set.h"


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
    no *p = avl_remove(s->conjunto->raiz, elemento, &flag);

    if(p == NULL) {
        return false;
    }

    s->conjunto->raiz = p;
    return true;
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

// unindo conjuntos
SET *set_uniao(SET *A, SET *B) {

}

// verificando interseccoes entre conjuntos
SET *set_interseccao(SET *A, SET *B) {

}

  