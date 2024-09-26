#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);
    int shm_id;
    int *shm_ptr;

    // Create shared memory
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        return 1;
    }
    printf("Parent: I have created a shared memory for result...\n");

    // Attach shared memory
    shm_ptr = (int *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (int *)-1) {
        perror("shmat");
        return 1;
    }
    printf("Parent: I have attached the shared memory...\n");

    // Fork a child process
    printf("Parent: I am about to fork a child process...\n");
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {  // Child process
        printf("Parent: Waiting for my child\n");
        printf("Child: I am calculating\n");

        // Calculate the summation from 1 to the specified number
        int sum = 0;
        for (int i = 1; i <= number; i++) {
            sum += i;
        }

        printf("Child: The result is %d\n", sum);

        // Write the result to shared memory
        *shm_ptr = sum;
        printf("Child: Goodbye\n");
    } else {  // Parent process
        // Wait for the child to finish
        wait(NULL);

        // Read the result from shared memory
        printf("Parent: sum from my child is %d\n", *shm_ptr);

        // Detach and remove the shared memory
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            return 1;
        }
        printf("Parent: I have detached the shared memory...\n");

        if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            return 1;
        }
        printf("Parent: I have removed the shared memory...\n");

        printf("Parent: Goodbye\n");
    }

    return 0;
}