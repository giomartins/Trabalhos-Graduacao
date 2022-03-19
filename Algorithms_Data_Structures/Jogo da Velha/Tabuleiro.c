#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tabuleiro.h"

/* Declaracao das funcoes padroes utilizadas no Trabalho Pratico: */

// Define o tamanho do tabuleiro que vai ser utilizado:
void SetTamanho(Tabuleiro *T, int n){
    // Verifica se o valor digitado e compativel com a criacao da matriz:
    if(n < 1 || n > 10){
        exit(1);
    }
    // O tamanho digitado e compativel, logo, pode ser guardado o valor na variavel:
    else{
        T->tamanho = n;
    }
}

// Coloca um elemento 'c' em uma posicao (i, j) do tabuleiro:
void SetElemento(Tabuleiro *T, int i, int j, char c){
    // Posicao incompativel para insercao:
    if((i < 0 || i >= T->tamanho) || (j < 0 || j >= T->tamanho)){
        printf("Coordenada nao disponivel para insercao na matriz.\n");
        exit(1);
    }
    // Posicao ok para insercao:
    else{
        T->matriz[i][j] = c;
    }
}

// Recupera o elemento de uma posicao (i, j) do tabuleiro:
char GetElemento(Tabuleiro T, int i, int j){
    char caractere;
    caractere = T.matriz[i][j];
    return caractere;
}

// Coloca um mesmo elemento 'c' em todas as posicoes do tabuleiro:
void MarcaTodos(Tabuleiro *T, char c){
    int x, y;
    // Jogo da Velha:
    if(T->tamanho == 0){
        for(x = 0; x < 3; x++)
            for(y = 0; y < 3; y++)
                T->matriz[x][y] = c;
    }
    // Caca Niqueis:
    else{
        for(x = 0; x < T->tamanho; x++)
            for(y = 0; y < T->tamanho; y++)
                T->matriz[x][y] = c;
    }
}

// Testa se uma linha 'i' do tabuleiro possui todos os elementos iguais a 'c', retornando true(1) ou false(0):
int TestaLinha(Tabuleiro T, int i, char c){
    int y;
    int cont_igual = 0;
    // Jogo da Velha:
    if(T.tamanho == 0){
        // Loop de comparacoes:
        for(y = 0; y < 3; y++){
            if(T.matriz[i][y] == c)
                cont_igual++;
        }
        // Resultado final:
        if(cont_igual == 3)
            return 1;
        else
            return 0;
    }
    // Caca Niqueis:
    else{
        // Loop de comparacoes:
        for(y = 0; y < T.tamanho; y++){
            if(T.matriz[i][y] == c)
                cont_igual++;
        }
        // Resultado final:
        if(cont_igual == T.tamanho)
            return 1;
        else
            return 0;
    }
}

// Testa se uma coluna 'j' do tabuleiro possui todos os elementos iguais a 'c', retornando true(1) ou false(0):
int TestaColuna(Tabuleiro T, int j, char c){
    int x;
    int cont_igual = 0;
    // Jogo da Velha:
    if(T.tamanho == 0){
        // Loop de comparacoes:
        for(x = 0; x < 3; x++){
            if(T.matriz[x][j] == c)
                cont_igual++;
        }
        // Resultado final:
        if(cont_igual == 3)
            return 1;
        else
            return 0;
    }
    // Caca Niqueis:
    else{
        // Loop de comparacoes:
        for(x = 0; x < T.tamanho; x++){
            if(T.matriz[x][j] == c)
                cont_igual++;
        }
        // Resultado final:
        if(cont_igual == T.tamanho)
            return 1;
        else
            return 0;
    }
}

