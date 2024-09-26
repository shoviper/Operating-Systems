#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);
    int pipe_fd[2];
    pid_t pid;
    char buffer[50];

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {  // Child process
        printf("Child: I am calculating\n");

        // Calculate the summation from 1 to the specified number
        int sum = 0;
        for (int i = 1; i <= number; i++) {
            sum += i;
        }

        printf("Child: the result is %d\n", sum);
        printf("Child: I am sending data\n");

        // Convert the sum to a string
        sprintf(buffer, "%d", sum);

        // Write the result to the pipe
        write(pipe_fd[1], buffer, strlen(buffer) + 1);

        printf("Child: Goodbye\n");

        // Close the write end of the pipe
        close(pipe_fd[1]);
    } else {  // Parent process
        printf("Parent: waiting for my child\n");

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Read the result from the pipe
        read(pipe_fd[0], buffer, sizeof(buffer));

        printf("Parent: sum from my child is %s\n", buffer);
        printf("Parent: Goodbye\n");

        // Close the read end of the pipe
        close(pipe_fd[0]);
    }

    return 0;
}