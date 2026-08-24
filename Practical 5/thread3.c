/**
 * Practical 5 - Program 3: thread3.c
 * 
 * Demonstrates:
 * Managing an array of threads using loops for creation and synchronization.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

void *display(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d is running.\n", id);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid[NUM_THREADS];
    int id[NUM_THREADS] = {1, 2, 3};

    /* Create threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&tid[i], NULL, display, &id[i]) != 0) {
            perror("Failed to create thread");
            return EXIT_FAILURE;
        }
    }

    /* Wait for threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("All threads completed.\n");
    return EXIT_SUCCESS;
}
