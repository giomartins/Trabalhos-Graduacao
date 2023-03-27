#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TP3.h"
  
//Inicia o vetor da tabela Hash
void Cria_Tabela_Hash(TipoHash *H){
    H->tabela_hash = malloc (4000 * sizeof(Palavra));
}

//Inicializa a lista encadeada
void Lista_Vazia(TipoHash *H){
    H->Primeiro = (Apontador) malloc (sizeof(Palavra));
    H->Ultimo = H->Primeiro;
    H->Primeiro->prox = NULL;
}

//Insere na linha correspondente da tabela hash:
void Insere_Tabela_Hash(TipoHash *H, char *palavra, int num_arq, int freq){
    H->Ultimo->prox = (Apontador) malloc (sizeof(Palavra));
    H->Ultimo = H->Ultimo->prox;
    strcpy(H->Ultimo->palavra, palavra);
    H->Ultimo->num_arquivo = num_arq;
    H->Ultimo->frequencia = freq;
}

//Converte a palavra para minuscula e calcula a posicao que a palavra ocupara na tabela Hash
int Calcula_Pos_Hash(char *palavra, int comprimento){
    int i = 0, somatorio = 0, resultado = 0;
    //Calculo
    for(i = 1; i <= comprimento; i++)
        somatorio += (i * palavra[i]);
    resultado = somatorio / 7;
    return resultado;
}

//Muda o caminho do arquivo a ser aberto:
void Altera_Caminho(char *arranjo, int numero, int comp_caminho){
    int resultado, resto, comp_aux;
    char aux[5];

    //Entre 0 a 9:
    if(numero >= 0 && numero < 10){
        aux[0] = numero + '0';
        aux[1] = '\0';
        comp_aux = strlen(aux);
        strcat(arranjo, aux);
    }
    // Entre 10 e 99:
    else if(numero >= 10 && numero < 100){
        resultado = numero / 10;
        resto = numero % 10;
        aux[0] = resultado + '0';
        aux[1] = resto + '0';
        aux[2] = '\0';
        strcat(arranjo, aux);
    }
    // Entre 100 e 150:
    else{
        resultado = numero / 100;
        resto = numero % 100;
        aux[0] = resultado + '0';
        resultado = resto / 10;
        aux[1] = resultado + '0';
        resto = resto % 10;
        aux[2] = resto + '0';
        aux[3] = '\0';
        strcat(arranjo, aux);
    }
}

//Remove caracteres indesejados da palavra:
int Trata_Palavra(char *palavra){
    int i;
    int comprimento = strlen(palavra);

    //Removo tudo o que nao for letra no inicio:
    while(  (palavra[0] < 65) || (palavra[0] > 90 && palavra[0] < 97) || (palavra[0] > 122) ){
        for(i = 0; i < comprimento; i++)
            palavra[i] = palavra[i + 1];
        comprimento--;
        if(comprimento == 0)
            break;
        palavra[comprimento] = '\0';
    }
    //Removo tudo o que nao for letra no fim:
    while(  (palavra[comprimento - 1] < 65) ||
    (palavra[comprimento - 1] > 90 && palavra[comprimento - 1] < 97) ||
    (palavra[comprimento - 1] > 122) ){
        palavra[comprimento - 1] = '\0';
        if(comprimento == 0)
            break;
        comprimento--;
    }
    return comprimento;
}

//Checa se a palavra esta presente no arquivo StopWord:
int is_StopWord(Dados *D, char *palavra){
    int i = 0, j = 0;

    if(D->comp_palavra1 <= 0)
        return 1;
    //174: numero de palavras no arquivo
    while(i < 174){
        if(strcasecmp(D->matriz_StopWord[i], palavra) == 0)
            return 1;
        i++;
    }
    return 0;
}

//Checa se a palavra que nao faz parte do arquivo StopWorld esta presente na Matriz:
void is_Saved(Dados *D, char *palavra, int comprimento){
    int i = 0;
    int resultado;

    //Converte a palavra para Minuscula:
    while(i < comprimento){
        palavra[i] = tolower(palavra[i]);
        i++;
    }
    //Comparo com todos os valores salvos na matriz:
    for(i = 0; i <= D->tam_matriz; i++){
        resultado = strcmp(palavra, D->matriz_Palavras[i]);
        // Palavra ja presente na matriz, nao verifico o resto.
        if(resultado == 0)
            break;
    }
    //Palavra nao esta presente na matriz:
    if(resultado != 0){
        strcpy(D->matriz_Palavras[D->tam_matriz], palavra);
        D->tam_matriz++;
    }
}

