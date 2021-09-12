#include <stdlib.h>
#include <stdio.h>
#include "tp3.h"

int main(int argc, char *argv[]){
    // Variaveis do programa:
    char nome_arquivo[20];
    int i, resultado, mes_opcao, ano_opcao, idioma_opcao, num_opcao, con_opcao;
    int qtdias_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char eventos[5];
    char semana[7][15] = {"Sabado", "Domingo", "Segunda-feira", "Terca-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira"};
    char week[7][15] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    char mes[12][15] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    char month[12][15] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    Tabela T;
    Tabela O;
    
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);
    CriaVetor(&T);
    // Montagem do arquivo de eventos:
    AbreArquivo(&T, nome_arquivo, eventos);
    //ImprimeArquivo(&T);
    printf("Operacoes disponiveis:\n");
    printf("1)- Imprimir calendario como lista.\n");
    printf("2)- Imprimir calendario como arquivo pdf.\n");
    printf("3)- Consulta de eventos.\n");
    printf("Digite a sua opcao: ");
    scanf("%d", &num_opcao);
    printf("\n\n");
    // Operacao 1 escolhida: Calendario como lista.
    if(num_opcao == 1){
        printf("Digite o mes do Calendario[1 a 12]: ");
        scanf("%d", &mes_opcao);
        printf("Digite o ano do calendario[1900 a 2999]: ");
        scanf("%d", &ano_opcao);
        printf("Escolha o idioma[0 -> Pt | 1 -> In]: ");
        scanf("%d", &idioma_opcao);
        TrataDadosEntrada(idioma_opcao, ano_opcao, qtdias_mes);
        printf("\n\n");
        // Saida de Dados: Portugues
        if(idioma_opcao == 0){
            printf("%s %d\n", mes[mes_opcao - 1], ano_opcao);
            printf("Quantidade de dias: %d\n", qtdias_mes[mes_opcao - 1]);
            printf("\n");
            for(i = 1; i <= qtdias_mes[mes_opcao - 1]; i++){
                resultado = DiaSemana(i, mes_opcao, ano_opcao);
                printf("%d %s\n", i, semana[resultado]);
                ProcuraEvento(&T, i, mes_opcao, ano_opcao);
            }
        }
        // Saida de Dados: Ingles
        else{
            printf("%s %d\n", month[mes_opcao - 1], ano_opcao);
            printf("Number of days: %d\n", qtdias_mes[mes_opcao - 1]);
            printf("\n");
            for(i = 1; i <= qtdias_mes[mes_opcao - 1]; i++){
                resultado = DiaSemana(i, mes_opcao, ano_opcao);
                printf("%d %s\n", i, week[resultado]);
                ProcuraEvento(&T, i, mes_opcao, ano_opcao);
            }
        }
    }
    // Operacao 2 escolhida: Calendario como arquivo pdf:
    else if(num_opcao == 2){
        printf("Digite o mes do Calendario[1 a 12]: ");
        scanf("%d", &mes_opcao);
        printf("Digite o ano do calendario[1900 a 2999]: ");
        scanf("%d", &ano_opcao);
        printf("Escolha o idioma[0 -> Pt | 1 -> In]: ");
        scanf("%d", &idioma_opcao);
        TrataDadosEntrada(idioma_opcao, ano_opcao, qtdias_mes);
        printf("\n\n");
        // Saida de Dados: Portugues
        if(idioma_opcao == 0){
            printf("Nao foi possivel terminar essa parte do tp.\n");
        }
        // Saida de Dados: Ingles
        else{
            printf("Nao foi possivel terminar essa parte do tp.\n");
        }
    }
    // Operacao 3 escolhida: Consulta de Eventos:
    else if(num_opcao == 3){
        printf("Bem vindo a consulta de arquivos!\n");
        printf("Operacoes disponiveis:\n");
        printf("1)- Ordenar e imprimir arquivo.\n");
        printf("2)- Pesquisar arquivo.\n");
        printf("Digite a sua opcao: ");
        scanf("%d", &con_opcao);
        printf("\n");
        // Ordena e imprime arquivo:
        if(con_opcao == 1){
            printf("Voce escolheu ordenar e imprimir arquivo. Temos as seguintes operacoes: \n");
            printf("1)- Ordem de eventos(A, F, V, O).\n");
            printf("2)- Ordem cronologica.\n");
            printf("Digite sua opcao: ");
            scanf("%d", &con_opcao);
            // TERMINAR
            printf("\n");
            ImprimeOrdena(&T, &O, con_opcao);

        }
        // Pesquisa arquivo:
        else if(con_opcao == 2){
            printf("Voce escolheu pesquisar arquivo. Temos as seguintes operacoes: \n");
            printf("1)- Tipo de evento(A, F, V, O).\n");
            printf("2)- Data especifica.\n");
            printf("Digite sua opcao: ");
            scanf("%d", &con_opcao);
            PesquisaArquivo(&T, con_opcao);
        }
    }
    // Erro:
    else{
        printf("Opcao digitada nao disponivel.\n");
        exit(1);
    }
}