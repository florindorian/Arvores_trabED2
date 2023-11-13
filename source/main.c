#include "Information/Information.h"
#include "ArvoreCPF/ArvoreCPF.h"
#include "ArvoreNome/ArvoreNome.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//      PROTÓTIPOS DAS FUNÇÕES
void detalhes_ArvCPF(ArvoreCPF *raiz);
void detalhes_ArvNome(ArvoreNome *raiz);
void menuEmpresa();
int codigoOpcao(char* opcao);

int main() {
    //      DECLARAÇÃO
    int cpf;
    char *nome, *profissao;
    int codigo, res;
    char opcao[3];
    Info *info = NULL, *infoRemover = NULL;
    ArvoreCPF *raiz = cria_ArvCPF();
    ArvoreNome *raizNome = cria_ArvNome();

    if (raiz == NULL) {
        printf("Erro na alocacao da raiz de CPFs");
        exit(1);
    }
    if (raizNome == NULL) {
        printf("Erro na alocacao da raiz de Nomes");
        exit(1);
    }

    //      EXIBIÇÃO INICIAL
    detalhes_ArvCPF(raiz);

    //      GERENCIANDO A ÁRVORE
    do {
        menuEmpresa();
        printf("\nOpcao escolhida: ");
        if (scanf(" %2[^\n]", opcao) != 1) {
            printf("Erro na leitura da opcao!\n");
            exit(1);
        }
        opcao[2] = '\0';
        codigo = codigoOpcao(opcao);

        switch (codigo) {
            case 0: //      Código para: s
                break;

            case 1: //      Código para: i
                nome = (char*) malloc(sizeof(char) * 50);
                profissao = (char*) malloc(sizeof(char) * 30);

                printf("\nInsira os dados no seguinte formato:\n");
                printf("<nome_sem_espacos> <CPF> <profissão_sem_espacos>\n");
                printf("> ");
                if ((scanf("%s", nome) && scanf("%d", &cpf) && scanf(" %s", profissao)) == 0){
                    printf("\nErro de leitura dos dados a serem inseridos!\n");
                    free(nome);
                    free(profissao);
                    break;
                }

                info = cria_Info(cpf, nome, profissao);
                if (info == NULL) {
                    printf("\nErro na alocacao da estrutura da informacao!\n");
                    break;
                }

                res = insere_ArvCPF(raiz, info);
                if (res) {
                    printf("\nInformacao inserida com sucesso!\n");
                } else {
                    printf("\nFalha na insercao!!!\n");
                }

                //      Criação e inserção de elementos na árvore de nome
                res = insere_ArvNome(raizNome, info);
                if (res) {
                    printf("\nInformacao inserida com sucesso!\n");
                } else {
                    printf("\nFalha na insercao!!!\n");
                }
                break;

            case 2: //      Código para: rn
                nome = (char*) malloc (sizeof(char) * 50);
                printf("Nome do funcionario a ser removido: ");
                if (scanf("%s", nome) != 1) {
                    printf("\nErro na leitura da opcao!\n");
                    free(nome);
                    break;
                }

                infoRemover = consulta_ArvNome(raizNome,nome);
                if (infoRemover != NULL) {
                    remove_ArvNome(raizNome, nome);
                    remove_ArvCPF(raiz, infoRemover->CPF);
                    // Desalocação da informação encontrada:
                    free(infoRemover);
                    infoRemover = NULL;
                    printf("\nFuncionario removido com sucesso!\n");
                } else {
                    printf("\nFuncionario nao registrado no sistema. Nao e possivel remove-lo!\n");
                }
                free(nome);
                break;

            case 3: //      Código para: rc
                printf("CPF do funcionario a ser removido: ");
                if (scanf("%d", &cpf) != 1) {
                    printf("\nErro na leitura da opcao!\n");
                    break;
                }

                infoRemover = consulta_ArvCPF(raiz, cpf);
                if (infoRemover != NULL) {
                    remove_ArvCPF(raiz, cpf);
                    remove_ArvNome(raizNome, infoRemover->Nome);
                    // Desalocação da informação encontrada:
                    free(infoRemover);
                    infoRemover = NULL;
                    printf("\nFuncionario removido com sucesso!\n");
                } else {
                    printf("\nFuncionario nao registrado no sistema. Nao e possivel remove-lo!\n");
                }
                break;

            case 4: //      Código para: bn
                nome = (char*) malloc(sizeof(char) * 50);
                printf("Nome a ser buscado: ");
                if (scanf("%s", nome) != 1) {
                    printf("\nErro na leitura da opcao!\n");
                    break;
                }
                info = consulta_ArvNome(raizNome, nome);
                if (info == NULL) {
                    printf("0\n");
                } else {
                    printf("%s %d %s\n", info->Nome, info->CPF, info->Profissao);
                }
                break;

            case 5: //      Código para: bc
                printf("CPF a ser buscado: ");
                if (scanf("%d", &cpf) != 1) {
                    printf("\nErro na leitura da opcao!\n");
                    break;
                }
                info = consulta_ArvCPF(raiz, cpf);
                if (info == NULL) {
                    printf("0\n");
                } else {
                    printf("%s %d %s\n", info->Nome, info->CPF, info->Profissao);
                }
                break;
            case 10: //     Código para: an
                detalhes_ArvNome(raizNome);
                break;

            case 11: //     Código para: ac
                detalhes_ArvCPF(raiz);
                break;

            default: //     Código -1 para qualquer outro caso
                printf("Valor invalido!!!\n");
        }
        printf("Tecle <enter>\n");
        getchar();
        getchar();

    } while (codigo != 0);

    //      LIBERANDO AS ÁRVORES
    int n_nos = totalNO_ArvCPF(raiz);
    libera_ArvCPF(raiz);
    Info** conjuntoInfos = libera_ArvNome(raizNome);

    //      Desaloca todo ponteiro Info* do array
    for (int i = 0; i < n_nos; i++) {
        libera_Info(conjuntoInfos[i]);
    }

    printf("Programa finalizado!\n");
    return 0;
}

