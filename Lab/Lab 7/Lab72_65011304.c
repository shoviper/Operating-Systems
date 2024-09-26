#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 5

// Function to handle SIGTERM in the child process
void sigterm_handler(int signum) {
    printf("Child: my id is %d, my parent has just terminated me\n", getpid());
    exit(0);
}

int main() {
    pid_t pids[NUM_CHILDREN];
    int i;

    // Fork 5 children
    for (i = 0; i < NUM_CHILDREN; ++i) {
        pids[i] = fork();
        if (pids[i] < 0) {
            // Fork failed
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pids[i] == 0) {
            // Child process
            signal(SIGTERM, sigterm_handler);  // Set up signal handler in the child
            printf("Child: my id is %d\n", getpid());
            
            // Enter an infinite loop
            while (1) {
                pause(); // Wait for signals
            }
        }
    }

    // Parent process
    sleep(2);  // Give time for children to enter their infinite loops

    // Send SIGTERM to all child processes
    for (i = 0; i < NUM_CHILDREN; ++i) {
        kill(pids[i], SIGTERM);
    }

    // Wait for all children to terminate
    for (i = 0; i < NUM_CHILDREN; ++i) {
        wait(NULL);
    }
    
    printf("Parent: I have killed all of my children\n");

    return 0;
}