// Testa se a diagonal esq-dir possui todos os elementos iguais a 'c', retornando true(1) ou false(0):
int TestaDiagonalED(Tabuleiro T, char c){
    int x, y;
    int cont_igual = 0;
    int ED_x = 0, ED_y = 0;
    // ED_x e ED_y recebem inicialmente o mesmo valor inicial(0).
    // Os valores da matriz na diagonal ED vao ser aqueles em que ED_x == ED_y.
    // Tanto ED_x quanto ED_y serao igualmente incrementados ate o fim da leitura da matriz.
    // Jogo da Velha:
    if(T.tamanho == 0){
        for(x = 0; x < 3; x++){
            for(y = 0; y < 3; y++){
                if((x == ED_x) && (y == ED_y)){
                    if(T.matriz[ED_x][ED_y] == c)
                        cont_igual++;
                }
            }
            ED_x++;
            ED_y++;
        }
        // Resultado final:
        if(cont_igual == 3)
            return 1;
        else
            return 0;
    }
    // Caca Niqueis:
    else{
        for(x = 0; x < T.tamanho; x++){
            for(y = 0; y < T.tamanho; y++){
                if((x == ED_x) && (y == ED_y)){
                    if(T.matriz[ED_x][ED_y] == c)
                        cont_igual++;
                }
            }
            ED_x++;
            ED_y++;
        }
        // Resultado final:
        if(cont_igual == T.tamanho)
            return 1;
        else
            return 0;
    }
}

// Testa se a diagonal dir-esq possui todos os elementos iguais a 'c', retornando true(1) ou false(0):
int TestaDiagonalDE(Tabuleiro T, char c){
    int x, y;
    int cont_igual = 0;
    int DE_x, DE_y;
    // DE_x e DE_y recebem inicialmente o valor minimo(0) e maximo respectivamente(T.tamanho - 1).
    // DE_x e incrementado ate o valor maximo(T.tamanho - 1) e DE_y e decrementado ate o valor minimo(0), dentro dos loops.
    // Jogo da Velha:
    if(T.tamanho == 0){
        DE_x = 0;
        DE_y = 2;
        for(x = 0; x < 3; x++){
            for(y = 0; y < 3; y++){
                if((x == DE_x) && (y == DE_y)){
                    if(T.matriz[DE_x][DE_y] == c)
                        cont_igual ++;
                }
            }
            DE_x++;
            DE_y--;
        }
        // Resultado final:
        if(cont_igual == 3)
            return 1;
        else
            return 0;
    }
    // Caca Niqueis:
    else {
        DE_x = 0;
        DE_y = T.tamanho - 1;
        for(x = 0; x < T.tamanho; x++){
            for(y = 0; y < T.tamanho; y++){
                if((x == DE_x) && (y == DE_y)){
                    if(T.matriz[DE_x][DE_y] == c)
                        cont_igual ++;
                }
            }
            DE_x++;
            DE_y--;
        }
        // Resultado final:
        if(cont_igual == T.tamanho)
            return 1;
        else
            return 0;
    }
}

// Testa se uma linha 'i' do tabuleiro possui todos os elementos diferentes, retornando true(1) ou false(0):
int TestaDiferente(Tabuleiro T, int i){
    int y, j;
    int cont_igual = 0;
    char item_comp = T.matriz[i][0];
    // Jogo da Velha:
    if(T.tamanho == 0){
        for(y = 1; y < 3; y++){
            //Caso y tenha chegado na ultima posicao, nao havera nenhum outro valor a mais ser comparado.
            if(y == 2)
                break;
            // Compara com todos os valores posteriores ao valor da posicao y:
            for(j = y; j < 3; j++){
                if(item_comp == T.matriz[i][j])
                    cont_igual++;
            }
            item_comp = T.matriz[i][y];
        }
    }
    // Caca Niqueis:
    else{
        for(y = 1; y < T.tamanho; y++){
            //Caso y tenha chegado na ultima posicao, nao havera nenhum outro valor a mais ser comparado.
            if(y == T.tamanho - 1)
                break;
            // Compara com todos os valores posteriores ao valor da posicao y:
            for(j = y; j < T.tamanho; j++){
                if(item_comp == T.matriz[i][j])
                    cont_igual++;
            }
            item_comp = T.matriz[i][y];
        }
    }
    //Se nao houve nenhuma igualdade de valores(cont_igual == 0), todos os valores sao diferentes.
    if(cont_igual == 0)
        return 1;
    else
        return 0;
}

