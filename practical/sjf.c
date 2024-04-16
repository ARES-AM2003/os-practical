#include<stdio.h>

// Structure to represent a process
struct Process {
    int pid; // Process ID
    int burst_time; // Burst time
    int arrival_time; // Arrival time
};

// Function to perform SJF scheduling
void SJF(struct Process proc[], int n) {
    // Sorting the processes based on burst time using Bubble Sort
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (proc[j].burst_time > proc[j+1].burst_time) {
                // Swapping
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }

    // Array to store completion time of each process
    int completion_time[n];
    completion_time[0] = proc[0].burst_time;

    // Calculating completion time of each process
    for (int i = 1; i < n; i++) {
        completion_time[i] = completion_time[i-1] + proc[i].burst_time;
    }

    // Array to store waiting time of each process
    int waiting_time[n];
    waiting_time[0] = 0;

    // Calculating waiting time of each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = completion_time[i-1] - proc[i].arrival_time;
    }

    // Printing the order of execution
    printf("Order of execution: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", proc[i].pid);
    }
    printf("\n");

    // Printing waiting time and turnaround time for each process
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, waiting_time[i], completion_time[i] - proc[i].arrival_time);
    }

    // Calculating average waiting time and average turnaround time
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += completion_time[i] - proc[i].arrival_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Array to store processes
    struct Process proc[n];

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i+1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process P%d: ", i+1);
        scanf("%d", &proc[i].burst_time);
        proc[i].pid = i + 1;
    }

    // Perform SJF scheduling
    SJF(proc, n);

    return 0;
}
