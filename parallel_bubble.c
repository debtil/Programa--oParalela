#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void troca();

int main(int argc, char *argv[]){
    int TAMANHO = 100000;
    int vetor[TAMANHO];

    for(int i = 0; i < TAMANHO; i++){
        vetor[i]=rand()%TAMANHO;
    }

    int numeros = TAMANHO;
    int i = 0, j = 0, primeiro;
    
    double start = omp_get_wtime();
    for(int i = 0; i < numeros - 1; i++){
        primeiro = i % 2;
        #pragma omp parallel for default(none), shared(vetor, primeiro, numeros)
        for(j = primeiro; j < numeros - 1; j += 1){
            if(vetor[j] > vetor[j + 1]){
                troca(&vetor[j], &vetor[j + 1]);
            }
        }
    }
    double finish = omp_get_wtime();
    double time_spent = finish - start;

    for(i = 0; i < TAMANHO; i++){
        printf(" %d", vetor[i]);
    }

    printf("\n tempo de execução do código paralelizado: %f\n", time_spent);
}

void troca(int *n1, int *n2){
    int aux;
    aux = *n1;
    *n1 = *n2;
    *n2 = aux;
}