// Imprime tabuleiro:
void Imprime(Tabuleiro T){
    int x, y;
    printf("\n");   
    // Jogo da Velha:   
    if(T.tamanho == 0){
        for(x = 0; x < 3; x++){
            for(y = 0; y < 3; y++){
                printf("%c ", T.matriz[x][y]);
            }
            printf("\n");
        }    
    }
    // Caca Niqueis:
    else{
        for(x = 0; x < T.tamanho; x++){
            for(y = 0; y < T.tamanho; y++){
                printf("%c ", T.matriz[x][y]);
            }
            printf("\n");
        }
    }
}
/********************************************************************************************************************/
/* Declaracao das funcoes extras utilizadas no programa: */
/* Funcoes exclusivas para o Caca Niqueis: */

// Cria uma matriz para a partida de Caca Niqueis de maneira dinamica:
void CriaMatriz_CN(Tabuleiro *T){
    int i;
    // Verifica se o 'T->tamanho' digitado e compativel(impar):
    if(T->tamanho % 2 == 0){
        printf("Atencao, o tamanho precisa ser impar.");
        exit(1);
    }
    // Tamanho ok:
    else{
        T->matriz = (char **)malloc(T->tamanho * sizeof(char *));
        for(i = 0; i < T->tamanho; i++)
            T->matriz[i] = (char *)malloc(T->tamanho * sizeof(char));
    }
}

// Guarda os dados presentes nos 'argvs' para Caca Niqueis:
void TrataDados_CN(Tabuleiro *T, char *argv[]){
    // Obs: o argv[1] referente ao tamanho ja foi tratada na funcao 'SetTamanho':
    // Nome do arquivo a ser lido:
    if(argv[2] != NULL){
        strcpy(T->nome_arquivo, argv[2]);
    }
    // Tamanho  a ser lido:
    if(T->tamanho % 2 == 0){
        printf("Tamanho digitado incompativel.\n");
        exit(1);
    }
}

// Realiza a abertura e leitura de arquivos para Caca Niqueis, quando disponiveis:
void AbreArquivo_CN(Tabuleiro *T){
    FILE *p_arq;
    int i, j;
    // Tentativa de abertura de arquivo:
    p_arq = fopen(T->nome_arquivo, "r+");
    // Leitura de arquivo, se estiver disponivel:
    if(p_arq != NULL){
        for(i = 0; i < T->tamanho; i++){
            for(j = 0; j < T->tamanho; j++){
                fscanf(p_arq, "%c", &T->matriz[i][j]);
                //Adaptacao para a leitura dos arquivos texte passados para Caca Niqueis:
                if(j < T->tamanho)
                    fscanf(p_arq, " ");
            }
        }
        fclose(p_arq);
    }
    // Nao foi encontrado o arquivo especificado:
    else{
        printf("Atencao usuario, nao foi encontrado o arquivo correspondente.\n");
        exit(1);
    }
}

// Realiza o preenchimento aleatorio da matriz de Caca Niqueis, dentro dos caracteres desejados:
void Rand_CN(Tabuleiro *T){
    int i, j;
    char elementos_cn[] = {35, 64, 37, 63, 42}; //ASCII em decimais:
    // Preenchimento de valores aleatorios:
    for(i = 0; i < T->tamanho; i++){
        for(j = 0; j < T->tamanho; j++){
            T->matriz[i][j] = elementos_cn[rand() % strlen(elementos_cn)];        
        }
    }
}

