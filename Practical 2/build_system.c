/**
 * Practical 2 - Real-World Scenario: build_system.c
 * 
 * Scenario:
 * A build automation tool (similar to 'make') that compiles multiple source files
 * concurrently using fork() and execvp(), waits for all jobs using waitpid(),
 * inspects their exit codes, and only proceeds to the linking step if all
 * compilations succeed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define NUM_JOBS 3

int main(void) {
    pid_t pids[NUM_JOBS];
    int build_failed = 0;

    /* Define compilation task commands */
    char *tasks[NUM_JOBS][4] = {
        {"echo", "[Task 1] Compiling module_auth.c ... Done.", NULL},
        {"echo", "[Task 2] Compiling module_database.c ... Done.", NULL},
        {"echo", "[Task 3] Compiling module_network.c ... Done.", NULL}
    };

    printf("====================================================\n");
    printf("        Build Automation Coordinator Simulator      \n");
    printf("====================================================\n");
    printf("Coordinator Parent PID = %d\n\n", getpid());

    /* Step 1: Fork child processes to run compilation tasks concurrently */
    for (int i = 0; i < NUM_JOBS; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Error: fork() failed for Task %d: %s\n", i + 1, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            /* Child Process: Run the compilation command */
            printf("[Worker %d Spawned] PID = %d, Parent PPID = %d\n", i + 1, getpid(), getppid());
            execvp(tasks[i][0], tasks[i]);

            /* If execvp fails */
            fprintf(stderr, "execvp() failed for Task %d: %s\n", i + 1, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else {
            /* Parent Process: Track child PID */
            pids[i] = pid;
        }
    }

    /* Step 2: Synchronize and wait for each child process */
    printf("\n[Coordinator] Waiting for all worker compilation tasks to finish...\n");

    for (int i = 0; i < NUM_JOBS; i++) {
        int status;
        pid_t finished_pid = waitpid(pids[i], &status, 0);

        if (finished_pid == -1) {
            fprintf(stderr, "waitpid() failed for PID %d: %s\n", pids[i], strerror(errno));
            build_failed = 1;
            continue;
        }

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("[Worker Finished] PID %d completed with exit code %d\n", finished_pid, exit_code);
            if (exit_code != 0) {
                build_failed = 1;
            }
        } else if (WIFSIGNALED(status)) {
            printf("[Worker Aborted] PID %d terminated by signal %d\n", finished_pid, WTERMSIG(status));
            build_failed = 1;
        }
    }

    /* Step 3: Conditional Linking Step */
    printf("\n====================================================\n");
    if (!build_failed) {
        printf("[Linking Step] All compilation modules completed successfully.\n");
        printf("[Linking Step] Linking objects into final binary 'app_release'...\n");
        printf("[Result] Build SUCCEEDED!\n");
    } else {
        printf("[Result] Build FAILED! One or more compilation tasks failed.\n");
    }
    printf("====================================================\n");

    return build_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
