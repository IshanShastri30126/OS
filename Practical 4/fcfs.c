/**
 * Practical 4 - CPU Scheduling Algorithm: fcfs.c
 * 
 * First-Come, First-Served (FCFS) CPU Scheduling
 * Non-preemptive scheduling policy where the process that requests the CPU first
 * is allocated the CPU first.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
} Process;

void sort_by_arrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    int n;
    printf("====================================================\n");
    printf("     First-Come First-Served (FCFS) Scheduler       \n");
    printf("====================================================\n");
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess P%d:\n", p[i].pid);
        printf("  Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("  Burst Time  : ");
        scanf("%d", &p[i].burst_time);
    }

    /* Sort processes by arrival time */
    sort_by_arrival(p, n);

    int current_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }
        p[i].start_time = current_time;
        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        current_time = p[i].completion_time;

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }

    /* Display Table */
    printf("\n------------------------------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\tResponse\n");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].start_time, p[i].completion_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }
    printf("------------------------------------------------------------------------------------\n");

    /* Gantt Chart */
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("|  P%d  ", p[i].pid);
    }
    printf("|\n0");
    for (int i = 0; i < n; i++) {
        printf("      %2d", p[i].completion_time);
    }
    printf("\n\n");

    /* Summary Metrics */
    printf("Average Waiting Time    : %.2f\n", total_wt / n);
    printf("Average Turnaround Time : %.2f\n", total_tat / n);
    printf("Average Response Time   : %.2f\n", total_rt / n);
    printf("Throughput              : %.4f processes/unit time\n", (float)n / current_time);
    printf("====================================================\n");

    return 0;
}
