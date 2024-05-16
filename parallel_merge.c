#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);
            #pragma omp section
            mergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main(int argc, char *argv[]) {
    int TAMANHO = 100000;
    int vetor[TAMANHO];

    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = rand() % TAMANHO;
    }

    double start = omp_get_wtime();
    mergeSort(vetor, 0, TAMANHO - 1);
    double finish = omp_get_wtime();
    double time_spent = finish - start;

    for (int i = 0; i < TAMANHO; i++) {
        printf(" %d", vetor[i]);
    }

    printf("\n tempo de execução do código paralelizado: %f\n", time_spent);

    return 0;
}