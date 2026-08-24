/**
 * Practical 4 - CPU Scheduling Algorithm: sjf.c
 * 
 * Shortest Job First (SJF) CPU Scheduling
 * Supports:
 * 1. Non-Preemptive SJF
 * 2. Preemptive SJF (Shortest Remaining Time First - SRTF)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int start_time;
    bool is_completed;
} Process;

void run_non_preemptive_sjf(Process p[], int n) {
    int completed = 0, current_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        p[i].is_completed = false;
    }

    printf("\n--- Non-Preemptive SJF Execution ---\n");

    while (completed < n) {
        int idx = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                } else if (p[i].burst_time == min_burst) {
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

    printf("\nPID\tArrival\tBurst\tFinish\tWaiting\tTurnaround\tResponse\n");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].waiting_time,
               p[i].turnaround_time, p[i].response_time);
    }
    printf("----------------------------------------------------------------------\n");
    printf("Average Waiting Time    : %.2f\n", total_wt / n);
    printf("Average Turnaround Time : %.2f\n", total_tat / n);
    printf("Average Response Time   : %.2f\n", total_rt / n);
}

void run_preemptive_srtf(Process p[], int n) {
    int completed = 0, current_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
        p[i].is_completed = false;
        p[i].start_time = -1;
    }

    printf("\n--- Preemptive SJF (SRTF) Execution ---\n");

    while (completed < n) {
        int idx = -1;
        int min_rem = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed) {
                if (p[i].remaining_time < min_rem && p[i].remaining_time > 0) {
                    min_rem = p[i].remaining_time;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].start_time == -1) {
                p[idx].start_time = current_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
                total_rt += p[idx].response_time;
            }

            p[idx].remaining_time--;
            current_time++;

            if (p[idx].remaining_time == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

                total_wt += p[idx].waiting_time;
                total_tat += p[idx].turnaround_time;

                p[idx].is_completed = true;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    printf("\nPID\tArrival\tBurst\tFinish\tWaiting\tTurnaround\tResponse\n");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].waiting_time,
               p[i].turnaround_time, p[i].response_time);
    }
    printf("----------------------------------------------------------------------\n");
    printf("Average Waiting Time    : %.2f\n", total_wt / n);
    printf("Average Turnaround Time : %.2f\n", total_tat / n);
    printf("Average Response Time   : %.2f\n", total_rt / n);
}

int main(void) {
    int n, choice;
    printf("====================================================\n");
    printf("        Shortest Job First (SJF) Scheduler          \n");
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
    }

    printf("\nSelect SJF Mode:\n");
    printf("1. Non-Preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        run_non_preemptive_sjf(p, n);
    } else {
        run_preemptive_srtf(p, n);
    }

    return 0;
}
