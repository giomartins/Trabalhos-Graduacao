#ifndef TP3_H
#define TP3_H

// Estrutura de Dados:
typedef struct Tabela_str *Apontador;

typedef struct Tabela_str{
    char evento;
    int dia;
    int mes;
    int ano;
    char descr_evento[40];
    Apontador prox;
}Evento;

typedef struct{
    Evento *dias;   // Os eventos serao separados pelos dias referentes.
    Apontador Primeiro, Ultimo;
}Tabela;


// Funcoes do Tp2:
void CriaVetor(Tabela *T);
void TrataDadosEntrada(int op_idioma, int op_ano, int *qtdias_mes);
int DiaSemana(int dia, int mes, int ano);
void InsereTabela(Tabela *T, char evento, int dia, int mes, int ano, char *descr_evento);
void GuardaEventos(char *eventos);
int TestaEvento(char *eventos, char evento);
void AbreArquivo(Tabela *T, char *nome_arq, char *eventos);
void ImprimeArquivo(Tabela *T);
void ProcuraEvento(Tabela *T, int dia, int mes, int ano);
// Funcoes do Tp3:
void Atribui(Apontador a, Apontador b);
void Ordena(Tabela *O, int opcao);
void ImprimeOrdena(Tabela *T, Tabela *O, int opcao);
void PesquisaArquivo(Tabela *T, int opcao);
#endif