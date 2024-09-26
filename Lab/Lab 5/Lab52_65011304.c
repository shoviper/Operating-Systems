#include <stdio.h>
#include <pthread.h>

typedef struct {
    int number;
    int result;
} ThreadData;

int calculateSummation(int num) {
    int sum = 0;
    for (int i = 1; i <= num; i++) {
        sum += i;
    }
    return sum;
}

void* childSummation(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->result = calculateSummation(2 * data->number);
    return NULL;
}

int main() {
    int number;
    ThreadData threadData;
    pthread_t thread;

    printf("Enter a number: ");
    scanf("%d", &number);

    int parentSum = calculateSummation(number);

    threadData.number = number;

    pthread_create(&thread, NULL, childSummation, &threadData);

    pthread_join(thread, NULL);

    int childSum = threadData.result;

    int finalResult = parentSum + childSum;

    printf("Final result: %d\n", finalResult);

    return 0;
}