/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B2-2                                 */
/*             Objetivo: << Bubblesort com ordem ascendente >>                      */
/*                                                                                  */
/*                                Autor: Matheus David Carbone Luna                 */
/*                                                                  Data:08/05/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Digite o número de elementos: ");
    scanf("%d", &n);

    int arr[n];
    printf("Digite %d números:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bubbleSort(arr, n);

    printf("Array ordenado em ordem ascendente: ");
    printArray(arr, n);

    return 0;
}
