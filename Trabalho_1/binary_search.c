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
    // Exemplo 1: O numero guardado na variavel x sera encontrado
    int exemplo_1[] = {2, 3, 4, 10, 25, 32, 40, 65, 132, 322, 541, 700, 1060, 2000, 3450};
    int n1 = sizeof(exemplo_1) / sizeof(exemplo_1[0]);
    int x1 = 25;
    int resultado_1 = binarySearch(exemplo_1, 0, n1 - 1, x1);
    (resultado_1 == -1) ? printf("\nElemento fora do exemplo 1") : printf("\nElemento no indice %d do exemplo 1", resultado_1);
    printf("\n");

    // Exemplo 2: O numero guardado na variavel x nao sera encontrado
    int exemplo_2[] = {116, 231, 267, 289, 306, 350, 397, 406, 456, 491, 665, 699, 707, 730, 750, 780, 899};
    int n2 = sizeof(exemplo_2) / sizeof(exemplo_2[0]);
    int x2 = 750;
    int resultado_2 = binarySearch(exemplo_2, 0, n2 - 1, x2);
    (resultado_2 == -1) ? printf("\nElemento fora do exemplo 2") : printf("\nElemento no indice %d do exemplo 2", resultado_2);
    printf("\n");

    // Exemplo 3:
    int exemplo_3[] = {679, 832, 980, 999, 1016, 1093, 1160, 1270, 1430, 1871, 2021, 2022, 3229, 3500, 4004};
    int n3 = sizeof(exemplo_3) / sizeof(exemplo_3[0]);
    int x3 = 2018;
    int resultado_3 = binarySearch(exemplo_3, 0, n3 - 1, x3);
    (resultado_3 == -1) ? printf("\nElemento fora do exemplo 3") : printf("\nElemento no indice %d do exemplo 3", resultado_3);
    printf("\n");

    printf("\n");
    return 0;
}