#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

// Process Structure
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};


// Compare function for qsort based on arrival time
int compare_arrival_time(const void *a, const void *b) {
    struct process *p1 = (struct process*)a;
    struct process *p2 = (struct process*)b;
    return p1->arrival_time - p2->arrival_time;
};

int main() {
    int n, total_waiting_time = 0, total_turnaround_time = 0, time = 0, start_time = 1e9;
    int completed = 0, current_process = -1;
    struct process processes[MAX_PROCESSES];
    
    // Input: Number of Processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input: Process ID, Arrival Time, Burst Time
    for (int i = 0; i < n; i++) {
        printf("Process ID: ");
        scanf("%d", &processes[i].pid);
        printf("Enter the arrival time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        if (processes[i].arrival_time < start_time) {
            start_time = processes[i].arrival_time;
        }
    }
    time = start_time;
    
    // Sort processes based on arrival time
    qsort(processes, n, sizeof(struct process), compare_arrival_time);
    printf("Gantt chart:\n");

    // Shortest Remaining Time First
    while (completed < n) {

        int next_process = -1;
        int shortest_remaining_time = 1e9;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time < shortest_remaining_time && processes[i].remaining_time > 0) {
                shortest_remaining_time = processes[i].remaining_time;
                next_process = i;
            }
        }

        // If no process is found, increment time and continue
        if (next_process == -1) {
            time++;
            continue;
        }

        // If process is found, print it if it is different from the current process
        if (current_process != next_process) {
            printf("%d P%d ", time, processes[next_process].pid);
            current_process = next_process;
        }

        // Decrement remaining time and increment time
        processes[next_process].remaining_time--;
        time++;

        // If process is completed, set turnaround time, waiting time and increment completed
        if (processes[next_process].remaining_time == 0) {
            completed++;
            int turnaround_time = time - processes[next_process].arrival_time;
            int waiting_time = turnaround_time - processes[next_process].burst_time;
            total_turnaround_time += turnaround_time;
            total_waiting_time += waiting_time;
            processes[next_process].turnaround_time = turnaround_time;
            processes[next_process].waiting_time = waiting_time;
        }
    }
    printf("%d\n", time);

    // Output: PID, Arrival Time, Burst Time, Turnaround Time, Waiting Time
    printf("PID\tAT\tBT\tTT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Output: Average Turnaround Time, Average Waiting Time
    printf("Average turnaround time: %.2f\n", (float)total_turnaround_time/n);
    printf("Average waiting time: %.2f\n", (float)total_waiting_time/n);
    return 0;
}