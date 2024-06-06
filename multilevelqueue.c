#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int type;  // 1 for higher priority, 2 for lower priority
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void sort_by_arrival_and_priority(Process processes[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time ||
                (processes[i].arrival_time == processes[j].arrival_time && processes[i].type > processes[j].type)) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void calculate_times(Process processes[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        current_time = processes[i].completion_time;
    }
}

void print_and_calculate_averages(Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    printf("PID\tType\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].type, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time/n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time/n);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter PID, Type (1/2), Arrival Time, Burst Time for process %d: ", i+1);
        scanf("%d %d %d %d", &processes[i].pid, &processes[i].type, &processes[i].arrival_time, &processes[i].burst_time);
    }

    sort_by_arrival_and_priority(processes, n);

    calculate_times(processes, n);

    printf("\nAll Processes Scheduling:\n");
    print_and_calculate_averages(processes, n);

    return 0;
}

