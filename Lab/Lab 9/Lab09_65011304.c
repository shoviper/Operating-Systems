#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define BUFFER_SIZE 4
#define NUM_ITEMS 40  

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void insertbuffer(int item) {
    sem_wait(&empty);  
    pthread_mutex_lock(&mutex); 

    // Insert item into buffer
    buffer[in] = item;
    printf("Producer entered %d Buffer size = %d\n", item, (in - out + BUFFER_SIZE) % BUFFER_SIZE + 1);
    in = (in + 1) % BUFFER_SIZE;  

    pthread_mutex_unlock(&mutex);  
    sem_post(&full);  
}

int readbuffer() {
    sem_wait(&full); 
    pthread_mutex_lock(&mutex); 

    int item = buffer[out];
    printf("Consumer consumed %d Buffer size = %d\n", item, (in - out + BUFFER_SIZE) % BUFFER_SIZE);
    out = (out + 1) % BUFFER_SIZE;  

    pthread_mutex_unlock(&mutex);  
    sem_post(&empty);  

    return item;
}

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        insertbuffer(i);  
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        readbuffer();  
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    sem_init(&empty, 0, BUFFER_SIZE);  
    sem_init(&full, 0, 0);  
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}