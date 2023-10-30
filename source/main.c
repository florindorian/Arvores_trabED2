#include "ArvoreBinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QTD 7
int dados[QTD];

// PROTÓTIPOS DAS FUNÇÕES
void exibeMenu();
void verDetalhes(ArvBin *raiz);

int main() {
  // DEFINIÇÕES
  // srand(time(0)); // Se desabilitado, mantém a mesma seed
  int res = 0, opcao = 0, valor;
  ArvBin *raiz = cria_ArvBin();

  // GERAÇÃO DOS NÚMEROS ALEATÓRIOS
  for (int i = 0; i < QTD; i++) {
    dados[i] = rand() % 100 + 1;

    for (int j = 0; j < i; j++) {
      if (dados[j] == dados[i]) {
        i--;
        break;
      }
    }
  }

  // INSERÇÃO DOS DADOS NA ÁRVORE
  for (int i = 0; i < QTD; i++) {
    res = insere_ArvBin(raiz, dados[i]);
    if (res == 0) {
      printf("\nNao foi possivel inserir o valor: %d\n", dados[i]);
    }
  }

  // EXIBIÇÃO INICIAL
  verDetalhes(raiz);

  // GERENCIANDO A ÁRVORE
  do {
    exibeMenu();
    printf("\nOpcao escolhida: ");
    if (scanf("%d", &opcao) != 1) {
      printf("Erro na leitura da opcao!\n");
      exit(1);
    }

    switch (opcao) {
    case 0:
      break;
    case 1:
      printf("Valor a ser inserido: ");
      if (scanf("%d", &valor) != 1) {
        printf("Erro na leitura da opcao!\n");
        exit(1);
      }
      if (insere_ArvBin(raiz, valor)) {
        printf("Valor %d inserido com sucesso!\n", valor);
      } else {
        printf("Falha na insercao!!!\n");
      }
      break;
    case 2:
      printf("Valor a ser removido: ");
      if (scanf("%d", &valor) != 1) {
        printf("Erro na leitura da opcao!\n");
        exit(1);
      }
      if (consulta_ArvBin(raiz, valor)) {
        remove_ArvBin(raiz, valor);
        printf("Valor %d removido com sucesso!\n", valor);
      } else {
        printf("O valor %d nao existe na arvore!\n", valor);
      }
      break;
    case 3:
      printf("Valor a ser consultado: ");
      if (scanf("%d", &valor) != 1) {
        printf("Erro na leitura da opcao!\n");
        exit(1);
      }
      printf("Valor %d existe na arvore? %s\n", valor,
             consulta_ArvBin(raiz, valor) ? "Sim" : "Nao");
      break;
    case 4:
      verDetalhes(raiz);
      break;
    default:
      printf("Valor invalido!!!\n");
    }
    printf("Tecle <enter>\n");
    getchar();
    getchar();

  } while (opcao != 0);

  // LIBERANDO A ÁRVORE
  libera_ArvBin(raiz);

  printf("Fim do programa!\n");
  return 0;
}

void exibeMenu() {
  printf("\n");
  printf("GERENCIADOR DE ARVORE BINARIA\n");
  printf("=============================\n");
  printf("<0> Sair\n");
  printf("<1> Inserir um valor\n");
  printf("<2> Remover um valor\n");
  printf("<3> Consultar um valor\n");
  printf("<4> Ver detalhes sobre a arvore\n");
}

void verDetalhes(ArvBin *raiz) {
  // RESULTADOS
  printf("\n--------------------------------");
  printf("\nSequencia de valores original:\n");
  for (int i = 0; i < QTD; i++) {
    printf("%d ", dados[i]);
  }
  printf("\n\nCaminhamento pre-ordem:\n");
  preOrdem_ArvBin(raiz);
  printf("\nCaminhamento em ordem:\n");
  emOrdem_ArvBin(raiz);
  printf("\nCaminhamento pos-ordem:\n");
  posOrdem_ArvBin(raiz);

  printf("\n\nMais informacoes:\n");
  printf("Esta vazia? \t\tR: %d\n", estaVazia_ArvBin(raiz));
  printf("Altura da arvore? \tR: %d\n", altura_ArvBin(raiz));
  printf("Total de nos? \t\tR: %d\n", totalNO_ArvBin(raiz));
  printf("--------------------------------\n");
}