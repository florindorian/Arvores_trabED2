#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArvoreNome.h"

struct t_no_nome{
    Info *info;
    struct t_no_nome* esq;
    struct t_no_nome* dir;
};

/*
 *      Funções necessárias para realizar ações em pedaços do código
 * */

//      Função criada para descobrir o tamanho de uma string
int tamanhoDoNome(char *nomeDeEntrada){
    int i = 0;
    while(nomeDeEntrada[i] != '\0') i++;
    return i;
}

//      Função para converter os caracteres alfabéticos em caixa alta
//  de uma String para suas respectivas versões em caixa baixa
char *nomeEmCaixaBaixa(char *nome){
    //      Para descobrir o tamanho da string do nome
    int tamanho = tamanhoDoNome(nome);

    //      Alocado dinamicamente ele para que não seja necessário alterar o nome diretamente
    //      O tamanho total deve ser igual à quantidade de caracteres da string mais 1 para o '\0'
    char *tNome=(char*) malloc( sizeof(char) * (tamanho + 1));

    //      Converte os caracteres para suas versões em caixa baixa
    for(int i = 0; i < tamanho ; i++ )
        tNome[i] = (char) tolower( nome[i] );

    //      Adiciona o '\0' no final da string
    tNome[tamanho] = '\0';

    return tNome;
}

//      Função para comparar a ordem alfabética de duas strings
int compararNomes(char *nomeA, char *nomeB){
    //      Pega os nomes de entrada
    //      e os converte para suas respectivas versões em caixa baixa
    char *tNomeA=nomeEmCaixaBaixa(nomeA);
    char *tNomeB=nomeEmCaixaBaixa(nomeB);

    //      Os compara usando strcmp
    int resultado=strcmp(tNomeA, tNomeB);

    //      Libera o espaço usado para alocar dinamicamente as strings
    free(tNomeA);
    free(tNomeB);

    /*
     *      checa se o resultado é igual a 0 (nomes iguais)
     *      se for diferente, esse caso ocorre:
     *          resultado / |resultado| -> resultado dividido pelo módulo do resultado
     *          para que o resultado seja 1 ou -1
     *          -1 = Vem antes na ordem alfabéitca
     *           1 = Vem depois na ordem alfabéitca
     * */
    resultado = (resultado == 0) ? 0 : (resultado/abs(resultado)) ;
    return resultado;
}


