#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 4000 // Número total de linhas da matriz
#define N 8000 // Número de colunas da matriz e tamanho do vetor

int matrix[M][N];
int vector[N];
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
                  // ascii to integer
    int numThreads = atoi(argv[1]);
    if (numThreads <= 0) {
        printf("Número de threads deve ser maior que 0.\n");
        return 1;
    }
    if (numThreads > M) numThreads = M;

    int value = 0;
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            matrix[i][j] = value++;
        }
    }

    for(int i = 0; i < N; i++) {
        vector[i] = (i % 2 == 0) ? 1 : -1;
    }

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
