#ifndef INFORMATION_H
#define INFORMATION_H

//      Definição da estrutura do DADO a ser armazenado na Árvore de CPF e Árvore Nome
typedef struct{
    int CPF;
    char* Nome;
    char* Profissao;
} Info;

Info* cria_Info(int cpf, char *nome, char *profissao);

void libera_Info(Info* info);

#endif
