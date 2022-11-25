#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  SET *Conj_A, *Conj_B;
  int num_a, num_b, num;
  int op;

// Cria os dois conjuntos:
  Conj_A = set_criar();
  Conj_B = set_criar();

// Recebe os tamanhos dos conjuntos:
  scanf("%d %d", &num_a, &num_b);

// Preenche o conjunto A:
  for(int i=0; i<num_a; i++) {
    scanf("%d",&num);
    set_inserir(Conj_A, num);

  }
// Preenche o conjunto B:
  for(int i=0; i<num_b; i++) {
    scanf("%d",&num);
    set_inserir(Conj_B, num);

  }

// Recebe a operacao a ser feita:
  scanf("%d", &op);

  switch(op) {
    // verificar se pertence
    case 1: {
              int aux;
              scanf("%d", &aux);
              if(set_pertence(Conj_A,aux)) 
                printf("Pertence.");
              else
                printf("Nao Pertence.");
              break;
    } // Uni conjuntos
    case 2: {
              SET *Conj_C = set_uniao(Conj_A,Conj_B);
              set_imprimir(Conj_C);
              set_apagar(&Conj_C);
              break;
    } // ve a interseccao
    case 3: {
              SET *Conj_C = set_interseccao(Conj_A, Conj_B);
              set_imprimir(Conj_C);
              set_apagar(&Conj_C);
              break;
    } // remove num
    case 4: { 
              int aux;
              scanf("%d", &aux);
              set_remover(Conj_A,aux);
              set_imprimir(Conj_A); 
    }
  }

  set_apagar(&Conj_A);
  set_apagar(&Conj_B);
    
  return 0;
}
