#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tp3.h"

/*
    ATENCAO!
    A execucao completa do trabalho, leva em torno de 5 minutos(pelo menos na maquina
    em que foi inicialmente testado), devido a execucao da funcao Inicia_Programa, 
    responsavel por montar o Indice Invertido.

    Atenciosamente,
    Giovanni Martins
*/


int main(int argc, char *argv[]){
    PalavraArquivo pal_arq;
    Dados dados;
    TipoHash hash;
    int i;
    
    clock_t t;
    t = clock();
        Procura_Palavra(&pal_arq, argv);
    t = clock() - t;
    double tempo_total = ((double)t)/CLOCKS_PER_SEC;

    printf("%s: %.1f second(s)\n", pal_arq.palavra1, tempo_total);
    for(i = 0; i < pal_arq.comp_arqs; i++)
        printf("%d ", pal_arq.mat_arqs[i]);
    printf("\n");

    Inicia_Programa(&hash, &dados, argv);
    printf("Numero de colisoes: %d\n", dados.qt_colisao);
}