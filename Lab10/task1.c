#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int isPrime(int num) {
    if (num <= 1) {
        return 0; 
    }

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0; 
        }
    }

    return 1; 
}


void *outputPrimes(void *arg) {
    int limit = *(int *)arg;

    printf("Prime numbers up to %d: ", limit);

    for (int i = 2; i <= limit; ++i) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }

    printf("\n");

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <limit>\n", argv[0]);
        exit(1);
    }

    int limit = atoi(argv[1]);
    if (limit <= 1) {
        fprintf(stderr, "Please enter a positive integer greater than 1.\n");
        exit(1);
    }

    pthread_t primeThread;
    int threadArg = limit;

    
   int threadCreateResult = pthread_create(&primeThread, NULL, outputPrimes, &threadArg);

    if (threadCreateResult != 0) {
        fprintf(stderr, "Thread creation failed with error code %d\n", threadCreateResult);
        exit(1);
    } else {
        printf("Thread created successfully.\n");
    }

    
    if (pthread_join(primeThread, NULL) != 0) {
        perror("Thread join failed");
        exit(1);
    }

    return 0;
}

