#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void troca(int *n1, int *n2);

int main(int argc, char *argv[]) {
    int n = 100000; // Tamanho do array
    int *v = (int *)malloc(n * sizeof(int));
    srand(time(NULL));

    // Preenche o array com números aleatórios
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100000;
    }

    clock_t start_time = clock(); // Inicia a contagem de tempo

    // Algoritmo Selection Sort sequencial
    for (int i = 0; i < n - 1; i++) {
        int the_min = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[the_min]) {
                the_min = j;
            }
        }
        // Troca de Elementos
        if (the_min != i) {
            troca(&v[i], &v[the_min]);
        }
    }

    clock_t end_time = clock(); // Finaliza a contagem de tempo

    
     for (int i = 0; i < n; i++) {
         printf("%d ", v[i]);
     }

    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\nTempo de execução: %f segundos\n", total_time);

    free(v); // Libera a memória alocada para o array

    return 0;
}

void troca(int *n1, int *n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
