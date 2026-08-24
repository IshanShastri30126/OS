/**
 * Practical 4 - CPU Scheduling Algorithm: round_robin.c
 * 
 * Round Robin (RR) CPU Scheduling
 * Preemptive scheduling algorithm designed especially for time-sharing systems.
 * Allocates a fixed time quantum (slice) to each process in circular order.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    bool is_in_queue;
} Process;

int main(void) {
    int n, tq;
    printf("====================================================\n");
    printf("        Round Robin (RR) CPU Scheduler              \n");
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
        p[i].remaining_time = p[i].burst_time;
        p[i].start_time = -1;
        p[i].is_in_queue = false;
    }

    printf("\nEnter Time Quantum: ");
    if (scanf("%d", &tq) != 1 || tq <= 0) return 1;

    /* Ready queue implementation */
    int queue[1000];
    int front = 0, rear = 0;

    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    /* Find process that arrives earliest */
    int min_arrival = 1e9, first_idx = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time < min_arrival) {
            min_arrival = p[i].arrival_time;
            first_idx = i;
        }
    }

    current_time = min_arrival;
    queue[rear++] = first_idx;
    p[first_idx].is_in_queue = true;

    printf("\nExecution Sequence (Gantt progression):\n");

    while (completed < n) {
        if (front == rear) {
            /* Queue is empty, jump to next arriving process */
            int next_arr = 1e9, next_idx = -1;
            for (int i = 0; i < n; i++) {
                if (p[i].remaining_time > 0 && p[i].arrival_time < next_arr) {
                    next_arr = p[i].arrival_time;
                    next_idx = i;
                }
            }
            if (next_idx != -1) {
                current_time = next_arr;
                queue[rear++] = next_idx;
                p[next_idx].is_in_queue = true;
            }
        }

        int curr = queue[front++];
        p[curr].is_in_queue = false;

        if (p[curr].start_time == -1) {
            p[curr].start_time = current_time;
            p[curr].response_time = p[curr].start_time - p[curr].arrival_time;
            total_rt += p[curr].response_time;
        }

        int exec_time = (p[curr].remaining_time > tq) ? tq : p[curr].remaining_time;
        printf("  [Time %2d - %2d] Process P%d executed for %d units\n",
               current_time, current_time + exec_time, p[curr].pid, exec_time);

        p[curr].remaining_time -= exec_time;
        current_time += exec_time;

        /* Enqueue newly arrived processes during this time slice */
        for (int i = 0; i < n; i++) {
            if (i != curr && p[i].arrival_time <= current_time && p[i].remaining_time > 0 && !p[i].is_in_queue) {
                /* Check if already in queue */
                bool found = false;
                for (int k = front; k < rear; k++) {
                    if (queue[k] == i) { found = true; break; }
                }
                if (!found) {
                    queue[rear++] = i;
                    p[i].is_in_queue = true;
                }
            }
        }

        /* If current process still has remaining time, push back to queue */
        if (p[curr].remaining_time > 0) {
            queue[rear++] = curr;
            p[curr].is_in_queue = true;
        } else {
            p[curr].completion_time = current_time;
            p[curr].turnaround_time = p[curr].completion_time - p[curr].arrival_time;
            p[curr].waiting_time = p[curr].turnaround_time - p[curr].burst_time;

            total_wt += p[curr].waiting_time;
            total_tat += p[curr].turnaround_time;
            completed++;
        }
    }

    /* Results Table */
    printf("\n------------------------------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tFinish\tWaiting\tTurnaround\tResponse\n");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].waiting_time,
               p[i].turnaround_time, p[i].response_time);
    }
    printf("------------------------------------------------------------------------------------\n");
    printf("Average Waiting Time    : %.2f\n", total_wt / n);
    printf("Average Turnaround Time : %.2f\n", total_tat / n);
    printf("Average Response Time   : %.2f\n", total_rt / n);
    printf("Throughput              : %.4f processes/unit time\n", (float)n / current_time);
    printf("====================================================\n");

    return 0;
}
