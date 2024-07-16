#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time; 
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int findShortestJob(struct Process processes[], int n, int current_time) {
    int shortest_job_index = -1;
    int shortest_job = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < shortest_job) {
            shortest_job_index = i;
            shortest_job = processes[i].remaining_time;
        }
    }
    return shortest_job_index;
}

void SJF(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    while (completed < n) {
        int shortest_job_index = findShortestJob(processes, n, current_time);
        if (shortest_job_index == -1) {
            current_time++; 
        } else {
           
            processes[shortest_job_index].remaining_time--;
            current_time++;
            if (processes[shortest_job_index].remaining_time == 0) {
                
                processes[shortest_job_index].completion_time = current_time;
                processes[shortest_job_index].turnaround_time = processes[shortest_job_index].completion_time - processes[shortest_job_index].arrival_time;
                processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
                completed++;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the total number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].pid = i + 1;
    }
    SJF(processes, n);
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    return 0;
}
