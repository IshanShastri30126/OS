/**
 * Practical 1: Linux System Calls and Kernel Interface Exploration
 * 
 * Objective:
 * Investigate Linux user-space and kernel-space interaction via direct
 * POSIX/Linux system calls (getpid, getppid, uname, sysinfo).
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

int main(void) {
    struct utsname u;
    struct sysinfo s;

    printf("====================================================\n");
    printf("     Linux System Calls & Kernel Info Explorer      \n");
    printf("====================================================\n\n");

    /* 1. Process Identification */
    printf("[1] Process Identifiers:\n");
    printf("    Process ID (PID)        : %d\n", getpid());
    printf("    Parent Process ID (PPID): %d\n\n", getppid());

    /* 2. Kernel & System Architecture Information */
    if (uname(&u) == 0) {
        printf("[2] Operating System & Kernel Details:\n");
        printf("    System Name     : %s\n", u.sysname);
        printf("    Node/Host Name  : %s\n", u.nodename);
        printf("    Kernel Release  : %s\n", u.release);
        printf("    Kernel Version  : %s\n", u.version);
        printf("    Hardware Machine: %s\n\n", u.machine);
    } else {
        perror("Error invoking uname()");
    }

    /* 3. Memory & System Statistics */
    if (sysinfo(&s) == 0) {
        long total_ram_mb = (s.totalram * s.mem_unit) / (1024 * 1024);
        long free_ram_mb  = (s.freeram  * s.mem_unit) / (1024 * 1024);
        long shared_mb    = (s.sharedram * s.mem_unit) / (1024 * 1024);
        long buffer_mb    = (s.bufferram * s.mem_unit) / (1024 * 1024);

        printf("[3] System Memory Statistics (sysinfo):\n");
        printf("    Total RAM       : %ld MB\n", total_ram_mb);
        printf("    Free RAM        : %ld MB\n", free_ram_mb);
        printf("    Shared RAM      : %ld MB\n", shared_mb);
        printf("    Buffer RAM      : %ld MB\n", buffer_mb);
        printf("    Active Procs    : %d\n", s.procs);
        printf("    Uptime          : %ld seconds\n\n", s.uptime);
    } else {
        perror("Error invoking sysinfo()");
    }

    printf("====================================================\n");
    return 0;
}
