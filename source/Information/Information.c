#include <stdlib.h>
#include "Information.h"

Info* cria_Info(int cpf, char *nome, char *profissao) {
    Info* info = (Info*) malloc(sizeof(Info));
    if (info == NULL) { //Erro na alocação da estrutura da informação
        return NULL;
    }

    info->CPF = cpf;
    info->Nome = nome;
    info->Profissao = profissao;
    return info;
}

void libera_Info(Info* info) {
    if (info == NULL)
        return;

    free(info->Nome);
    info->Nome = NULL;
    free(info->Profissao);
    info->Nome = NULL;
    free(info);
    info = NULL;
}