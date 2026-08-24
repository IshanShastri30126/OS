/**
 * Practical 4 - CPU Scheduling Algorithm: priority.c
 * 
 * Priority CPU Scheduling (Non-Preemptive & Preemptive)
 * (Assuming Lower Numerical Value = Higher Priority)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int start_time;
    bool is_completed;
} Process;

void run_non_preemptive_priority(Process p[], int n) {
    int completed = 0, current_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) p[i].is_completed = false;

    printf("\n--- Non-Preemptive Priority Execution ---\n");

    while (completed < n) {
        int idx = -1;
        int highest_pri = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed) {
                if (p[i].priority < highest_pri) {
                    highest_pri = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highest_pri) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = current_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_wt += p[idx].waiting_time;
            total_tat += p[idx].turnaround_time;
            total_rt += p[idx].response_time;

            p[idx].is_completed = true;
            completed++;
            current_time = p[idx].completion_time;
        } else {
            current_time++;
        }
    }

    printf("\nPID\tArrival\tBurst\tPriority\tFinish\tWaiting\tTurnaround\tResponse\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].completion_time, p[i].waiting_time,
               p[i].turnaround_time, p[i].response_time);
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("Average Waiting Time    : %.2f\n", total_wt / n);
    printf("Average Turnaround Time : %.2f\n", total_tat / n);
    printf("Average Response Time   : %.2f\n", total_rt / n);
}

int main(void) {
    int n;
    printf("====================================================\n");
    printf("            Priority CPU Scheduler                  \n");
    printf("====================================================\n");
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess P%d:\n", p[i].pid);
        printf("  Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("  Burst Time  : ");
        scanf("%d", &p[i].burst_time);
        printf("  Priority (lower number = higher priority): ");
        scanf("%d", &p[i].priority);
    }

    run_non_preemptive_priority(p, n);
    return 0;
}
