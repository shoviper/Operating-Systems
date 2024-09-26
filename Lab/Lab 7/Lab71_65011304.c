#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void sigint_handler(int signum) {
    // This function is called when SIGINT is received
    printf("Get SIGINT from child\n");
    printf("parent: Bye\n");
    exit(0);
}

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("child: Sleeping for 5 seconds\n");
        sleep(5);

        // Send SIGINT signal to the parent
        printf("child: sending SIGINT\n");
        kill(getppid(), SIGINT);

        printf("child: Bye\n");
        exit(0);
    } else {
        // Parent process
        // Register SIGINT signal handler
        signal(SIGINT, sigint_handler);

        printf("parent: Waiting for my child to send SIGINT\n");

        // Parent process runs in an infinite loop until it gets SIGINT
        while (1) {
            pause(); // Wait for signals
        }
    }

    return 0;
}
