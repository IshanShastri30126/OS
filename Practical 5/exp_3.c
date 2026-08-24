/**
 * Practical 5 - Experiment 3: exp_3.c (Thread Scaling)
 * 
 * Objective:
 * Execute with user-defined thread count (e.g., 2, 4, 8, 16 threads) and analyze
 * scalability, thread overhead, and CPU concurrency.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *worker(void *arg) {
    int id = *(int *)arg;
    printf("  [Thread %2d] Started\n", id);
    sleep(1); /* Simulate background work */
    printf("  [Thread %2d] Completed\n", id);
    return NULL;
}

int main(void) {
    int n;
    printf("====================================================\n");
    printf("        POSIX Thread Scalability Experiment         \n");
    printf("====================================================\n");
    printf("Enter number of threads to spawn (e.g., 2, 4, 8, 16): ");
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of threads.\n");
        return EXIT_FAILURE;
    }

    pthread_t *tid = malloc(n * sizeof(pthread_t));
    int *ids = malloc(n * sizeof(int));

    if (!tid || !ids) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    printf("\nLaunching %d threads concurrently...\n", n);
    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        if (pthread_create(&tid[i], NULL, worker, &ids[i]) != 0) {
            perror("pthread_create failed");
            return EXIT_FAILURE;
        }
    }

    /* Wait for all spawned threads */
    for (int i = 0; i < n; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("\nAll %d threads completed successfully.\n", n);
    printf("====================================================\n");

    free(tid);
    free(ids);
    return EXIT_SUCCESS;
}
