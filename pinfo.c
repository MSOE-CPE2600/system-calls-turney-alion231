// Alion Bujku

// pinfo.c

#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>  // Added for getpriority and PRIO_PROCESS
#include <errno.h>

void print_scheduler(int policy) {
    switch (policy) {
        case SCHED_OTHER: printf("Scheduling Method: SCHED_OTHER\n"); break;
        case SCHED_FIFO: printf("Scheduling Method: SCHED_FIFO\n"); break;
        case SCHED_RR: printf("Scheduling Method: SCHED_RR\n"); break;
        default: printf("Scheduling Method: Unknown\n"); break;
    }
}

int main(int argc, char* argv[]) {
    pid_t pid = (argc > 1) ? atoi(argv[1]) : getpid();
    int priority = getpriority(PRIO_PROCESS, pid);
    int policy = sched_getscheduler(pid);

    if (priority == -1 && errno) {
        perror("getpriority");
        return 1;
    }

    if (policy == -1 && errno) {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Process ID: %d\n", pid);
    printf("Priority: %d\n", priority);
    print_scheduler(policy);

    return 0;
}