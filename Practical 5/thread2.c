/**
 * Practical 5 - Program 2: thread2.c
 * 
 * Demonstrates:
 * Concurrent multithreaded execution. Two worker threads execute a loop
 * concurrently, printing their IDs and iteration numbers with interleaved execution.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *worker(void *arg) {
    int id = *(int *)arg;
    for (int i = 1; i <= 5; i++) {
        printf("Thread %d : %d\n", id, i);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t t1, t2;
    int a = 1;
    int b = 2;

    printf("[Main Thread] Creating Thread 1 and Thread 2...\n");

    pthread_create(&t1, NULL, worker, &a);
    pthread_create(&t2, NULL, worker, &b);

    /* Wait for both threads to finish */
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("[Main Thread] Both worker threads have finished.\n");
    return EXIT_SUCCESS;
}
