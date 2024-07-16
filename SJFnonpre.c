#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char process_name;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void sort_by_burst_time(Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
void compute_completion_time(Process *processes, int n) {
    int current_time = 0;
    int index = 0;
    while (index < n) {
        int next_process = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
                if (next_process == -1 || processes[i].burst_time < processes[next_process].burst_time) {
                    next_process = i;
                }
            }
        }
        if (next_process == -1) {
              current_time = processes[index].arrival_time;
        } else {
            processes[next_process].completion_time = current_time + processes[next_process].burst_time;
            current_time = processes[next_process].completion_time;
        }
        index++;
    }
}
void compute_turnaround_waiting_time(Process *processes, int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}
void display_table(Process *processes, int n) {
    printf("Process   Arrival Time   Burst Time   Completion Time   Turnaround Time   Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("  %c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_name,
                                                            processes[i].arrival_time,
                                                            processes[i].burst_time,
                                                            processes[i].completion_time,
                                                            processes[i].turnaround_time,
                                                            processes[i].waiting_time);
    }
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process *processes = (Process *)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d (Name Arrival Burst): ", i + 1);
        scanf(" %c %d %d", &processes[i].process_name, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }
     sort_by_burst_time(processes, n);
     compute_completion_time(processes, n);
    compute_turnaround_waiting_time(processes, n);
    display_table(processes, n);
    free(processes);
    return 0;
}
