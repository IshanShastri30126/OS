/**
 * Practical 2 - Target Binary: p1.c (or hello.c)
 * 
 * Objective:
 * A simple standalone C program called by execv() in example.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("[p1.c Executing] Hello from replaced process!\n");
    printf("[p1.c Executing] Current Process PID = %d, Parent PPID = %d\n", getpid(), getppid());
    
    if (argc > 1) {
        printf("[p1.c Executing] Received Arguments:\n");
        for (int i = 0; i < argc; i++) {
            printf("    argv[%d] = %s\n", i, argv[i]);
        }
    }
    
    return EXIT_SUCCESS;
}