void detalhes_ArvCPF(ArvoreCPF *raiz) {
    //      RESULTADOS
    printf("\n--------------------------------");
    printf("\nCaminhamento pre-ordem:\n");
    preOrdem_ArvCPF(raiz);
    printf("\nCaminhamento em ordem:\n");
    emOrdem_ArvCPF(raiz);
    printf("\nCaminhamento pos-ordem:\n");
    posOrdem_ArvCPF(raiz);

    printf("\n\nMais informacoes:\n");
    printf("Esta vazia? \t\tR: %d\n", estaVazia_ArvCPF(raiz));
    printf("Altura da arvore? \tR: %d\n", altura_ArvCPF(raiz));
    printf("Total de nos? \t\tR: %d\n", totalNO_ArvCPF(raiz));
    printf("--------------------------------\n");
}

void detalhes_ArvNome(ArvoreNome *raiz) {
    //      RESULTADOS
    printf("\n--------------------------------");
    printf("\nCaminhamento pre-ordem:\n");
    preOrdem_ArvNome(raiz);
    printf("\nCaminhamento em ordem:\n");
    emOrdem_ArvNome(raiz);
    printf("\nCaminhamento pos-ordem:\n");
    posOrdem_ArvNome(raiz);

    printf("\n\nMais informacoes:\n");
    printf("Esta vazia? \t\tR: %d\n", estaVazia_ArvNome(raiz));
    printf("Altura da arvore? \tR: %d\n", altura_ArvNome(raiz));
    printf("Total de nos? \t\tR: %d\n", totalNO_ArvNome(raiz));
    printf("--------------------------------\n");
}

void menuEmpresa() {
    printf("\n");
    printf("=============================\n");
    printf("GERENCIAMENTO DE FUNCIONARIOS\n");
    printf("=============================\n");
    printf("[i]  Inserir novo funcionario no sistema\n");
    printf("[rn] Remover funcionario por nome\n");
    printf("[rc] Remover funcionario por CPF\n");
    printf("[bn] Buscar funcionario por nome\n");
    printf("[bc] Buscar funcionario por CPF\n");
    printf("[an] Ver detalhes sobre a arvore de nomes\n");
    printf("[ac] Ver detalhes sobre a arvore de CPFs\n");
    printf("[s]  Sair do programa\n");
}

//      Função que converte os comandos tipo "string" inseridos pelo usuário em códigos tipo "int"
int codigoOpcao(char* opcao) {
    if (strcmp(opcao, "i") == 0)
        return 1;
    if (strcmp(opcao, "rn") == 0)
        return 2;
    if (strcmp(opcao, "rc") == 0)
        return 3;
    if (strcmp(opcao, "bn") == 0)
        return 4;
    if (strcmp(opcao, "bc") == 0)
        return 5;
    if (strcmp(opcao, "s") == 0)
        return 0;

    //      Funcionalidades extras:
    if (strcmp(opcao, "an") == 0)
        return 10;
    if (strcmp(opcao, "ac") == 0)
        return 11;

    //      Código default, retornado quando o usuário escolhe uma opção não válida
    return -1;
}