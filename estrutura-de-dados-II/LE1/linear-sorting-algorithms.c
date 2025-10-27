#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N1 50000
#define N2 100000

int* gerarVetor(int n){
    int* v = (int*)malloc(n*sizeof(int));
    if (v == NULL){
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    for(int i = 0; i < n; i++){
        v[i] = rand()%n;
    }
    return v;
}

int* copiarVetor(int* vOriginal, int n){
    int* copia = (int*)malloc(n*sizeof(int));
    if(copia == NULL){
        printf("Erro ao alocar memoria.");
        exit(1);
    }
    for(int i = 0; i < n; i++) {
        copia[i] = vOriginal[i];
    }
    return copia;
}

void tempoGasto(clock_t inicio, clock_t fim){
    double tempo = ((double)(fim - inicio)) * 1000/CLOCKS_PER_SEC;
    printf("%.5f ms", tempo);
}

void imprimirVetor(int* v, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
}

void countingSort(int v[], int n){
    int max = v[0];
    for(int i = 1; i < n; i++){
        if(v[i] > max)
            max = v[i];
    }

    int* freq = (int*)calloc(max+1, sizeof(int));
    int* saida = (int*)malloc(n*sizeof(int));

    for(int i = 0; i < n; i++){
        freq[v[i]]++;
    }
    for(int i = 1; i <= max; i++){
        freq[i] += freq[i-1];
    }
    for(int i = n-1; i >= 0; i--){
        saida[freq[v[i]] - 1] = v[i];
        freq[v[i]]--;
    }
    for(int i = 0; i < n; i++){
        v[i] = saida[i];
    }

    free(freq);
    free(saida);
}

int getMax(int v[], int n){
    int max = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

void countingSortExp(int v[], int n, int exp){
    int* saida = (int*)malloc(n*sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(v[i]/exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--){
        saida[count[(v[i]/exp) % 10] - 1] = v[i];
        count[(v[i]/exp)%10]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = saida[i];

    free(saida);
}

void radixSort(int v[], int n){
    int max = getMax(v, n);
    for (int exp = 1; max/exp > 0; exp *= 10)
        countingSortExp(v, n, exp);
}

void bucketSort(int v[], int n){
    int max = v[0], min = v[0];
    for (int i = 1; i < n; i++){
        if (v[i] > max) max = v[i];
        if (v[i] < min) min = v[i];
    }

    int bucketCount = n/10 + 1;
    int range = (max - min + 1)/bucketCount + 1;

    int** buckets = (int**)malloc(bucketCount*sizeof(int*));
    int* sizes = (int*)calloc(bucketCount, sizeof(int));

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int*)malloc(n*sizeof(int));
        sizes[i] = 0;
    }

    for (int i = 0; i < n; i++){
        int idx = (v[i] - min)/range;
        buckets[idx][sizes[idx]++] = v[i];
    }

    int k = 0;
    for (int i = 0; i < bucketCount; i++){
        for (int j = 1; j < sizes[i]; j++){
            int key = buckets[i][j];
            int m = j - 1;
            while (m >= 0 && buckets[i][m] > key){
                buckets[i][m + 1] = buckets[i][m];
                m--;
            }
            buckets[i][m + 1] = key;
        }
        for (int j = 0; j < sizes[i]; j++){
            v[k++] = buckets[i][j];
        }
        free(buckets[i]);
    }
    free(buckets);
    free(sizes);
}

void ordenaVetor(int N){
    int* Voriginal = gerarVetor(N);
    int* Vcopia;

    clock_t inicio, fim;

    if (N < 50){
        printf("\nVetor original:\n");
        imprimirVetor(Voriginal, N);
    }

    Vcopia = copiarVetor(Voriginal, N);
    printf("\nCountingSort: ");
    inicio = clock();
    countingSort(Vcopia, N);
    fim = clock();
    tempoGasto(inicio, fim);
    if (N < 50){
        printf("\nOrdenado (Counting Sort):\n");
        imprimirVetor(Vcopia, N);
    }
    free(Vcopia);

    Vcopia = copiarVetor(Voriginal, N);
    printf("\nRadixSort:   ");
    inicio = clock();
    radixSort(Vcopia, N);
    fim = clock();
    tempoGasto(inicio, fim);
    if (N < 50){
        printf("\nOrdenado (Radix Sort):\n");
        imprimirVetor(Vcopia, N);
    }
    free(Vcopia);

    Vcopia = copiarVetor(Voriginal, N);
    printf("\nBucketSort:  ");
    inicio = clock();
    bucketSort(Vcopia, N);
    fim = clock();
    tempoGasto(inicio, fim);
    if (N < 50){
        printf("\nOrdenado (Bucket Sort):\n");
        imprimirVetor(Vcopia, N);
    }
    free(Vcopia);

    free(Voriginal);
    printf("\n");
}

int main(){
    srand(time(NULL));

    int N;

    /*printf("\nDigite o tamanho do vetor para teste: ");
    scanf("%d", &N);*/

    printf("\n\nTeste do vetor de %d elementos:", N);
    ordenaVetor(N);

    printf("\n\nTeste do vetor de %d elementos:", N1);
    ordenaVetor(N1);

    printf("\n\nTeste do vetor de %d elementos:", N2);
    ordenaVetor(N2);
}

