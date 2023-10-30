#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

typedef struct NO *ArvBin;

// Criando e destruindo uma árvore
ArvBin *cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);

// Informações básicas
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);

// Percorrendo uma Árvore Binária
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

// Inserção em Árvore Binária de Busca
int insere_ArvBin(ArvBin *raiz, int valor);

// Remoção em Árvore Binária de Busca
int remove_ArvBin(ArvBin *raiz, int valor);
struct NO *remove_atual(struct NO *atual);

// Consulta em Árvore Binária de Busca
int consulta_ArvBin(ArvBin *raiz, int valor);

#endif