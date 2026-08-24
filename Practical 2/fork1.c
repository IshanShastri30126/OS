/**
 * Practical 2 - Program 1: fork1.c
 * 
 * Demonstrates:
 * Process creation using fork(), identifying parent and child processes via PID/PPID,
 * and synchronizing termination using wait().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        /* Error handling */
        perror("fork() failed");
        return EXIT_FAILURE;
    }
    else if (pid == 0) {
        /* Child Process */
        printf("[Child Process]  PID = %d, PPID = %d\n", getpid(), getppid());
        printf("[Child Process]  Work completed. Exiting.\n");
        exit(EXIT_SUCCESS);
    }
    else {
        /* Parent Process */
        printf("[Parent Process] PID = %d, Created Child PID = %d\n", getpid(), pid);
        printf("[Parent Process] Waiting for child process to finish...\n");
        
        wait(NULL); /* Wait for child process termination */
        
        printf("[Parent Process] Child process has finished. Exiting parent.\n");
    }

    return EXIT_SUCCESS;
}
