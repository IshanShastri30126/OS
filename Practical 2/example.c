/**
 * Practical 2 - Program 2: example.c
 * 
 * Demonstrates:
 * Process replacement using execv(). Notice that the code following a successful
 * execv() call is never executed because the address space is completely replaced.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("[example.c] Process Started. PID = %d\n", getpid());
    printf("[example.c] Preparing to execute './p1' via execv()...\n");

    /* Argument list must be null-terminated */
    char *args[] = {"./p1", "hello", "C", "Programming", NULL};

    /* Execute the binary ./p1 */
    execv("./p1", args);

    /* If execv() returns, an error occurred */
    perror("[example.c] execv() execution failed");
    printf("[example.c] Back to example.c (only reached if execv fails)\n");

    return EXIT_FAILURE;
}
