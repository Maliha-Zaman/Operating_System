#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 5
#define MAX_SIZE 1000

void nonPreemptiveSJF(int n, int arrival_times[], int burst_times[], int start_times[], int finish_times[], int arrived[], int visited[], int current_process[]) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst_times[i];
    }

    int current_time = 0;
    int process_pointer = 0;
    while (current_time < total_time) {
        for (int i = 0; i < n; i++) {
            if (arrival_times[i] <= current_time && !arrived[i]) {
                arrived[i] = 1;
            }
        }

        int min_burst = INT_MAX;
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (arrived[i] && !visited[i] && burst_times[i] < min_burst) {
                min_burst = burst_times[i];
                min_index = i;
            }
        }

        if (min_index != -1) {
            current_process[process_pointer] = min_index + 1;
            process_pointer++;
            start_times[min_index] = current_time;
            current_time += burst_times[min_index];
            finish_times[min_index] = current_time;
            visited[min_index] = 1;
        } else {
            break;
        }
    }
}

void printProcessQueue(int n, int current_process[]) {
    int i;
    for (i = 0;; i++) {
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

    printf("Average Waiting Time: %.2lf\n", (double)waiting_times / n);
    printf("Average Response Time: %.2lf\n", (double)response_times / n);
}

int main() {
    int arrival_times[N] = {3, 0, 1, 4, 5};
    int burst_times[N] = {10, 1, 2, 7, 5};
    int start_times[N], finish_times[N];
    int arrived[N], visited[N];
    int current_process[MAX_SIZE];

    for (int i = 0; i < N; i++) {
        start_times[i] = -1;
        finish_times[i] = 0;
        arrived[i] = 0;
        visited[i] = 0;
        current_process[i] = 0;
    }

    memset(current_process, -1, sizeof(current_process));
    nonPreemptiveSJF(N, arrival_times, burst_times, start_times, finish_times, arrived, visited, current_process);

    printf("Non-Preemptive SJF:\n");
    printProcessQueue(N, current_process);
    printProcessDetails(N, arrival_times, burst_times, start_times, finish_times);

    return 0;
}
