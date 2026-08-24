/**
 * Practical 5 - Experiment 1: exp_1.c (Performance Comparison)
 * 
 * Objective:
 * Compare execution time of sequential execution versus multithreaded execution.
 * 
 * Explanation:
 * Sequential execution completes tasks one after another (Total Time ≈ N * Task_Duration).
 * Multithreaded execution runs tasks concurrently across CPU cores (Total Time ≈ Task_Duration).
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NUM_TASKS 4

void *task(void *arg) {
    sleep(1); /* Simulate 1 second of computation/IO work */
    return NULL;
}

double get_wall_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

int main(void) {
    double start_time, end_time;

    printf("====================================================\n");
    printf("   Sequential vs Multithreaded Execution Benchmark  \n");
    printf("   (Workload: %d tasks, each taking 1 second)       \n", NUM_TASKS);
    printf("====================================================\n\n");

    /* 1. Sequential Execution */
    printf("[1] Starting Sequential Execution...\n");
    start_time = get_wall_time();
    for (int i = 0; i < NUM_TASKS; i++) {
        sleep(1);
    }
    end_time = get_wall_time();
    double seq_time = end_time - start_time;
    printf("    Sequential Execution Time  : %.3f seconds\n\n", seq_time);

    /* 2. Multithreaded Execution */
    printf("[2] Starting Multithreaded Execution (%d concurrent threads)...\n", NUM_TASKS);
    pthread_t tid[NUM_TASKS];
    start_time = get_wall_time();

    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_create(&tid[i], NULL, task, NULL);
    }

    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_join(tid[i], NULL);
    }

    end_time = get_wall_time();
    double mt_time = end_time - start_time;
    printf("    Multithreaded Execution Time: %.3f seconds\n\n", mt_time);

    /* Comparison */
    printf("====================================================\n");
    printf("Speedup Factor: %.2fx faster with multithreading\n", seq_time / mt_time);
    printf("====================================================\n");

    return EXIT_SUCCESS;
}
