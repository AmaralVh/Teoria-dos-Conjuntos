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

    A = avl_criar();

    return A;
}

// verificando se pertence
bool set_pertence(SET *A, int elemento) {

}

//inserindo elemento
bool set_inserir (SET *s, int elemento) {

}

// removendo elemento
bool set_remover(SET *s, int elemento) {

}

//apagando conjunto
void set_apagar(SET **s) {

}

// imprimindo conjunto
void set_imprimir(SET *s) {

}

// unindo conjuntos
SET *set_uniao(SET *A, SET *B) {

}

// verificando interseccoes entre conjuntos
SET *set_interseccao(SET *A, SET *B) {

}

  