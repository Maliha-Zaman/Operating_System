#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main(int argc, char *argv[]) {

    int num = atoi(argv[1]);
    if (num < 0) {
        printf("Error: Please provide a non-negative integer.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        
        printf("Child Process Fibonacci Sequence: ");
        for (int i = 0; i < num; ++i) {
            printf("%d ", fibonacci(i));
        }
        printf("\n");
    } else {
        
        wait(NULL); 
        printf("Parent Process: Child process completed.\n");
    }

    return 0;
}

