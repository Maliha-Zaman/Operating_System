#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_M 100
#define MAX_K 100
#define MAX_N 100


int matrixA[MAX_M][MAX_K];
int matrixB[MAX_K][MAX_N];
int matrixC[MAX_M][MAX_N];


typedef struct {
    int row;
    int col;
    int k_value;
} ThreadData;


void *matrixMultiply(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    int i = data->row;
    int j = data->col;
    int k;

    matrixC[i][j] = 0;
    for (k = 0; k < data->k_value; k++) {
        matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
    }

    pthread_exit(NULL);
}

int main() {
    int M, K, N;

   
    printf("Enter the number of rows (M) for matrix A: ");
    scanf("%d", &M);

    printf("Enter the number of columns (K) for matrix A: ");
    scanf("%d", &K);

    printf("Enter the number of columns (N) for matrix B: ");
    scanf("%d", &N);

    if (M <= 0 || K <= 0 || N <= 0 || M > MAX_M || K > MAX_K || N > MAX_N) {
        fprintf(stderr, "Invalid matrix dimensions.\n");
        exit(EXIT_FAILURE);
    }

    
    printf("Enter elements for matrix A (%d x %d):\n", M, K);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &matrixA[i][j]);
        }
    }

    printf("Enter elements for matrix B (%d x %d):\n", K, N);
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &matrixB[i][j]);
        }
    }

    
    pthread_t threads[M][N];
    ThreadData thread_data[M][N];

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            thread_data[i][j].row = i;
            thread_data[i][j].col = j;
            thread_data[i][j].k_value = K;

            if (pthread_create(&threads[i][j], NULL, matrixMultiply, (void *)&thread_data[i][j]) != 0) {
                fprintf(stderr, "Error creating thread.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (pthread_join(threads[i][j], NULL) != 0) {
                fprintf(stderr, "Error joining thread.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    
    printf("Resulting Matrix C:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }

    return 0;
}

