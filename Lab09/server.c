
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define ARRAY_SIZE 5

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int shmid;
    int *sharedData;

    
    shmid = shmget(SHM_KEY, sizeof(int) * ARRAY_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    sharedData = shmat(shmid, NULL, 0);
    if (sharedData == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

   
    printf("Enter %d integer values:\n", ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        scanf("%d", &sharedData[i]);
    }

   
    bubbleSort(sharedData, ARRAY_SIZE);

   
    printf("Sorted array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", sharedData[i]);
    }
    printf("\n");

   
    shmdt(sharedData);


    return 0;
}