//Guarda as palavras referentes ao arquivo StopWord:
void Abre_StopWord(Dados *D, char *argv[2]){
    FILE *p_arq;
    int i = 0;

    p_arq = fopen(argv[2], "r+");
    //StopWord aberto:
    if(p_arq != NULL){
        while(fscanf(p_arq, "%s", D->matriz_StopWord[i]) != EOF)
            i++;
    }
    //StopWord nao encontrado:
    else{
        printf("O arquivo StorWord.txt nao foi encontrado.\n");
        exit(1);
    }
}

//Guarda todas as palavras que nao sao do StopWorld em uma matriz:
void Guarda_Palavra_Matriz(TipoHash *H, Dados *D){
    FILE *p_arq;
    int resultado;

    p_arq = fopen(D->caminho_arq1, "r+");
    if(p_arq != NULL){
        while(fscanf(p_arq, "%s", D->palavra1) != EOF){
            D->comp_palavra1 = Trata_Palavra(D->palavra1);
            resultado = is_StopWord(D, D->palavra1);
            //Se nao for StopWord, insiro na tabela Hash:
            if(resultado == 0){
                //Remove palavras Nulas:
                if(D->palavra1[0] != '\0'){
                    is_Saved(D, D->palavra1, D->comp_palavra1);
                }
            }
        }
    }
    else{
        printf("O arquivo presente no caminho %s nao foi encontrado\n", D->caminho_arq1);
        exit(1);
    }
}

//Verifica a frequencia de cada palavra em cada arquivo:
void Frequencia_Palavra(TipoHash *H, Dados *D, int x){
    FILE *p_arq;
    int i;
    int comp;

    //Pega o comprimento inicial do caminho e calcula a posicao com a funcao hash
    comp = strlen(D->caminho_arq2);
    D->valor_pos = Calcula_Pos_Hash(D->matriz_Palavras[x], comp);

    for(i = 1; i <= 150; i++){
        //Zera a contagem e ajusta o novo caminho:
        D->frequencia = 0;
        Altera_Caminho(D->caminho_arq2, i, comp);
        //Tentativa de abrir o arquivo:
        p_arq = fopen(D->caminho_arq2, "r");
        if(p_arq != NULL){
            while(fscanf(p_arq, "%s", D->palavra2) != EOF){
                D->comp_palavra2 =  Trata_Palavra(D->palavra2);
                //comparacao da palavra:
                if(strcasecmp(D->matriz_Palavras[x], D->palavra2) == 0)
                    D->frequencia++;
            }
            fclose(p_arq);
            //Foi encontrada uma palavra em um determinado arquivo:
            //Palavras com comprimento maior que 20 sao descartadas
            if(D->frequencia > 0 && D->comp_palavra2 < 20){
                //Fazer a insercao na lista encadeada:
                Insere_Tabela_Hash(H, D->matriz_Palavras[x], i, D->frequencia);
            }
        }
        else{
            printf("Algo deu errrado!\n");
            exit(1);
        }
        D->caminho_arq2[comp] = '\0';
    }
    //printf("\n");
}

//Funcao que procura a palavra contida no caminho de argv[1]:
void Procura_Palavra(PalavraArquivo *P, char *argv[]){
    FILE *p_arq1, *p_arq2;
    int i;
    int cnt = 0;

    P->comp_arqs = 0;
    strcpy(P->caminho, "corpus/");
    P->tam_caminho = strlen(P->caminho);

    //Pega palavra:
    p_arq1 = fopen(argv[1], "r+");
    fscanf(p_arq1, "%s", P->palavra1);
    P->comp_p1 = Trata_Palavra(P->palavra1);

    //Procura a palavra:
    for(i = 1; i <= 150; i++){
        P->freq = 0;
        Altera_Caminho(P->caminho, i, P->tam_caminho);
        p_arq2 = fopen(P->caminho, "r+");
        //Arquivo aberto:
        if(p_arq2 != NULL){
            while(fscanf(p_arq2, "%s", P->palavra2) != EOF){
                P->comp_p2 = Trata_Palavra(P->palavra2);
                if(strcasecmp(P->palavra1, P->palavra2) == 0){
                  P->freq++;
                }
            }
            if(P->freq > 0){
                P->mat_arqs[P->comp_arqs] = i;
                P->comp_arqs++;
            }
        }
        else{
            printf("Algo deu errado!\n");
            exit(1);
        }
        P->caminho[P->tam_caminho] = '\0';
    }
    printf("\n");
}

