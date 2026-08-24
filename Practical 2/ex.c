/**
 * Practical 2 - Program 3: ex.c
 * 
 * Demonstrates:
 * Process replacement with an external system binary (/bin/ls) using execv().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("[ex.c] PID = %d\n", getpid());
    printf("[ex.c] Replacing process image with '/bin/ls -l'...\n\n");

    /* Argument vector for ls -l */
    char *args[] = {"ls", "-l", NULL};

    /* Execute /bin/ls */
    execv("/bin/ls", args);

    /* Executed only if execv fails */
    perror("[ex.c] Failed to execute /bin/ls");
    return EXIT_FAILURE;
}
