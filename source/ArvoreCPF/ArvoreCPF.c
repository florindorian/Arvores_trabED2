#include <stdio.h>
#include <stdlib.h>
#include "ArvoreCPF.h"
#include "../Information/Information.h"

struct t_no_cpf {
    Info *info;
    struct t_no_cpf* esq;
    struct t_no_cpf* dir;
};

//      Função para criar uma Arvore Binária de CPF
//      Aloca ela dinamicamente e retorna um ponteiro para ela
ArvoreCPF *cria_ArvCPF(){
    ArvoreCPF* raiz = (ArvoreCPF*) malloc(sizeof(ArvoreCPF));
    if (raiz != NULL)
        *raiz = NULL;
    else {
        printf("Falha na alocacao da arvore!\n");
        exit(1); //Falha na alocação
    }
    return raiz;
}

//      Função para liberar a memória alocada de um Nó
//      Libera ele mesmo e passa para liberar os nós filhos
void libera_NO_cpf(No* no, Info** conjuntoInfos) {
    static int pos = 0;

    //      Caso base da recursão:
    if (no == NULL)
        return;
    //      Caminhamento pré-fixado
    //      para recolher as informações de cada nó e armazenar em um array de Info*
    conjuntoInfos[pos++] = no->info;
    libera_NO_cpf(no->esq, conjuntoInfos);
    libera_NO_cpf(no->dir, conjuntoInfos);

    //      Após fazer o caminhamento acima para encontrar um nó folha, libera o nó
    free(no);
    no = NULL;
}

//      Libera a memória dos nós alocados em uma árvore
Info** libera_ArvCPF(ArvoreCPF* raiz) {
    if (raiz == NULL)
        return NULL;

    //      Cria um array para armazenar todos os ponteiros Info* alocados
    //      para que sejam desalocados no código principal
    int n_nos = totalNO_ArvCPF(raiz);
    Info** conjuntoInfos = (Info**) malloc(sizeof(Info*) * n_nos);

    //     libera cada nó
    libera_NO_cpf(*raiz, conjuntoInfos);

    //      libera a raíz
    free(raiz);
    raiz = NULL;
    return conjuntoInfos;
}

//
//      Funções para dar informações básicas da árvore
//

//      Função para saber se a árvore está vazia
int estaVazia_ArvCPF(ArvoreCPF *raiz) {
    //      Se houve algum erro de alocação, por exemplo
    if (raiz == NULL) {
        return 1;
        //      Se a árvore de fato não possui nenhum nó
    } else if (*raiz == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//      Função para descobrir a altura de uma árvore
//      Antes checa se a árvore está com erro de alocação
//      Depois vê se a árvore tem pelo menos um único nó alocado
int altura_ArvCPF(ArvoreCPF *raiz) {
    //      Se houve erro na alocação da árvore
    if (raiz == NULL) {
        return 0;
        //      Se um endereço não contém o endereço de um nó (não há filho à direita ou à esquerd
    } else if (*raiz == NULL) {
        return -1;
    }

    //      Recursivamente procura pela folha mais distante
    //      Quando a função encontrar uma folha, a entrada será um Nó com valor NULL
    //      O retorno com entrada NULL é 0
    //      Com isso, a função começará a terminar a recursividade
    int alt_esq = altura_ArvCPF(&((*raiz)->esq));
    int alt_dir = altura_ArvCPF(&((*raiz)->dir));

    //      Vê em qual lado tá a maior subarovre, e a retorna + 1
    //          +1 -> para incrementar contando o nó atual
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}

//      Função para descobrir a quantidade de Nós na árvore
int totalNO_ArvCPF(ArvoreCPF *raiz) {
    //      Se houve erro na alocação da árvore
    if (raiz == NULL) {
        return 0;
    } else if (*raiz == NULL) {
        return 0;
    }

    //      Busca recursivamente por todos os nós
    //      Quando a entrada é um nó NULL, o retorno é 0
    int totalNosEsq = totalNO_ArvCPF(&((*raiz)->esq));
    int totalNosDir = totalNO_ArvCPF(&((*raiz)->dir));


    //      É o valor da quantidade de nós das subárvores esquerdas e direitas
    //      As folhas retornarão somente 1, pois terão o retorno 0 de Nós NULL
    //      Assim
    //          +1 -> para incrementar com o valor do nó atual
    //          Soma com o valor da quantidade de nós dos dois lados
    return (totalNosEsq + totalNosDir + 1);
}

//      Funçẽos para percorrer uma Árvore Binária

//      Em pré ordem
void preOrdem_ArvCPF(ArvoreCPF *raiz) {
        //      Testa se houve erro de alocação da árvore
    if (raiz == NULL)
        return;
        //      Se de fato a raiz guarda o endereço de um nó
    if (*raiz != NULL) {
        printf("%d ", (*raiz)->info->CPF);
        preOrdem_ArvCPF(&((*raiz)->esq));
        preOrdem_ArvCPF(&((*raiz)->dir));
    }
    //      Não precisa de "else",
    //  pois ao não entrar no "if", subentende-se que *raiz é igual a NULL
    //  e o retorno da função é automático por não ter nada após a condicional
}

//      Em ordem
void emOrdem_ArvCPF(ArvoreCPF *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        emOrdem_ArvCPF(&((*raiz)->esq));
        printf("%d ", (*raiz)->info->CPF);
        emOrdem_ArvCPF(&((*raiz)->dir));
    }
    //      Não precisa de "else",
    //  pois ao não entrar no "if", subentende-se que *raiz é igual a NULL
    //  e o retorno da função é automático por não ter nada após a condicional
}

//      Em pré-ordem
void posOrdem_ArvCPF(ArvoreCPF *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        posOrdem_ArvCPF(&((*raiz)->esq));
        posOrdem_ArvCPF(&((*raiz)->dir));
        printf("%d ", (*raiz)->info->CPF);
    }
    //      Não precisa de "else",
    //  pois ao não entrar no "if", subentende-se que *raiz é igual a NULL
    //  e o retorno da função é automático por não ter nada após a condicional
}

