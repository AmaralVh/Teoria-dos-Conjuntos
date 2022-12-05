#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"
#include "set.h"
#include "avl.h"

// Estrutura de um conjunto (set):
struct set {
    avl *conjunto; // Ponteiro para um avl.
};

// Criando conjunto:
SET *set_criar(void) {
    SET *A = (SET *) malloc(sizeof(SET));

    A->conjunto = avl_criar();

    return A;
}

// Verificando se elemento pertence ao conjunto:
bool set_pertence(SET *A, int elemento) {
    if(A->conjunto == NULL) {
        exit(1);
    }

    // A verificacao de pertencimento se resume a uma busca na arvore:
    return avl_busca(A->conjunto->raiz, elemento);
}

// Inserindo elemento no conjunto:
bool set_inserir (SET *s, int elemento) {
    if(set_pertence(s, elemento)) {
        printf("Elemento %d ja existe no conjunto!\n", elemento);
        return false;
    }

    item *x = criar_item(elemento);
    int flag = 0;
    no *p = avl_insere(s->conjunto->raiz, x, &flag);

    s->conjunto->raiz = p;
    return true;
}

// Removendo elemento do conjunto:
bool set_remover(SET *s, int elemento) {
    int flag = 0;
    int achou = 1;
    s->conjunto->raiz = avl_remove(s->conjunto->raiz, elemento, &flag, &achou);

    if(achou == 1) {
        return true;
    }
    return false;
}

// Apagando conjunto:
void set_apagar(SET **s) {
    deletar_AVL((*s)->conjunto->raiz);
    free((*s)->conjunto);
    (*s)->conjunto = NULL;
    free(*s);
    *s = NULL;
}

// Imprimindo conjunto:
void set_imprimir(SET *s) {
    avl_imprimir(s->conjunto->raiz);
}

// Funcao que percorre um conjunto e insere elemento em outro, conforme uniao ou interseccao (operacao):
void set_percorre(no *p, SET *conjunto_b, SET *conjunto_c, int operacao){

    if(p != NULL){
        switch (operacao) {
            case 0:
                // Se elemento pertence a B, entao insere em C:
                if(set_pertence(conjunto_b, retorna_info(p))) {
                    set_inserir(conjunto_c, retorna_info(p));
                }
                break;
            
            case 1:
                // Se elemento nao pertence a B, entao insere em C:
                if(!set_pertence(conjunto_b, retorna_info(p))) {
                    set_inserir(conjunto_c, retorna_info(p));
                }
                break;
            case 2:
                // Sempre insere o elemento em C:
                set_inserir(conjunto_c, retorna_info(p));
        }

        // Percorrendo recursivamente:
        set_percorre(retorna_filho_esq(p), conjunto_b, conjunto_c, operacao);  
        set_percorre(retorna_filho_dir(p), conjunto_b, conjunto_c, operacao);
    }
}


// Verificando interseccoes entre conjuntos
SET *set_interseccao(SET *A, SET *B) {
    // Conjunto C = interseccao:
    SET *C = set_criar();
    
    // Chama a funcao mandando 0 como o ultimo argumento ('operacao' em set_percorre):
    set_percorre(A->conjunto->raiz, B, C, 0); // Percorrera conjunto A.

    if (C->conjunto->raiz == NULL) {
        printf(" Vazio \n");
    }

    return C;
}


// Unindo conjuntos
SET *set_uniao(SET *A, SET *B) {
    // Conjunto C = uniao:
    SET *C = set_criar();

    // Chama a funcao mandando 2 como o ultimo argumento ('operacao' em set_percorre):
    set_percorre(A->conjunto->raiz, A, C, 2); // Percorrera conjunto A.
    // Chama a funcao mandando 1 como o ultimo argumento ('operacao' em set_percorre):
    set_percorre(B->conjunto->raiz, A, C, 1); // Percorrera conjunto B.

    return C;
}
  