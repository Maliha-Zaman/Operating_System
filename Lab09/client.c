#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define ARRAY_SIZE 5

int binarySearch(int arr[], int low, int high, int searchKey) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        
        if (arr[mid] == searchKey)
            return mid;

        
        if (arr[mid] < searchKey)
            low = mid + 1;
        
        else
            high = mid - 1;
    }

    return -1; 
}

int main() {
    int shmid;
    int *sharedData;

    
    shmid = shmget(SHM_KEY, sizeof(int) * ARRAY_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    sharedData = shmat(shmid, NULL, 0);
    if (sharedData == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    
    printf("Sorted array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", sharedData[i]);
    }
    printf("\n");

    
    int searchKey;
    printf("Enter the value to search: ");
    scanf("%d", &searchKey);

    
    int resultIndex = binarySearch(sharedData, 0, ARRAY_SIZE - 1, searchKey);

    if (resultIndex != -1) {
        printf("Value %d found at index %d in the sorted array.\n", searchKey, resultIndex);
    } else {
        printf("Value %d not found in the sorted array.\n", searchKey);
    }

    
    shmdt(sharedData);

    return 0;
}

