#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

struct NO {
    int info;
    struct NO* esq;
    struct NO* dir;
};

//Criando e destruindo uma árvor
ArvBin* cria_ArvBin() {
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if (raiz != NULL) 
        *raiz = NULL;
    else {
        printf("Falha na alocacao!\n");
        exit(1); //Falha na alocação
    }    
    return raiz;
}

void libera_NO(struct NO* no) {
    if (no == NULL) 
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz) {
    if (raiz == NULL) 
        return;
    libera_NO(*raiz); //libera cada nó
    free(raiz); //libera a raíz
}


//Informações básicas
int estaVazia_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) { //Se houve algum erro de alocação, por exemplo
        return 1;
    } else if (*raiz == NULL) { //Se a árvore de fato não possui nenhum nó
        return 1;
    } else {
        return 0;
    }
}

/*PROBLEMA NO VÍDEO: [ED] Aula 72 - Árvore Binária: informações básicas 
    RETORNAR -1 ao invés de 0 no caso base
    LOGO: A função abaixo retorna a altura da árvore (caso exista) ou -1 caso esteja vazia.*/

//Aqui se recebe um "endereço do tipo ArvBin". ArvBin por sua vez guarda o endereço de um nó.
//Logo, é um endereço de um endereço de um nó que se espera se espera.
int altura_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) { //Se houve erro na alocação da árvore
        return 0;
    } else if (*raiz == NULL) { //Se um endereço não contém o endereço de um nó (não há filho à direita ou à esquerd
        return -1;
        //Em outras palavras, se um nó existe, tem algum ponteiro apontando para ele.
        //Então o que se verifica, é se há um endereço para um nó no endereço chamado "raiz"
    }
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir) 
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}

int totalNO_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) { //Se houve erro na alocação da árvore
        return 0;
    } else if (*raiz == NULL) {
        return 0;
    }
    int totalNosEsq = totalNO_ArvBin(&((*raiz)->esq));
    int totalNosDir = totalNO_ArvBin(&((*raiz)->dir));

    return (totalNosEsq + totalNosDir + 1);
}


//Percorrendo uma Árvore Binária
void preOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) //Testa se houve erro de alocação da árvore
        return;
    if (*raiz != NULL) { //Se de fato a raiz guarda o endereço de um nó
        printf("%d ", (*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
    // Não precisa de "else", pois ao não entrar no "if", subentende-se que *raiz é igual a NULL e o retorno da função é automático por não ter nada após a condicional
    return;
}

void emOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d ", (*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d ", (*raiz)->info);
    }
}

//Inserção em Árvore Binária de Busca
//Retorna 1 se a inserção deu certo, e 0 caso contrário
int insere_ArvBin(ArvBin *raiz, int valor) {
    if (raiz == NULL) {//Erro na alocação da árvore
        printf("primeiro if");
        return 0;
    }
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if (novo == NULL) {//Erro na alocação do nó
        printf("segundo if");
        return 0;
    }
    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    //Procurar onde inserir
    if (*raiz == NULL) {
        *raiz = novo;
    } else {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;

        while (atual != NULL) {
            ant = atual;
            if (valor == atual->info) { //Se o elemento já existe
                free(novo);
                printf("terceiro if");
                return 0;
            }
            if (valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }

        if (valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

//Remoção em Árvore Binária de Busca
//FUNÇÃO RESPONSÁVEL PELA BUSCA DO NÓ A SER REMOVIDO
int remove_ArvBin(ArvBin *raiz, int valor) {
    if (raiz == NULL) return 0;
    struct NO* atual = *raiz;
    struct NO* ant = NULL;

    while (atual != NULL) {
        //Achou o nó a ser removido. Tratar o lado da remoção
        if (valor == atual->info) {
            if (atual == *raiz) {
                *raiz = remove_atual(atual);
            } else {
                if (ant->esq == atual)
                    ant->esq = remove_atual(atual);
                else
                    ant->dir = remove_atual(atual);
            }
            return 1;
        }

        //Continua andando na árvore a procura do nó a ser removido
        ant = atual;
        if (valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    //Acho que é isso, no vídeo a está cortada essa parte
    return 0;
}

//FUNÇÃO RESPONSÁVEL POR TRATAR OS 3 TIPOS DE REMOÇÃO
struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    //Sem filho da esquerda.
    //Apontar para o filho da direita (trata nó folha e nó com 1 filho)
    if (atual->esq == NULL) {
        no2 = atual->dir;
        free(atual);
        return no2;
    }

    //Procura o filho mais a direita na sub-árvore da esquerda
    no1 = atual;
    no2 = atual->esq;
    while (no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }

    //Copia o filho mais a direita na sub-árvore esquerda para o lugar do nó removido
    if (no1 != atual) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;

    free(atual);
    return no2;
}

//Consulta em Árvore Binária de Busca
int consulta_ArvBin(ArvBin *raiz, int valor) {
    if (raiz == NULL) //Se houve erro na alocação da árvore
        return 0;

    struct NO *atual = *raiz;
    while (atual != NULL) {
        if (valor == atual->info){
            return 1;
        }
        if (valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}
