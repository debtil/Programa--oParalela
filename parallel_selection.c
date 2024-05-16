#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
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

    double start_time = omp_get_wtime(); // Inicia a contagem de tempo

    // Algoritmo Selection Sort paralelizado com OpenMP
    for (int i = 0; i < n - 1; i++) {
        int the_min, tmp;

        // Bloco Paralelo
        #pragma omp parallel default(shared) private(the_min, tmp)
        {
            // Inicialização do Mínimo Local
            the_min = i;

            // Determinação do Mínimo Local
            #pragma omp for
            for (int j = i + 1; j < n; j++) {
                if (v[j] < v[the_min]) {
                    the_min = j;
                }
            }

            // Troca de Elementos (Seção Crítica)
            #pragma omp critical
            {
                if (v[the_min] < v[i]) {
                    tmp = v[i];
                    v[i] = v[the_min];
                    v[the_min] = tmp;
                }
            }
        }
    }

    double end_time = omp_get_wtime(); // Finaliza a contagem de tempo

    
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    printf("\nTempo de execução: %f segundos\n", end_time - start_time);

    free(v); // Libera a memória alocada para o array

    return 0;
}
