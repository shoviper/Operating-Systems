#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M1_ROWS 2
#define M1_COLS 3
#define M2_ROWS 3
#define M2_COLS 2

typedef struct {
    int row;
    int col;
    int (*multiplicand)[M1_COLS];
    int (*multiplier)[M2_COLS];
    int *result;
} ThreadData;

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int sum = 0;
    for (int i = 0; i < M1_COLS; i++) {
        sum += data->multiplicand[data->row][i] * data->multiplier[i][data->col];
    }
    *data->result = sum;
    pthread_exit(0);
}

int main() {
    int multiplicand[M1_ROWS][M1_COLS] = {
        {5, 6, 7},
        {4, 8, 9}
    };

    int multiplier[M2_ROWS][M2_COLS] = {
        {6, 4},
        {5, 7},
        {1, 1}
    };

    int result[M1_ROWS][M2_COLS];
    pthread_t threads[M1_ROWS * M2_COLS];
    ThreadData threadData[M1_ROWS * M2_COLS];

    int threadIndex = 0;

    for (int i = 0; i < M1_ROWS; i++) {
        for (int j = 0; j < M2_COLS; j++) {
            threadData[threadIndex].row = i;
            threadData[threadIndex].col = j;
            threadData[threadIndex].multiplicand = multiplicand;
            threadData[threadIndex].multiplier = multiplier;
            threadData[threadIndex].result = &result[i][j];

            pthread_create(&threads[threadIndex], NULL, multiply, &threadData[threadIndex]);
            threadIndex++;
        }
    }

    for (int i = 0; i < threadIndex; i++) {
        pthread_join(threads[i], NULL);
    }


    printf("Result matrix:\n");
    for (int i = 0; i < M1_ROWS; i++) {
        for (int j = 0; j < M2_COLS; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}