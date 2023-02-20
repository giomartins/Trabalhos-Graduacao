#ifndef TP3_H
#define TP3_H

typedef struct {
    char matriz_StopWord[174][15];      //174 palavras presentes no arquivo StopWord.txt
    char matriz_Palavras[26000][100];   //Matriz que guarda todas as palavras que nao sao do StopWorld:
    int tam_matriz; 
    int valor_pos;
    int frequencia;
    int qt_colisao;

    char palavra1[100];
    int comp_palavra1;
    char palavra2[100];
    int comp_palavra2;

    char caminho_arq1[20];
    char caminho_arq2[20];
}Dados;

typedef struct{
    int mat_arqs[150];
    int comp_arqs;
    char palavra1[100];
    char palavra2[100];
    char caminho[30];
    int comp_p1;
    int comp_p2;
    int tam_caminho;
    int freq;
}PalavraArquivo;

// Implementacao do conjunto de listas encadeadas que irao conter a tabela Hash:
typedef struct Hash_str *Apontador;

typedef struct Hash_str{
    char palavra[20];
    int num_arquivo;
    int frequencia;
    Apontador prox;
}Palavra;

typedef struct{
    Palavra *tabela_hash;
    Apontador Primeiro, Ultimo;
}TipoHash;



// Funcoes utilizadas no programa
void Cria_Tabela_Hash(TipoHash *H);
void Lista_Vazia(TipoHash *H);
void Insere_Tabela_Hash(TipoHash *H, char *palavra, int num_arq, int freq);
int Calcula_Pos_Hash(char *palavra, int comprimento);
void Altera_Caminho(char *arranjo, int numero, int comp_caminho);
int Trata_Palavra(char *palavra);
int is_StopWord(Dados *D, char *palavra);
void is_Saved(Dados *D, char *palavra, int comprimento);
void Abre_StopWord(Dados *D, char *argv[]);
void Guarda_Palavra_Matriz(TipoHash *H, Dados *D);
void Frequencia_Palavra(TipoHash *H, Dados *D, int x);
void Procura_Palavra(PalavraArquivo *P, char *argv[]);
void Imprime_Tabela_Hash(TipoHash *H, int n);
void Saida_Arquivo(TipoHash *H, Dados *D);
void Inicia_Programa(TipoHash *H, Dados *D, char *argv[]);
#endif