// Realiza a partida de Caca-Niqueis, bem como o uso de todas as funcoes principais:
void Partida_CN(Tabuleiro *T, char *argv[]){
    // Chamada das variaveis que irao calcular os resultados da matriz:
    T->res_lin_meio = 0;
    T->res_dig_ED = 0;
    T->res_dig_DE = 0;
    // Chamada das funcoes iniciais para a inicializacao da matriz:
    SetTamanho(T, atoi(argv[1]));
    TrataDados_CN(T, argv);
    CriaMatriz_CN(T);
    // Existe argv para a leitura(o argv correspondente nao esta vazio):
    if(argv[2] != NULL){
        AbreArquivo_CN(T);
        // Teste das diagonais e linha do meio caso tenha dado bingo:
        T->res_lin_meio = TestaLinha(*T, (T->tamanho - 1) / 2, T->matriz[(T->tamanho - 1) / 2][0]);
        T->res_dig_ED = TestaDiagonalED(*T, T->matriz[0][0]);
        T->res_dig_DE = TestaDiagonalDE(*T, T->matriz[0][T->tamanho - 1]);
        // Impressao da Matriz:
        Imprime(*T);
        // Resultado final:
        if(T->res_lin_meio == 1 || T->res_dig_ED == 1 || T->res_dig_DE == 1)
            printf("\nBingo!\n");
        else
            printf("\nTente outra vez... \n");
    }
    // Nao existe argv para a leitura (matriz aleatoria):
    else{
        Rand_CN(T);
        // Teste das diagonais e linha do meio caso tenha dado bingo:
        T->res_lin_meio = TestaLinha(*T, (T->tamanho - 1) / 2, T->matriz[(T->tamanho - 1) / 2][0]);
        T->res_dig_ED = TestaDiagonalED(*T, T->matriz[0][0]);
        T->res_dig_DE = TestaDiagonalDE(*T, T->matriz[0][T->tamanho - 1]);
        // Impressao da Matriz:
        Imprime(*T);
        // Resultado final:
        if(T->res_lin_meio == 1 || T->res_dig_ED == 1 || T->res_dig_DE == 1)
            printf("\nBingo!\n");
        else
            printf("\nTente outra vez...\n");
    }
}
/****************************************************************************************************************************/

/*Funcoes exclusivas para o Jogo da Velha: */

// Cria uma matriz para a partida de Jogo da Velha de maneira dinamica:
void CriaMatriz_V(Tabuleiro *T){
    int i, j;
    T->matriz = (char **)malloc(3 * sizeof(char *));
    for(i = 0; i < 3; i++)
        T->matriz[i] = (char *)malloc(3 * sizeof(char));
}

// Testa se alguma linha, coluna ou diagonal deu um resultado positivo:
void TestaMatriz_V(Tabuleiro *T, char c){
    int i, j;
    // Inicializando variaveis:
    T->res_lin_1 = 0, T->res_lin_2 = 0, T->res_lin_3 = 0;
    T->res_col_1 = 0, T->res_col_2 = 0, T->res_col_3 = 0;
    T->res_dig_ED = 0, T->res_dig_DE = 0;
    // Testando linhas, colunas, diagonais, caso tenha encontrado vitoria:
    T->res_lin_1 = TestaLinha(*T, 0, c);
    T->res_lin_2 = TestaLinha(*T, 1, c);
    T->res_lin_3 = TestaLinha(*T, 2, c);
    T->res_col_1 = TestaColuna(*T, 0, c);
    T->res_col_2 = TestaColuna(*T, 1, c);
    T->res_col_3 = TestaColuna(*T, 2, c);
    T->res_dig_ED = TestaDiagonalED(*T, c);
    T->res_dig_DE = TestaDiagonalDE(*T, c);
    // Verifica o resultado:
    if(T->res_lin_1 == 1 || T->res_lin_2 == 1 || T->res_lin_3 == 1 ||
    T->res_col_1 == 1 || T->res_col_2 == 1 || T->res_col_3 == 1 ||
    T->res_dig_ED == 1 || T->res_dig_DE == 1){
        printf("\nO vencedor foi %c!\n", c);
        exit(0);
    }
}

