#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  SET *Conj_A, *Conj_B;
  int num_a, num_b, num;
  int op = 0;

// Cria os dois conjuntos:
  Conj_A = set_criar();
  Conj_B = set_criar();

// Recebe os tamanhos dos conjuntos:
  printf("Coloque os tamanhos dos dois conjuntos A e B: ");
  scanf("%d %d", &num_a, &num_b);

// Preenche o conjunto A:
  printf("Preencha o conjunto A:\n");
  for(int i=0; i<num_a; i++) {
    scanf("%d",&num);
    if(set_inserir(Conj_A, num) == false) {
      i--;
    }
  }
// Preenche o conjunto B:
  printf("Preencha o conjunto B:\n");
  for(int i=0; i<num_b; i++) {
    scanf("%d",&num);
    if(set_inserir(Conj_B, num) == false) {
      i--;
    }
  }

while(op != -1) {
  // Recebe a operacao a ser feita:
    printf("\n[1] - Verificar se elemento pertence a um conjunto.\n");
    printf("[2] - Realizar uniao dos conjuntos.\n");
    printf("[3] - Verificar interseccao entre os conjuntos.\n");
    printf("[4] - Remover elemento de um conjunto.\n");
    printf("[-1] - Sair do programa.\n");
    printf("Digite a operacao que deseja fazer: ");
    scanf("%d", &op);

    switch(op) {
      // Verifica se pertence:
      case 1: {
                int elem;
                char conjunto;

                printf("[A] ou [B]\n");
                printf("Digite com qual dos conjuntos voce deseja verificar o pertencimento: ");
                scanf(" %c", &conjunto);
                printf("Digite o elemento que deseja verificar se pertence ao conjunto: ");
                scanf("%d", &elem);
                if(conjunto == 'A' || conjunto == 'a') {
                  if(set_pertence(Conj_A, elem)) 
                    printf("Pertence.\n");
                  else
                    printf("Nao Pertence.\n");
                } else if(conjunto == 'B' || conjunto == 'b'){
                  if(set_pertence(Conj_B, elem)) 
                    printf("Pertence.\n");
                  else
                    printf("Nao Pertence.\n");
                } else {
                  printf("Resposta invalida.\n");
                }
                break;
      } // Une conjuntos:
      case 2: {
                SET *Conj_C = set_uniao(Conj_A,Conj_B);
                printf("Uniao entre A e B:   ");
                set_imprimir(Conj_C);
                set_apagar(&Conj_C);
                break;
      } // Verifica a interseccao:
      case 3: {
                printf("Interseccao entre A e B:   ");
                SET *Conj_C = set_interseccao(Conj_A, Conj_B);
                set_imprimir(Conj_C);
                set_apagar(&Conj_C);
                break;
      } // Remove elemento:
      case 4: { 
                int elem;
                char conjunto;

                printf("[A] ou [B]\n");
                printf("Digite de qual dos conjuntos voce deseja remover o elemento: ");
                scanf(" %c", &conjunto);
                printf("Digite o elemento que deseja remover do conjunto: ");
                scanf("%d", &elem);

                if(conjunto == 'A' || conjunto == 'a') {
                  set_remover(Conj_A, elem);
                  printf("Conjunto A apos a remocao:   ");
                  set_imprimir(Conj_A); 
                } else if(conjunto == 'B' || conjunto == 'b') {
                  set_remover(Conj_B, elem);
                  printf("Conjunto B apos a remocao:   ");
                  set_imprimir(Conj_B); 
                } else {
                  printf("Resposta invalida.\n");
                }
                break; 
      }
      case -1:
                printf("Saindo do programa! Ate mais!\n");
                break;
    }
}

  set_apagar(&Conj_A);
  set_apagar(&Conj_B);
    
  return 0;
}
