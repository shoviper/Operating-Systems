#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void child_process(int num1, int num2) {
    int sum = num1 + num2;
    printf("Child process: Sum of %d and %d is %d\n", num1, num2, sum);
    exit(sum);
}

void parent_process(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <num1> <num2> <num3> <num4>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int num3 = atoi(argv[3]);
    int num4 = atoi(argv[4]);

    pid_t pid1, pid2;
    int status1, status2;
    int result1, result2;

    pid1 = fork();
    if (pid1 == 0) {
        
        child_process(num1, num2);
    } else if (pid1 < 0) {
        perror("fork child 1 failed");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == 0) {
        
        child_process(num3, num4);
    } else if (pid2 < 0) {
        perror("fork child 2 failed");
        exit(EXIT_FAILURE);
    }

    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    if (WIFEXITED(status1)) {
        result1 = WEXITSTATUS(status1);
        printf("Child 1 exited with status %d\n", result1);
    } else {
        fprintf(stderr, "Child 1 did not exit normally\n");
    }

    if (WIFEXITED(status2)) {
        result2 = WEXITSTATUS(status2);
        printf("Child 2 exited with status %d\n", result2);
    } else {
        fprintf(stderr, "Child 2 did not exit normally\n");
    }

    int total_sum = result1 + result2;
    printf("Total sum of results from both children: %d\n", total_sum);
}

int main(int argc, char *argv[]) {
   
    if (argc == 3) {
        int num1 = atoi(argv[1]);
        int num2 = atoi(argv[2]);
        child_process(num1, num2);
    } else {
        parent_process(argc, argv);
    }

    return 0;
}