#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 2 // Número total de linhas da matriz
#define N 3 // Número de colunas da matriz e tamanho do vetor

int matrix[M][N] = {
    {1, -1, 2},
    {0, -3, 1}
};
int vector[N] = {2, 1, 0};
int result[M] = {0};

typedef struct {
    int startRow;
    int endRow;
} ThreadData;

void* computeRange(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->startRow; i <= data->endRow; i++) {
        for (int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <numero de threads>\n", argv[0]);
        return 1;
    }

    int numThreads = atoi(argv[1]);
    if (numThreads <= 0) {
        printf("Número de threads deve ser maior que 0.\n");
        return 1;
    }
    if (numThreads > M) numThreads = M;

    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];

    int rowsPerThread = M / numThreads;
    int extraRows = M % numThreads;

    int currentRow = 0;
    for (int i = 0; i < numThreads; i++) {
        threadData[i].startRow = currentRow;
        currentRow += rowsPerThread + (extraRows > 0 ? 1 : 0); // Distribui as linhas extras
        threadData[i].endRow = currentRow - 1;
        extraRows--;

        if (pthread_create(&threads[i], NULL, computeRange, (void*)&threadData[i])) {
            printf("Erro ao criar thread\n");
            exit(-1);
        }
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Vetor resultante:\n");
    for (int i = 0; i < M; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}