// Guarda os valores presentes nos 'argvs' para o Jogo da Velha:
void TrataDados_V(Tabuleiro *T, char *argv[]){
    // Ira fazer com que as funcoes 'caiam' nas condicoes certas:
    T->tamanho = 0;
    // Opcao de partida para o Jogo da Velha:
    if(argv[1] != NULL)
        T->opcao = atoi(argv[1]);
    if(T->opcao < 1 || T->opcao > 3){
        printf("Opcao indisponivel.\n");
        exit(1);
    }
    // Nome do arquivo a ser lido:
    if(argv[2] != NULL)
        strcpy(T->nome_arquivo, argv[2]);
    // Imprimindo valores guardados:
    printf("Opcao digitada: %d\tNome arquivo: %s\n", T->opcao, T->nome_arquivo);
}

// Funcao que realiza a jogada de um jogador no Jogo da Velha:
void Jogada_J(Tabuleiro *T, int i, int j, char c){   
    // Coordenadas fora da matriz:
    while((i < 0 || i > 2)   ||    (j < 0 || j > 2)  ||  T->matriz[i][j] == 'X' || T->matriz[i][j] == 'O'){
        printf("\nCoordenadas ja preenchidas ou invalidas, digite novamente[x y]: ");
        scanf("%d %d", &i, &j);
    }
    // Preenchimento das coordenadas da matriz:
    T->matriz[i][j] = c;
    Imprime(*T);
    // Teste de algum resultado positivo:
    TestaMatriz_V(T, c);
}

// Funcao que realiza a jogada do Computador no Jogo da Velha:
void Jogada_PC(Tabuleiro *T, char c){
    int i, j;
    i = rand() % 3;
    j = rand() % 3;
    // Criacao de novas posicoes caso ja tenham sido utilizadas:
    while(T->matriz[i][j] != '_'){
        i = rand() % 3;
        j = rand() % 3; 
    }
    // Preenchimento das coordenadas da matriz:
    T->matriz[i][j] = c;
    printf("\nO computador escolheu as coordenadas: %d %d\n", i, j);
    Imprime(*T);
    // Teste de algum resultado positivo:
    TestaMatriz_V(T, c);
}

// Realiza o preenchimento da matriz do Jogo da Velha, alternando entre as jogadas:
void Preenche_Matriz(Tabuleiro *T){
    int i;
    int x, y;
    //Leitura das jogadas: 
    for(i = 0; i < 9; i++){
        // Quem joga e o Jogador 1:
        if(i % 2 == 0){
            printf("\nJ1[x y]: ");
            scanf("%d %d", &x, &y);
            Jogada_J(T, x, y, T->op_j1);
        }
        // Quem joga e o Computador ou o Jogador 2:
        else{
            // Computador:
            if(T->opcao == 1){
                Jogada_PC(T, T->op_j2);
            }
            // Jogador 2:
            else{
                printf("\nJ2[x y]: ");
                scanf("%d %d", &x, &y);
                Jogada_J(T, x, y, T->op_j2);
            }
        }
    }
    // Todas as posicoes foram preenchidas e o jogo nao foi interrompido, logo deu Velha.
    printf("\nDeu velha!\n");
}

