#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tabuleiro.h"

int main(int argc, char *argv[]){
    // Chamada do tipo abstrato de dados:
    Tabuleiro tabl_v;
    // Chamada da funcao principal:
    Partida_V(&tabl_v, argv); 
}
