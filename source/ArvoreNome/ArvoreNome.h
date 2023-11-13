#ifndef ARVORE_NOME_H
#define ARVORE_NOME_H

#include "../Information/Information.h"


//      Definição da estrutura da Árvore de Nome
typedef struct t_no_nome NoNome;
//      Definição do tipo da Árvore de Nome
typedef NoNome* ArvoreNome;


//      Criando e destruindo uma árvore
ArvoreNome* cria_ArvNome();
Info** libera_ArvNome(ArvoreNome *raiz);

//      Informações básicas
int estaVazia_ArvNome(ArvoreNome *raiz);
int altura_ArvNome(ArvoreNome *raiz);
int totalNO_ArvNome(ArvoreNome *raiz);

//       Percorrendo uma Árvore Binária
void preOrdem_ArvNome(ArvoreNome *raiz);
void emOrdem_ArvNome(ArvoreNome *raiz);
void posOrdem_ArvNome(ArvoreNome *raiz);


//      Inserção em Árvore Binária de Busca
int insere_ArvNome(ArvoreNome *raiz, Info *info);

//      Remoção em Árvore Binária de Busca
Info* remove_ArvNome(ArvoreNome *raiz, char *nome);
NoNome* remove_atual_nome(NoNome *atual);

//      Consulta em Árvore Binária de Busca
Info* consulta_ArvNome(ArvoreNome *raiz, char *nome);

#endif