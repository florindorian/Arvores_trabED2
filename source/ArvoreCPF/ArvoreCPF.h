#ifndef ARVORE_CPF_H
#define ARVORE_CPF_H

#include "../Information/Information.h"

//      Definição da estrutura da Árvore de CPF
typedef struct t_no_cpf No;
//      Definição do tipo da Árvore de CPF
typedef No* ArvoreCPF;

//      Criando e destruindo uma árvore
ArvoreCPF* cria_ArvCPF();
Info** libera_ArvCPF(ArvoreCPF *raiz);

//      Informações básicas
int estaVazia_ArvCPF(ArvoreCPF *raiz);
int altura_ArvCPF(ArvoreCPF *raiz);
int totalNO_ArvCPF(ArvoreCPF *raiz);

//      Percorrendo uma Árvore Binária
void preOrdem_ArvCPF(ArvoreCPF *raiz);
void emOrdem_ArvCPF(ArvoreCPF *raiz);
void posOrdem_ArvCPF(ArvoreCPF *raiz);

//      Inserção em Árvore Binária de Busca
int insere_ArvCPF(ArvoreCPF *raiz, Info *info);

//      Remoção em Árvore Binária de Busca
Info* remove_ArvCPF(ArvoreCPF *raiz, int valor);
No* remove_atual_CPF(No *atual);

//      Consulta em Árvore Binária de Busca
Info* consulta_ArvCPF(ArvoreCPF *raiz, int valor);

#endif