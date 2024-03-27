#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 5
#define MAX_SIZE 1000

void initializeArrays(int n, int start_times[], int finish_times[], int has_arrived[], int current_processes[], int remaining_burst[]) {
    for (int i = 0; i < n; i++) {
        start_times[i] = -1;
        finish_times[i] = 0;
        has_arrived[i] = 0;
        current_processes[i] = 0;
        remaining_burst[i] = INT_MAX;
    }
}

void updateArrivalStatus(int n, int current_time, int arrival_times[], int has_arrived[], int remaining_burst[], int burst_times[]) {
    for (int j = 0; j < n; j++) {
        if (arrival_times[j] <= current_time && !has_arrived[j]) {
            has_arrived[j] = 1;
            remaining_burst[j] = burst_times[j];
        }
    }
}

int findMinRemainingTime(int n, int remaining_burst[]) {
    int min_remaining_time = INT_MAX;
    int min_index = -1;
    for (int j = 0; j < n; j++) {
        if (remaining_burst[j] < min_remaining_time && remaining_burst[j] > 0) {
            min_remaining_time = remaining_burst[j];
            min_index = j;
        }
    }
    return min_index;
}

void sjfPreemptive(int n, int arrival_times[], int burst_times[], int start_times[], int finish_times[], int has_arrived[], int current_processes[], int remaining_burst[]) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst_times[i];
    }
    int queue_pointer = 0;

    for (int current_time = 0; current_time < total_time; current_time++) {
        updateArrivalStatus(n, current_time, arrival_times, has_arrived, remaining_burst, burst_times);

        int min_index = findMinRemainingTime(n, remaining_burst);

        if (min_index != -1) {
            if (start_times[min_index] == -1) {
                start_times[min_index] = current_time;
            }
            remaining_burst[min_index]--;
            if (remaining_burst[min_index] == 0) {
                finish_times[min_index] = current_time + 1;
            }

            if (current_processes[queue_pointer] != min_index + 1) {
                current_processes[queue_pointer + 1] = min_index + 1;
                queue_pointer++;
            } else {
                current_processes[queue_pointer] = min_index + 1;
            }
        } else {
            break;
        }
    }
}

void printProcessQueue(int n, int current_processes[]) {
    int i;
    for (i = 1;; i++) {
        if (current_processes[i + 1] == -1) {
            break;
        }
        printf("P%d->", current_processes[i]);
    }
    printf("P%d\n", current_processes[i]);
}

void printProcessDetails(int n, int arrival_times[], int burst_times[], int start_times[], int finish_times[]) {
    int waiting_times = 0;
    int response_times = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d:\n", i + 1);
        printf("Start Time: %d\n", start_times[i]);
        printf("Finish Time: %d\n", finish_times[i]);
        printf("Waiting Time: %d\n", finish_times[i] - arrival_times[i] - burst_times[i]);
        printf("Response Time: %d\n", start_times[i] - arrival_times[i]);

        waiting_times += finish_times[i] - arrival_times[i] - burst_times[i];
        response_times += start_times[i] - arrival_times[i];
    }

    printf("Average Waiting Time: %.2lf\n", (double)waiting_times / N);
    printf("Average Response Time: %.2lf\n", (double)response_times / N);
}

void sjfPreemptiveSolve(int n, int arrival_times[], int burst_times[]) {
    int start_times[N], finish_times[N];
    int has_arrived[N], current_processes[MAX_SIZE];
    int remaining_burst[N];

    initializeArrays(n, start_times, finish_times, has_arrived, current_processes, remaining_burst);
    memset(current_processes, -1, sizeof(current_processes));

    sjfPreemptive(n, arrival_times, burst_times, start_times, finish_times, has_arrived, current_processes, remaining_burst);

    printProcessQueue(n, current_processes);
    printProcessDetails(n, arrival_times, burst_times, start_times, finish_times);
}

int main() {
    int arrival_times[N] = {3, 0, 1, 4, 5};
    int burst_times[N] = {10, 1, 2, 7, 5};

    printf("SJF Preemptive:\n");
    sjfPreemptiveSolve(N, arrival_times, burst_times);

    return 0;
}
