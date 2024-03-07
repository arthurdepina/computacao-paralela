// Versão do Código sem uso de Threads.

#include <stdio.h>

#define M 2 // Número de linhas da matriz
#define N 3 // Número de colunas da matriz e linhas do vetor

void multiplyMatrixByVector(int matrix[M][N], int vector[N], int result[M]) {
    for (int i = 0; i < M; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int matrix[M][N] = {
        {1, -1, 2},
        {0, -3, 1}
    };
    int vector[N] = {2, 1, 0};
    int result[M];

    multiplyMatrixByVector(matrix, vector, result);

    printf("Resulting vector:\n");
    for (int i = 0; i < M; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}
