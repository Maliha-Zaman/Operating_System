#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 5
#define MAX_SIZE 1000

void preemptivePriority(int n, int arrival_times[], int burst_times[], int start_times[], int finish_times[], int priority[], int arrived[], int current_process[], int remaining_time[]) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst_times[i];
    }
    int queue_pointer = 0;
    for (int current_time = 0; current_time <= total_time; current_time++) {
        for (int j = 0; j < n; j++) {
            if (arrival_times[j] <= current_time && !arrived[j]) {
                arrived[j] = 1;
                remaining_time[j] = burst_times[j];
            }
        }
        int max_priority = -1;
        int max_index = -1;
        for (int i = 0; i < n; i++) {
            if (arrived[i] && priority[i] > max_priority) {
                max_priority = priority[i];
                max_index = i;
            }
        }

        if (max_index != -1) {
            if (start_times[max_index] == -1) {
                start_times[max_index] = current_time;
            }
            remaining_time[max_index]--;
            if (remaining_time[max_index] == 0) {
                finish_times[max_index] = current_time + 1;
                priority[max_index] = -1;
            }
            if (current_process[queue_pointer] != max_index + 1) {
                current_process[queue_pointer + 1] = max_index + 1;
                queue_pointer++;
            } else {
                current_process[queue_pointer] = max_index + 1;
            }
        } else {
            break;
        }
    }
}

void printProcessQueue(int n, int current_process[]) {
    int i;
    for (i = 1;; i++) {
        if (current_process[i + 1] == -1) {
            break;
        }
        printf("P%d->", current_process[i]);
    }
    printf("P%d\n", current_process[i]);
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

    printf("Average Waiting Time: %lf\n", (double)waiting_times / n);
    printf("Average Response Time: %lf\n", (double)response_times / n);
}

int main() {
    int arrival_times[N] = {3, 0, 1, 4, 5};
    int burst_times[N] = {10, 1, 2, 7, 5};
    int start_times[N], finish_times[N];
    int priority[N] = {3, 1, 3, 4, 2};
    int arrived[N], current_process[MAX_SIZE];
    int remaining_time[N];

    for (int i = 0; i < N; i++) {
        start_times[i] = -1;
        finish_times[i] = 0;
        arrived[i] = 0;
        current_process[i] = 0;
        remaining_time[i] = INT_MAX;
    }

    memset(current_process, -1, sizeof(current_process));
    preemptivePriority(N, arrival_times, burst_times, start_times, finish_times, priority, arrived, current_process, remaining_time);

    printf("Preemptive Priority:\n");
    printProcessQueue(N, current_process);
    printProcessDetails(N, arrival_times, burst_times, start_times, finish_times);

    return 0;
}
