#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int prioridade;
    int ordem;
} Elemento;

typedef struct {
    Elemento* dados;
    int tamanho;
    int capacidade;
} HeapMax;

HeapMax* criarHeap(int capacidade) {
    HeapMax* heap = (HeapMax*)malloc(sizeof(HeapMax));
    heap->dados = (Elemento*)malloc(sizeof(Elemento) * capacidade);
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}

void reheapUp(HeapMax* heap, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        Elemento atual = heap->dados[i];
        Elemento paiElem = heap->dados[pai];

        if (atual.prioridade > paiElem.prioridade ||
           (atual.prioridade == paiElem.prioridade && atual.ordem < paiElem.ordem)) {
            heap->dados[i] = paiElem;
            heap->dados[pai] = atual;
            i = pai;
        } else {
            break;
        }
    }
}

void reheapDown(HeapMax* heap, int i) {
    while(1) {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int maior = i;

        if (esq < heap->tamanho) {
            Elemento esqElem = heap->dados[esq];
            Elemento maiorElem = heap->dados[maior];
            if (esqElem.prioridade > maiorElem.prioridade ||
               (esqElem.prioridade == maiorElem.prioridade && esqElem.ordem < maiorElem.ordem)) {
                maior = esq;
            }
        }

        if (dir < heap->tamanho) {
            Elemento dirElem = heap->dados[dir];
            Elemento maiorElem = heap->dados[maior];
            if (dirElem.prioridade > maiorElem.prioridade ||
               (dirElem.prioridade == maiorElem.prioridade && dirElem.ordem < maiorElem.ordem)) {
                maior = dir;
            }
        }

        if (maior != i) {
            Elemento temp = heap->dados[i];
            heap->dados[i] = heap->dados[maior];
            heap->dados[maior] = temp;
            i = maior;
        } else {
            break;
        }
    }
}

void inserir(HeapMax* heap, int prioridade, int ordem) {
    if (heap->tamanho == heap->capacidade) {
        printf("Heap cheio!\n");
        return;
    }

    Elemento novo;
    novo.prioridade = prioridade;
    novo.ordem = ordem;
    heap->dados[heap->tamanho] = novo;
    reheapUp(heap, heap->tamanho);
    heap->tamanho++;
}


Elemento extrairMax(HeapMax* heap) {
    Elemento raiz = heap->dados[0];
    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--; p
    reheapDown(heap, 0);
    return raiz;
}


void imprimirHeap(HeapMax* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("(Prioridade:%d, Ordem:%d) ", heap->dados[i].prioridade, heap->dados[i].ordem);
    }
    printf("\n");
}


int main() {
    HeapMax* heap = criarHeap(7);

    // 3 prioridades: (1 - menor), (2 - média), (3 - maior)
    inserir(heap, 1, 1);
    inserir(heap, 3, 2);
    inserir(heap, 2, 3);
    inserir(heap, 2, 4);
    inserir(heap, 3, 5);
    inserir(heap, 1, 6);
    inserir(heap, 3, 7);

    imprimirHeap(heap);

    printf("\nOrdem de atendimento:\n");
    while (heap->tamanho > 0) {
        Elemento e = extrairMax(heap);
        printf("Prioridade: %d, Ordem: %d\n", e.prioridade, e.ordem);
    }

    free(heap->dados);
    free(heap);

    return 0;
}