//      Função para realizar a inserção de um dado na árvore
int insere_ArvCPF(ArvoreCPF *raiz, Info* info) {

    //      Checagem de ero de alocação
    if (raiz == NULL) {
        return 0;
    }

    //      Alocação do novo nó a ser armazenado
    No* novo;
    novo = (No*) malloc(sizeof(No));
    //      Checagem de ero de alocação do No "novo"
    if (novo == NULL) {
        return 0;
    }

    //      Armazenamento de suas informações básicas
    //      Nós folhas sendo diretamente NULL para caso sejam folhas,
    //          caso contrário terão os devidos filhos.
    novo->info = info;
    novo->esq = NULL;
    novo->dir = NULL;

    //Procurar onde inserir

    //      Caso seja a raiz
    if (*raiz == NULL) {
        *raiz = novo;
        //      Caso não seja a raiz, procura por onde é a posição
    } else {
        //      Valores temporarios para auxiliar na busca da posição
        //      "atual" é o Nó da iteração atual
        //      "ant" é o Nó de uma iteração anterior
        No* atual = *raiz;
        No* ant = NULL;

        while (atual != NULL) {
            ant = atual;
            if (info->CPF == atual->info->CPF) {
                //      Se o elemento já existe
                //      Erro na inserção
                free(novo);
                return 0;
            }
            if (info->CPF > atual->info->CPF)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        //      Encontrou uma folha
        //      A partir daqui começa a trabalhar com o nó anterior
        //      Checa se a informação a ser inserida vem antes ou depois da folha
        if (info->CPF > ant->info->CPF)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    //      Inserção com sucesso
    return 1;
}

//      Função para remover um Nó na árvore, aqui ela faz a busca do nó
Info* remove_ArvCPF(ArvoreCPF *raiz, int valor) {
    //      Declarações e checagens iniciais
    Info* info = NULL;
    if (raiz == NULL)
        return NULL;
    No* atual = *raiz;
    No* ant = NULL;

    while (atual != NULL) {
        //      Achou o nó a ser removido. Tratar o lado da remoção
        if (valor == atual->info->CPF) {
            info = atual->info;
            if (atual == *raiz) {
                *raiz = remove_atual_CPF(atual);
            } else {
                if (ant->esq == atual)
                    ant->esq = remove_atual_CPF(atual);
                else
                    ant->dir = remove_atual_CPF(atual);
            }
            return info;
        }

        //      Continua andando na árvore a procura do nó a ser removido
        ant = atual;
        if (valor > atual->info->CPF)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    //      Significa que o nó a ser removido não foi encontrado
    return NULL;
}

//      Realiza a remoção do Nó
No* remove_atual_CPF(No* atual) {
    No *no1, *no2;
    //      Sem filho da esquerda.
    //      Apontar para o filho da direita (trata nó folha e nó com 1 filho)
    if (atual->esq == NULL) {
        no2 = atual->dir;
        free(atual);
        return no2;
    }

    //      Procura o filho mais a direita na sub-árvore da esquerda
    no1 = atual;
    no2 = atual->esq;
    while (no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }

    //      Copia o filho mais a direita na sub-árvore esquerda para o lugar do nó removido
    if (no1 != atual) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;

    free(atual);
    return no2;
}

//      Consulta em Árvore Binária de Busca
Info* consulta_ArvCPF(ArvoreCPF *raiz, int valor) {
    //      Se houve erro na alocação da árvore
    if (raiz == NULL)
        return NULL;

    No *atual = *raiz;
    while (atual != NULL) {
        if (valor == atual->info->CPF){
            //      Retorna a struct procurada com todas as informações, caso exista na árvore
            return atual->info;
        }
        if (valor > atual->info->CPF)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    //      Caso a informação procurada não exista na árvore
    return NULL;
}
