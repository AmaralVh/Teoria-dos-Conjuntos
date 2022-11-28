#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  SET *Conj_A;
  int num_a, num;
  int op;

  // Cria o conjunto:
  Conj_A = set_criar();

  // Recebe os tamanho do conjunto:
  scanf("%d", &num_a);
  printf("Recebi o tamanho do conjunto.\n");

  // Preenche o conjunto A:
  for(int i=0; i<num_a; i++) {
    scanf("%d",&num);
    set_inserir(Conj_A, num);

  }

  printf("Conjunto inteiro: ");
  set_imprimir(Conj_A);
  set_remover(Conj_A, 3);

  printf("\n\nConjunto apos a remocao: ");
  set_imprimir(Conj_A);

  set_apagar(&Conj_A);
  printf("\nConjunto apagado.\n");
    
  return 0;
}