// Realiza a abertura e a leitura da ordem das jogadas do Jogo da Velha, de um arquivo texto:
void AbreArquivo_V(Tabuleiro *T){
    // Inicializando variaveis:
    FILE *p_arq;
    int i, j;
    int x, y;
    int flag = 0;
    // Tentativa de abertura de arquivo:  
    p_arq = fopen(T->nome_arquivo, "r+");
    if(p_arq != NULL){
        //Leitura das jogadas(limite maximo de 9 jogadas, tabuleiro 3 x 3):
        for(i = 0; i < 9; i++){
            // Jogadas pares: Jogador 1
            if(i % 2 == 0){
                fscanf(p_arq, "%d %d", &x, &y);
                // Verifica se as coordenadas passadas sao validas:
                if((x >= 0)  && (x <= 2) && (y >= 0) && (y <= 2)){
                    T->matriz[x][y] = 'X';
                    printf("\nJ1: %d %d\n", x, y);
                    Imprime(*T);
                    TestaMatriz_V(T, 'X');
                }
            }
            // Jogadas impares: Jogador 2
            else {
                fscanf(p_arq, "%d %d", &x, &y);
                // Verifica se as coordenadas passadas sao validas: 
                if((x >= 0)  && (x <= 2) && (y >= 0) && (y <= 2)){
                    T->matriz[x][y] = 'O';
                    printf("\nJ2: %d %d\n", x, y);
                    Imprime(*T);
                    TestaMatriz_V(T, 'O');
                }
            }
        }
        // Resultado inconclusivo / Velha:
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                if(T->matriz[i][j] == '_')
                    flag = 1;
        if(flag == 1)
            printf("\nResultado inconclusivo!\n");
        else      
            printf("\nDeu velha!\n");
    }
    // Nao foi encontrado o arquivo especificado:
    else {
        printf("Atencao usuario, nao foi encontrado o arquivo correspondente.\n");
        exit(1);
    }
    fclose(p_arq);
}

// Realiza a partida de Caca-Niqueis, bem como o uso de todas as funcoes principais:
void Partida_V(Tabuleiro *T, char *argv[]){
    // Chamada das funcoes iniciais:
    TrataDados_V(T, argv);
    CriaMatriz_V(T);
    MarcaTodos(T, '_');
    //Opcoes de partida:
    // Opcao 1: Jogador x Computador.
    if(T->opcao == 1){
        printf("Voce escolheu a opcao Jogador x Computador!\n\n");
        // Selecao das opcoes:
        printf("Digite o caracter correspondente ao Jogador 1[X/O]: ");
        scanf("%c", &T->op_j1);
        // Foi digitado um valor incorreto:
        while(T->op_j1 != 'X' && T->op_j1 != 'O'){
            printf("\nOpcao invalida, digite novamente[X/O]: ");
            scanf(" %c", &T->op_j1);
        }
        //Opcao recebida pelo computador:
        if(T->op_j1 == 'X')
            T->op_j2 = 'O';
        else
            T->op_j2 = 'X';
        // Impressao das jogadas escolhidas:
        printf("Jogador 1: %c\tComputador: %c\n", T->op_j1, T->op_j2);
        printf("\n");
        //Inicio do Jogo:
        Preenche_Matriz(T);
    }
    // Opcao 2: Jogador x Joga
    else if(T->opcao == 2){
        printf("Voce escolheu a opcao Jogador x Jogador!\n\n");
        // Selecao das opcoes:
        printf("Digite o caracter correspondente ao Jogador 1[X/O]: ");
        scanf("%c", &T->op_j1);
        // Foi digitado um valor incorreto:
        while(T->op_j1 != 'X' && T->op_j1 != 'O'){
            printf("\nOpcao invalida, digite novamente[X/O]: ");
            scanf(" %c", &T->op_j1);
        }
        // Opcao recebida pelo Jogador 2:
        if(T->op_j1 == 'X')
            T->op_j2= 'O';
        else
            T->op_j2 = 'X';
        printf("Jogador 1: %c\tJogador 2: %c\n", T->op_j1, T->op_j2);
        printf("\n");
        //Inicio do jogo:
        Preenche_Matriz(T);
    }
    // Opcao 3: Leitura de jogadas no arquivo texto.
    else{
        printf("Voce escolheu a opcao leitura de arquivo!\n");
        AbreArquivo_V(T);
    }
}   