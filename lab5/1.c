#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

// Process Structure
struct process {
    int pid;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    int n, quantum, time = 0, total_waiting_time = 0, total_turnaround_time = 0;
    int lowest_arrival_time = 1e9, start_time = 0;
    struct process processes[MAX_PROCESSES];

    // Input: Number of Processes, Time Quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Input: Process ID, Arrival Time, Burst Time
    for (int i = 0; i < n; i++) {
        printf("Process ID: ");
        scanf("%d", &processes[i].pid);
        printf("Enter the arrival time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        if (processes[i].arrival_time < lowest_arrival_time) {
            lowest_arrival_time = processes[i].arrival_time;
        }
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    start_time = lowest_arrival_time;
    time = lowest_arrival_time;
    int completed = 0;

    printf("Gantt chart:\n");
    
    // Round Robin
    while (completed < n) {

        for (int i = 0; i < n; i++) {
            // Check if any process has arrived
            if (processes[i].arrival_time > time) {
                continue;
            }
            // Check if process has remaining time
            if (processes[i].remaining_time > 0) {

                // If remaining time is greater than quantum, run for quantum time
                // Else run for remaining time and Set Time, Remaining Time, Waiting Time, Turnaround Time, Completed
                if (processes[i].remaining_time > quantum) {
                    printf("%d P%d ", time, processes[i].pid);
                    start_time = time;
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    printf("%d P%d ", time, processes[i].pid);
                    start_time = time;
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].waiting_time = time - processes[i].burst_time - processes[i].arrival_time;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    total_waiting_time += processes[i].waiting_time;
                    total_turnaround_time += processes[i].turnaround_time;
                    completed++;
                }
            }
        }
    }

    // Output: PID, Arrival Time, Burst Time, Turnaround Time, Waiting Time
    printf("%d \n", time);
    printf("PID\tAT\tBT\tTT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Output: Average Turnaround Time, Average Waiting Time
    printf("Average turnaround time: %.2f\n", (float)total_turnaround_time/n);
    printf("Average waiting time: %.2f\n", (float)total_waiting_time/n);
    return 0;
}