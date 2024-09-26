#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i, j, numChild;
    
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            if (i % 2 == 0) {
                numChild = 4;
            } else {
                numChild = 5;
            }

            for (int j = 0; j < numChild; j++) {
                pid = fork();
                if (pid == 0) {
                    printf("I am sub-child %d of child %d\n", j, i);
                    exit(0);
                }
            }
            while(wait(NULL) != -1);
            printf("I am child %d\n",i); 
            exit(0);
        }
    }
    while(wait(NULL) != -1);
    printf("I am parent\n");    
    return 0;
}