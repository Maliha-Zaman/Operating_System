#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 5
#define MAX_SIZE 1000

int arrival[N] = {3, 0, 1, 4, 5};
int burst[N] = {10, 1, 2, 7, 5};
int start[N], finish[N];
int arrived[N], visited[N];
int current_process[MAX_SIZE];
int remaining_time[N];
const int quantum = 4;

int minimum(int num1, int num2) {
    return (num1 < num2) ? num1 : num2;
}

void initializeArrays(int n) {
    for (int i = 0; i < n; i++) {
        start[i] = -1;
        finish[i] = 0;
        arrived[i] = 0;
        visited[i] = 0;
        current_process[i] = 0;
        remaining_time[i] = INT_MAX;
    }

    memset(current_process, -1, sizeof(current_process));
}

void performRoundRobin(int n) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst[i];
    }

    int current_time = 0, process_pointer = 0;
    int current_process_ix = 0;
    while (current_time < total_time) {
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= current_time && !arrived[i]) {
                arrived[i] = 1;
                remaining_time[i] = burst[i];
            }
        }
        int i;
        for (i = 0; i < n; i++) {
            if (arrived[i] && !visited[i] && remaining_time[i] > 0) {
                if (i != n - 1) {
                    visited[i] = 1;
                } else {
                    memset(visited, 0, sizeof(visited));
                }
                current_process[process_pointer] = i + 1;
                process_pointer++;
                if (start[i] == -1) {
                    start[i] = current_time;
                }
                current_time += minimum(remaining_time[i], quantum);
                remaining_time[i] -= minimum(remaining_time[i], quantum);
                if (remaining_time[i] == 0) {
                    finish[i] = current_time;
                }
                break;
            }
        }
        if (i == n) {
            break;
        }
    }
}

void printResults(int n) {
    int i;
    for (i = 0;; i++) {
        if (current_process[i + 1] == -1) {
            break;
        }
        printf("P%d->", current_process[i]);
    }
    printf("P%d\n", current_process[i]);

    int waiting_times = 0;
    int response_times = 0;

    for (int i = 0; i < N; i++) {
        printf("P%d:\n", i + 1);
        printf("Start Time: %d\n", start[i]);
        printf("Finish Time: %d\n", finish[i]);
        printf("Waiting Time: %d\n", finish[i] - arrival[i] - burst[i]);
        printf("Response Time: %d\n", start[i] - arrival[i]);

        waiting_times += finish[i] - arrival[i] - burst[i];
        response_times += start[i] - arrival[i];
    }

    printf("Average Waiting Time: %lf\n", (double)waiting_times / N);
    printf("Average Response Time: %lf\n", (double)response_times / N);
}

int main() {
    initializeArrays(N);
    performRoundRobin(N);
    printResults(N);

    printf("\n\n");
    return 0;
}
