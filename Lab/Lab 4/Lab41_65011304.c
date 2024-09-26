#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int choice;
    pid_t pid;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. ls\n");
        printf("2. date\n");
        printf("3. ps\n");
        printf("0. exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Executing ls...\n");
                pid = fork();
                if (pid == 0) {
                    
                    execlp("ls", "ls", "-l", NULL);
                    perror("execlp ls failed");
                    exit(EXIT_FAILURE);
                } else if (pid > 0) {
                    wait(NULL);
                } else {
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                }
                break;
                
            case 2:
                printf("Executing date...\n");
                pid = fork();
                if (pid == 0) {

                    execlp("date", "date", NULL);
                    perror("execlp date failed");
                    exit(EXIT_FAILURE);
                } else if (pid > 0) {
                    wait(NULL);
                } else {
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                }
                break;
                
            case 3:
                printf("Executing ps...\n");
                pid = fork();
                if (pid == 0) {
                    
                    execlp("ps", "ps", NULL);
                    perror("execlp ps failed");
                    exit(EXIT_FAILURE);
                } else if (pid > 0) {
                    wait(NULL);
                } else {
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                }
                break;
                
            case 0:
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
                
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    
    return 0;
}