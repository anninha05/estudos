#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellsort() {}
void heapsort() {}
void mergesort() {}
void quicksort() {}

int* gerarVetor(int n) {
    int* v = (int*) malloc(n * sizeof(int));
    if (v == NULL) {
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    for(int i = 0; i < n; i++) {
        v[i] = rand() % n;
    }
    return v;
}

int* copiarVetor(int* vOriginal, int n) {
    int* copia = (int*) malloc(n * sizeof(int));
    if(copia == NULL) {
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    for(int i = 0; i < n; i++) {
        copia[i] = vOrigial[i];
    }
    return copia;
}

void tempoGasto(clock_t inicio, clock_t fim) {
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("%.2f segundos", tempo);
}

int main() {
    srand(time(NULL));

    int qtd;
    printf("Informe a quantidade de numeros aleatorios que deseja ordenar: ");
    scanf("%d", &qtd);

    int* vetorOriginal = gerarVetor(qtd);

    clock_t inicio, fim;

    printf("\n--- Desempenho dos algoritmos ---");

    int* v1 = copiarVetor();
    inicio = clock();
    shellsort();
    fim = clock();
    printf("\nShellsort: ");
    tempoGasto();
    free(v1);

    int* v2 = copiarVetor();
    inicio = clock();
    heapsort();
    fim = clock();
    printf("\nHeapsort: ");
    tempoGasto();
    free(v2);

    int* v3 = copiarVetor();
    inicio = clock();
    mergesort();
    fim = clock();
    printf("\nMergesort: ");
    tempoGasto();
    free(v3);

    int* v4 = copiarVetor();
    inicio = clock();
    quicksort();
    fim = clock();
    printf("\nQuicksort: ");
    tempoGasto();
    free(v4);

    free(vetorOriginal);
    return 0;
}

