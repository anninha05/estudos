#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellSort(int v[], int n) {
    int h = 1;

    while (h <= (n - 1) / 3) {
        h = 3 * h + 1;
    }

    while (h > 0) {
        for (int j = h; j < n; j++) {
            int key = v[j];
            int i = j;

            while ((i - h) >= 0 && key < v[i - h]) {
                v[i] = v[i - h];
                i = i - h;
            }
            v[i] = key;
        }
        h = (h - 1) / 3;
    }
}

void criaHeap(int *v, int pai, int fim){
    int aux = v[pai];
    int filho = 2 * pai + 1;

    while (filho <= fim) {
        if (filho < fim) {
            if (v[filho] < v[filho + 1]) {
                filho++;
            }
        }
        if (aux < v[filho]) {
            v[pai] = v[filho];
            pai = filho;
            filho = 2 * pai + 1;
        } else {
            filho = fim + 1;
        }
    }
    v[pai] = aux;
}

void heapsort(int* v, int n){
    int i, aux;

    for (i = (n - 1) / 2; i >= 0; i--) {
        criaHeap(v, i, n - 1);
    }

    for (i = n - 1; i >= 1; i--) {
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        criaHeap(v, 0, i - 1);
    }
}

void merge(int* v, int inicio, int meio, int fim){
    int* temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int*) malloc(tamanho * sizeof(int));
    if(temp != NULL){
        for(i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                if(v[p1] < v[p2]) {
                    temp[i] = v[p1++];
                } else {
                    temp[i] = v[p2++];
                }
                if(p1 > meio) {
                    fim1 = 1;
                }
                if(p2 > fim) {
                    fim2 = 1;
                }
            }else{
                if(!fim1) {
                    temp[i] = v[p1++];
                } else {
                    temp[i] = v[p2++];
                }
            }
        }
        for(j = 0, k = inicio; j < tamanho; j++, k++) {
            v[k] = temp[j];
        }

    }
    free(temp);
}

void mergesort(int* v, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio + fim) / 2);
        mergesort(v, inicio, meio);
        mergesort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

int particiona(int* v, int inicio, int final){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = final;
    pivo = v[inicio];
    while(esq < dir){
        while(esq <= final && v[esq] <= pivo)
            esq++;
        while(dir >= 0 && v[dir] > pivo)
            dir--;
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
        }
    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    return dir;
}

void quicksort(int* v, int inicio, int fim){
    int pivo;
    if(fim > inicio){
        pivo = particiona(v, inicio, fim);
        quicksort(v, inicio, pivo - 1);
        quicksort(v, pivo + 1, fim);
    }
}

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
        copia[i] = vOriginal[i];
    }
    return copia;
}

void tempoGasto(clock_t inicio, clock_t fim) {
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("%.5f segundos", tempo);
}

int main() {
    srand(time(NULL));

    int qtd;
    printf("Informe a quantidade de numeros aleatorios que deseja ordenar: ");
    scanf("%d", &qtd);

    int* vetorOriginal = gerarVetor(qtd);

    /*if (qtd <= 100) {
        printf("\nVetor gerado: ");
        for(int i = 0; i < qtd; i++) {
            printf("%d ", vetorOriginal[i]);
        }
    }*/

    clock_t inicio, fim;

    printf("\n--- Desempenho dos algoritmos ---");

    int* v1 = copiarVetor(vetorOriginal, qtd);
    inicio = clock();
    shellSort(v1, qtd);
    fim = clock();
    printf("\ni) Shellsort: ");
    tempoGasto(inicio, fim);
    free(v1);

    int* v2 = copiarVetor(vetorOriginal, qtd);
    inicio = clock();
    heapsort(v2, qtd);
    fim = clock();
    printf("\nii) Heapsort: ");
    tempoGasto(inicio, fim);
    free(v2);

    int* v3 = copiarVetor(vetorOriginal, qtd);
    inicio = clock();
    mergesort(v3, 0, qtd - 1);
    fim = clock();
    printf("\niii) Mergesort: ");
    tempoGasto(inicio, fim);
    free(v3);

    int* v4 = copiarVetor(vetorOriginal, qtd);
    inicio = clock();
    quicksort(v4, 0, qtd - 1);
    fim = clock();
    printf("\niv) Quicksort: ");
    tempoGasto(inicio, fim);
    free(v4);

    /*printf("\nVetor ordenado: ");
        for(int i = 0; i < qtd; i++) {
            printf("%d ", v4[i]);
    }*/
    free(vetorOriginal);
    return 0;
}

