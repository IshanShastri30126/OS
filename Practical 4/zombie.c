/**
 * Practical 4 - Process State Experiment: zombie.c
 * 
 * Demonstrates:
 * Creation of a Zombie (defunct) process.
 * When a child process terminates, its entry remains in the process table
 * until its parent reads its exit status with wait().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork() failed");
        return EXIT_FAILURE;
    }
    else if (pid == 0) {
        /* Child process terminates immediately */
        printf("[Child Process]  PID = %d, PPID = %d. Exiting now...\n", getpid(), getppid());
        exit(0);
    }
    else {
        /* Parent process sleeps without calling wait() */
        printf("[Parent Process] PID = %d. Created Child PID = %d.\n", getpid(), pid);
        printf("[Parent Process] Sleeping for 30 seconds without calling wait()...\n");
        printf("[Parent Process] Child %d is now in ZOMBIE (defunct) state.\n", pid);
        printf("[Parent Process] Check in another terminal: ps aux | grep 'Z'\n");

        sleep(30);

        printf("[Parent Process] Parent waking up and exiting.\n");
    }

    return EXIT_SUCCESS;
}
