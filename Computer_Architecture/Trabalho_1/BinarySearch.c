#include <stdio.h>
#include <stdlib.h>

// Funcao que executa a Binary Search de maneira recursiva
int binarySearch(int arr[], int l , int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

// Funcao principal do programa
int main(void) {
    // Declaracao de variaveis
    int tamanho = 0;
    int *array;
    int resultado = 0;
    int elemento = 0;

    // Insercao do tamanho do array
    printf("Digite a quantidade de elementos do array: ");           
    scanf("%d", &tamanho);

    // Alocação de espaçao para o array a ser criado
    array = malloc(tamanho * sizeof(int));                     
    printf("\n");
    
    // Loop de execucao que preenche array
    for (int i = 0; i < tamanho; i++){                               
        printf("Digite o %d° elemento: ", i + 1);
        scanf("%d", &array[i]);
    }

    // Impressao do array a ser utilizado no exemplo
    printf("\nArray do exemplo:\t");                                        
    for (int i = 0; i < tamanho; i++){
        printf("%d\t", array[i]);
    }

    // Entrada do valor a ser pesquisado
    printf("\n");
    printf("Entre com o valor a ser pesquisado: ");
    scanf("%d", &elemento);

    // Resultado final da pesquisa
    resultado = binarySearch(array, 0, tamanho - 1, elemento);
    (resultado == -1) ? printf("\nElemento nao foi encontrado no arranjo!\n") : printf("\nElemento na posicao [%d] do array!\n", resultado);
    printf("\n");
    
    return 0;
}