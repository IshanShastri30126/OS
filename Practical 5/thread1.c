/**
 * Practical 5 - Program 1: thread1.c
 * 
 * Demonstrates:
 * Shared memory between threads in POSIX Pthreads.
 * When a worker thread changes a global variable, the change is directly visible
 * to the main thread since both share the same address space.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Global variable shared by all threads */
int x = 10;

void *change_value(void *arg) {
    printf("[Worker Thread] Current x = %d. Modifying x to 20...\n", x);
    x = 20;
    printf("[Worker Thread] Modified x = %d\n", x);
    return NULL;
}

int main(void) {
    pthread_t tid;

    printf("[Main Thread] Initial x = %d\n", x);
    
    /* Create worker thread */
    if (pthread_create(&tid, NULL, change_value, NULL) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    /* Wait for worker thread to complete */
    pthread_join(tid, NULL);

    printf("[Main Thread] Value of x after thread completion = %d\n", x);
    printf("[Inference] The thread updated the shared memory directly.\n");

    return EXIT_SUCCESS;
}
