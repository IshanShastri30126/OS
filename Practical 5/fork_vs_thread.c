/**
 * Practical 5 - Memory Space Comparison (Process Isolation): fork_vs_thread.c
 * 
 * Demonstrates:
 * In process creation via fork(), parent and child have separate isolated memory
 * address spaces. Changing a variable in the child does NOT affect the parent.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int x = 10;
    printf("[Process Experiment] Initial x in main process = %d\n", x);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork() failed");
        return EXIT_FAILURE;
    }
    else if (pid == 0) {
        /* Child Process */
        x = 20;
        printf("[Child Process]  Modified x = %d (PID: %d)\n", x, getpid());
        exit(0);
    }
    else {
        /* Parent Process */
        wait(NULL); /* Wait for child to complete */
        printf("[Parent Process] Value of x after child exit = %d (PID: %d)\n", x, getpid());
        printf("[Inference] Parent's variable remained unchanged (Memory Isolation).\n");
    }

    return EXIT_SUCCESS;
}
