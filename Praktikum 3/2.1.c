#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 3 // Größe der quadratischen Matrizen
#define MAX_RANDOM_VALUE 5 // Maximale Zufallszahl

int matrix1[MATRIX_SIZE][MATRIX_SIZE];
int matrix2[MATRIX_SIZE][MATRIX_SIZE];
int result[MATRIX_SIZE][MATRIX_SIZE];

void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void *multiplyRow(void *arg) {
    int row = *((int *)arg);
    printf("Thread ID: %ld\n", pthread_self());

    for (int j = 0; j < MATRIX_SIZE; j++) {
        result[row][j] = 0;
        for (int k = 0; k < MATRIX_SIZE; k++) {
            result[row][j] += matrix1[row][k] * matrix2[k][j];
        }
    }

    printf("Thread ID: %ld finished.\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    // Initialisierung der Matrizen mit Zufallszahlen
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix1[i][j] = rand() % (MAX_RANDOM_VALUE + 1);
            matrix2[i][j] = rand() % (MAX_RANDOM_VALUE + 1);
        }
    }

    printf("Matrix 1:\n");
    printMatrix(matrix1);

    printf("Matrix 2:\n");
    printMatrix(matrix2);

    pthread_t threads[MATRIX_SIZE];
    int thread_args[MATRIX_SIZE];

    // Starten der Threads
    for (int i = 0; i < MATRIX_SIZE; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, multiplyRow, &thread_args[i]);
    }

    // Warten auf Beendigung der Threads
    for (int i = 0; i < MATRIX_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Result Matrix:\n");
    printMatrix(result);

    return 0;
}
