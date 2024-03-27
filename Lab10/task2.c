#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_SEQUENCE 100

int fib_sequence[MAX_SEQUENCE];
int sequence_length;
void *generateFibonacci(void *arg) {
    int i;
    fib_sequence[0] = 0;
    fib_sequence[1] = 1;

    for (i = 2; i < sequence_length; i++) {
        fib_sequence[i] = fib_sequence[i - 1] + fib_sequence[i - 2];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t fib_thread;
    int i;

    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of Fibonacci numbers>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    
    sequence_length = atoi(argv[1]);

    
    if (sequence_length <= 0 || sequence_length > MAX_SEQUENCE) {
        fprintf(stderr, "Invalid input. Please provide a positive number up to %d\n", MAX_SEQUENCE);
        exit(EXIT_FAILURE);
    }

    
    if (pthread_create(&fib_thread, NULL, generateFibonacci, NULL) != 0) {
        perror("Error creating thread");
        exit(EXIT_FAILURE);
    }

    
    if (pthread_join(fib_thread, NULL) != 0) {
        perror("Error joining thread");
        exit(EXIT_FAILURE);
    }

    
    printf("Fibonacci Sequence:\n");
    for (i = 0; i < sequence_length; i++) {
        printf("%d ", fib_sequence[i]);
    }
    printf("\n");

    return 0;
}