//Funcao que imprime a lista encadeada da posicao 'n' da Tabela Hash:
void Imprime_Tabela_Hash(TipoHash *H, int n){
    Apontador x;
    x = H->tabela_hash[n].prox->prox;
    char palavra_aux[20];

    while(x != NULL){
        strcpy(palavra_aux, x->palavra);
        printf("[%s] => ", x->palavra);
        while(strcasecmp(palavra_aux, x->palavra) == 0){
            printf("(%d, %d) ", x->num_arquivo, x->frequencia);
            x = x->prox;
            if(x == NULL)
                break;
        }

        printf("\n");
    }
}

//Funcao que monta o arquivo da lista invertida, atraves da tabela hash e listas encadeadas:
void Saida_Arquivo(TipoHash *H, Dados *D){
    FILE *p_arq;
    Apontador x;
    char palavra_aux[20];
    int i;

    p_arq = fopen("corpus/inverted_list.txt", "w+");
    for(i = 0; i < 4000; i++){
        x = H->tabela_hash[i].prox->prox;
        while(x != NULL){
            strcpy(palavra_aux, x->palavra);
            fprintf(p_arq, "[%s] => ", x->palavra);
            while(strcasecmp(palavra_aux, x->palavra) == 0){
                fprintf(p_arq, "(%d, %d) ", x->num_arquivo, x->frequencia);
                x = x->prox;
                if(x == NULL){
                    break;
                }
            }
            D->qt_colisao++;
            fprintf(p_arq, "\n");
        }
    }
    fclose(p_arq);
}

//Funcao principal do programa:
void Inicia_Programa(TipoHash *H, Dados *D, char *argv[]){
    int i, j;
    int tam_caminho_inicial;

    D->tam_matriz = 0;
    D->qt_colisao = 0;

    strcpy(D->caminho_arq1, "corpus/");
    strcpy(D->caminho_arq2, "corpus/");
    tam_caminho_inicial = strlen(D->caminho_arq1);

    //Cria o vetor com as listas encadeadas:
    Cria_Tabela_Hash(H);
    for(i = 0; i < 4000; i++){
        Lista_Vazia(H);
        H->tabela_hash[i].prox = H->Primeiro;
    }

    //Guarda as palavras do arquivo StopWord:
    Abre_StopWord(D, argv);

    // Leitura das Palavras que serao utilizadas no indice invertido:
    for(i = 1; i <= 150; i++){
        Altera_Caminho(D->caminho_arq1, i, tam_caminho_inicial);
        Guarda_Palavra_Matriz(H, D);
        D->caminho_arq1[tam_caminho_inicial] = '\0';
    }

    //Guarda as informacoes na Tabelaa Hash:
    for(i = 0; i < D->tam_matriz; i++){
        Frequencia_Palavra(H, D, i);
    }

    //Saida final do arquivo:
    Saida_Arquivo(H, D);

    // FUNCOES PARA TESTES -> PRESENTES NA DOCUMENTACAO:
    /*
    //Impressao das palavras do arquivo StopWord:
    printf("Palavras do Arquivo StopWorld\n");
    for(i = 0; i < 174; i++)
        printf("%s\n", D->matriz_StopWord[i]);
    //Impressao das palavras da Lista Invertida:
    printf("Palavras do Indice Invertido:\n");
    for(i = 0; i < D->tam_matriz; i++){
        printf("[%d]: %s\n", i, D->matriz_Palavras[i]);
    }
    Apontador aux;
    //Impressao das informacoes guardadas na tabela Hash:
    for(i = 0; i < 4000; i++){
        aux = H->tabela_hash[i].prox->prox;
        // So mando imprimir as linhas que contêm informacoes:
        if(aux != NULL)
            Imprime_Tabela_Hash(H, i);
    }
    */
}