//      Função para criar uma Arvore Binária de nomes
//      Aloca ela dinamicamente e retorna um ponteiro para ela
ArvoreNome *cria_ArvNome(){
    ArvoreNome* raiz = (ArvoreNome*) malloc(sizeof(ArvoreNome));
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
void libera_NO_nome(NoNome* no, Info** conjuntoInfos) {
    static int pos = 0;

    //      Caso base da recursão:
    if (no == NULL)
        return;

    //      Caminhamento pré-fixado
    //      para recolher as informações de cada nó e armazenar em um array de Info*
    conjuntoInfos[pos++] = no->info;
    libera_NO_nome(no->esq, conjuntoInfos);
    libera_NO_nome(no->dir, conjuntoInfos);

    //      Após fazer o caminhamento acima para encontrar um nó folha, libera o nó
    free(no);
    no = NULL;
}

//      Libera a memória dos nós alocados em uma árvore
Info** libera_ArvNome(ArvoreNome* raiz) {
    if (raiz == NULL)
        return NULL;

    //      Cria um array para armazenar todos os ponteiros Info* alocados
    //      para que sejam desalocados no código principal
    int n_nos = totalNO_ArvNome(raiz);
    Info** conjuntoInfos = (Info**) malloc(sizeof(Info*) * n_nos);

    //      Libera cada nó
    libera_NO_nome(*raiz, conjuntoInfos);

    //      libera a raíz
    free(raiz);
    raiz = NULL;

    return conjuntoInfos;
}


//
//      Funções para dar informações básicas da árvore
//

//      Função para saber se a árvore está vazia
int estaVazia_ArvNome(ArvoreNome *raiz) {
    //      Checar se houve algum erro na alocação da árvore
    if (raiz == NULL) {
        return 1;

    //      Checar se a árvore de fato não possui nenhum nó
    } else if (*raiz == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//      Função para descobrir a altura de uma árvore
//      Antes checa se a árvore está com erro de alocação
//      Depois vê se a árvore tem pelo menos um único nó alocado
int altura_ArvNome(ArvoreNome *raiz) {
    //      Caso de erro de alocação na entrada
    if (raiz == NULL) {
        return 0;
        //      Caso não haja nenhum nó na árvore
    } else if (*raiz == NULL) {
        return -1;
    }

    //      Recursivamente procura pela folha mais distante
    //      Quando a função encontrar uma folha, a entrada será um Nó com valor NULL
    //      O retorno com entrada NULL é 0
    //      Com isso, a função começará a terminar a recursividade
    int alt_esq = altura_ArvNome(&((*raiz)->esq));
    int alt_dir = altura_ArvNome(&((*raiz)->dir));

    //      Vê em qual lado tá a maior subarovre, e a retorna + 1
    //          +1 -> para incrementar contando o nó atual
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}


//      Função para checar a quantitade de nós em uma árvore
int totalNO_ArvNome(ArvoreNome *raiz) {
    //      Se houve erro na alocação da árvore ou não haver nenhum nó na mesma
    if (raiz == NULL) {
        return 0;
    } else if (*raiz == NULL) {
        return 0;
    }

    //      Busca recursivamente por todos os nós
    //      Quando a entrada é um nó NULL, o retorno é 0
    int totalNosEsq = totalNO_ArvNome(&((*raiz)->esq));
    int totalNosDir = totalNO_ArvNome(&((*raiz)->dir));

    //      É o valor da quantidade de nós das subárvores esquerdas e direitas
    //      As folhas retornarão somente 1, pois terão o retorno 0 de Nós NULL
    //      Assim
    //          +1 -> para incrementar com o valor do nó atual
    //          Soma com o valor da quantidade de nós dos dois lados
    return (totalNosEsq + totalNosDir + 1);
}


//      Funçẽos para percorrer uma Árvore Binária

//      Em pré ordem
void preOrdem_ArvNome(ArvoreNome *raiz) {
    //      Testa se houve erro de alocação da árvore
    if (raiz == NULL)
        return;
    //      Se de fato a raiz guarda o endereço de um nó
    if (*raiz != NULL) {
        //      Imprime o valor da string do nome, e passa recursivamente para os próximos
        printf("%s ", (*raiz)->info->Nome);
        preOrdem_ArvNome(&((*raiz)->esq));
        preOrdem_ArvNome(&((*raiz)->dir));
    }
    //      Não precisa de "else",
    //  pois ao não entrar no "if", subentende-se que *raiz é igual a NULL
    //  e o retorno da função é automático por não ter nada após a condicional

}

void emOrdem_ArvNome(ArvoreNome *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        emOrdem_ArvNome(&((*raiz)->esq));
        printf("%s ", (*raiz)->info->Nome);
        emOrdem_ArvNome(&((*raiz)->dir));
    }
    //      Não precisa de "else",
    //  pois ao não entrar no "if", subentende-se que *raiz é igual a NULL
    //  e o retorno da função é automático por não ter nada após a condicional
}

void posOrdem_ArvNome(ArvoreNome *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        posOrdem_ArvNome(&((*raiz)->esq));
        posOrdem_ArvNome(&((*raiz)->dir));
        printf("%s ", (*raiz)->info->Nome);
    }
    //      Não precisa de "else",
    //  pois ao não entrar no "if", subentende-se que *raiz é igual a NULL
    //  e o retorno da função é automático por não ter nada após a condicional
}

//      Função para realizar a inserção de um dado na árvore
int insere_ArvNome(ArvoreNome *raiz, Info* Info) {

    //      Checagem de ero de alocação
    if (raiz == NULL) {
        return 0;
    }

    //      Alocação do novo nó a ser armazenado
    NoNome* novo;
    novo = (NoNome*) malloc(sizeof(NoNome));
    //      Checagem de ero de alocação do No "novo"
    if (novo == NULL) {
        return 0;
    }

    //      Armazenamento de suas informações básicas
    //      Nós folhas sendo diretamente NULL para caso sejam folhas,
    //          caso contrário terão os devidos filhos.
    novo->info = Info;
    novo->esq = NULL;
    novo->dir = NULL;

    //      Variavel para salvar o resultado da comparação das strings de nomes
    int comp;


    //      Procurar onde inserir

    //      Caso seja a raiz
    if (*raiz == NULL) {
        *raiz = novo;
    //      Caso não seja a raiz, procura por onde é a posição
    } else {
        //      Valores temporarios para auxiliar na busca da posição
        //      "atual" é o Nó da iteração atual
        //      "ant" é o Nó de uma iteração anterior

        NoNome* atual = *raiz;
        NoNome* ant = NULL;

        while (atual != NULL) {
            /*
             * -1 se o nome vem antes em ordem alfabética
             *  0 se forem iguais
             *  1 se vier depois em ordem alfabética
             * */
            comp = compararNomes(Info->Nome, atual->info->Nome);
            ant = atual;
            //      Se os nomes forem iguais, logo ele já existe
            if (comp == 0) {
                //      Erro na inserção
                free(novo);
                return 0;
            }
            //      Maiores valores a direita
            //      Em string, se vem depois é "Maior", logo vai a direita
            if (comp>0)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        //      Encontrou uma folha
        //      A partir daqui começa a trabalhar com o nó anterior
        //      Checa se a informação a ser inserida vem antes ou depois da folha
        comp = compararNomes(Info->Nome, ant->info->Nome);
        if (comp>0)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    //      Inserção com sucesso
    return 1;
}

//      Função para remover um Nó na árvore, aqui ela faz a busca do nó
Info* remove_ArvNome(ArvoreNome *raiz, char *nome) {

    //      Declarações e checagens iniciais
    Info* info = NULL;
    if (raiz == NULL)
        return NULL;
    NoNome* atual = *raiz;
    NoNome* ant = NULL;
    int comp;

    while (atual != NULL) {
        comp = compararNomes(nome, atual->info->Nome);
        //      Achou o nó a ser removido. Tratar o lado da remoção
        if (comp==0) {
            info = atual->info;
            if (atual == *raiz) {
                *raiz = remove_atual_nome(atual);
            } else {
                if (ant->esq == atual)
                    ant->esq = remove_atual_nome(atual);
                else
                    ant->dir = remove_atual_nome(atual);
            }
            return info;
        }

        //      Continua andando na árvore a procura do nó a ser removido
        ant = atual;
        if (comp>0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    //      Significa que o nó a ser removido não foi encontrado
    return NULL;
}

//      Realiza a remoção do Nó
NoNome* remove_atual_nome(NoNome* atual) {
    NoNome *no1, *no2;
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
Info* consulta_ArvNome(ArvoreNome *raiz, char *nome) {
    if (raiz == NULL)
        //      Se houve erro na alocação da árvore
        return NULL;
    NoNome *atual = *raiz;

    int cond;
    while (atual != NULL) {
        cond = compararNomes(nome, atual->info->Nome);
        //      Retorna a struct procurada com todas as Informações, caso exista na árvore
        if (cond == 0){
            return atual->info;
        }
        if (cond>0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL; //     Caso a Informação procurada não exista na árvore
}
