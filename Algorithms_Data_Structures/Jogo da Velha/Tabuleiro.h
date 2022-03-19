#ifndef TABULEIRO_H
#define TABULEIRO_H

    /* Criacao da struct responsavel por guardar as informacoes do Tabuleiro: */
    typedef struct {
        char **matriz;                  // Matriz principal utilizada para Jogo da Velha e Caca Niqueis.
        char tipo_jogo[10];             // Variavel referente ao valor passado em argv[0], para Ambos.
        char nome_arquivo[30];          // Variavel referente ao valor passado em argv[2], nao sendo este obrigatorio, em ambos os casos.
        int res_dig_ED;                 // Guarda o valor '1' quando todos os valores da diagonal 'esquerda-direita' sao iguais.
        int res_dig_DE;                 // Guarda o valor '1' quando todos os valores da diagonal 'direita-esquerda' sao iguais.
        
        // Variaveis exclusivas para Caca Niqueis:
        int tamanho;                    // Variavel referente ao valor passado em argv[1], para CacaNiqueis.
        int res_lin_meio;               // Guarda o valor '1' quando todos os valores da linha do meio da matriz sao iguais.
        
        // Variaveis exclusivas para Jogo da Velha:
        int opcao;                      // Variavel refererente ao valor pssado em argv[1], para Jogo da Velha.
        char op_j1;                     // Variavel responsavel por guardar a opcao do jogador 1('X'/'O').
        char op_j2;                     // Variavel responsavel por guardar a opcao do jogador 2 ou computador('X'/'O').
        int res_lin_1;                  // Guarda o valor '1' quando todos os valores da linha 1 sao iguais.
        int res_lin_2;                  // Guarda o valor '1' quando todos os valores da linha 2 sao iguais.
        int res_lin_3;                  // Guarda o valor '1' quando todos os valores da linha 3 sao iguais.
        int res_col_1;                  // Guarda o valor '1' quando todos os valores da coluna 1 sao iguais.
        int res_col_2;                  // Guarda o valor '1' quando todos os valores da coluna 2 sao iguais.
        int res_col_3;                  // Guarda o valor '1' quando todos os valores da coluna 3 sao iguais.
    }Tabuleiro;

    /* Definicao das funcoes padroes utilizadas no Trabalho Pratico: */
    void SetTamanho(Tabuleiro *T, int n);
    void SetElemento(Tabuleiro *T, int i, int j, char c);
    char GetElemento(Tabuleiro T, int i, int j);
    void MarcaTodos(Tabuleiro *T, char c);
    int TestaLinha(Tabuleiro T, int i, char c);
    int TestaColuna(Tabuleiro T, int j, char c);
    int TestaDiagonalED(Tabuleiro T, char c);
    int TestaDiagonalDE(Tabuleiro T, char c);
    int TestaDiferente(Tabuleiro T, int i);
    void Imprime(Tabuleiro T);
    
    /* Definicao das funcoes extras utilizadas no programa: */
    
    // Funcoes exclusivas para o Caca Niqueis:
    void CriaMatriz_CN(Tabuleiro *T);
    void TrataDados_CN(Tabuleiro *T, char *argv[]);
    void AbreArquivo_CN(Tabuleiro *T);
    void Rand_CN(Tabuleiro *T);
    void Partida_CN(Tabuleiro *T, char *argv[]);
    
    // Funcoes exclusivs para o Jogo da Velha:
    void CriaMatriz_V(Tabuleiro *T);
    void TestaMatriz_V(Tabuleiro *T, char c);
    void TrataDados_V(Tabuleiro *T, char *argv[]);
    void Jogada_J(Tabuleiro *T, int i, int j, char c);
    void Jogada_PC(Tabuleiro *T, char c);
    void Preenche_Matriz(Tabuleiro *T);
    void AbreArquivo_V(Tabuleiro *T);
    void Partida_V(Tabuleiro *T, char *argv[]);

#endif
