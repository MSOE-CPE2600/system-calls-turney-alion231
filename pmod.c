// Alion Bujku

// pmod.c

#define GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/resource.h>

int main(int argc, char* argv[]) {
    int current_priority = getpriority(PRIO_PROCESS, 0);
    if (current_priority == -1 && errno) {
        perror("getpriority");
        return 1;
    }

    if (setpriority(PRIO_PROCESS, 0, current_priority + 10) != 0) {
        perror("setpriority");
        return 1;
    }
    printf("Priority reduced by 10. New priority: %d\n", current_priority + 10);

    struct timespec sleep_time = {1, 837272638};
    if (nanosleep(&sleep_time, NULL) != 0) {
        perror("nanosleep");
        return 1;
    }

    printf("Goodbye!\n");
    return 0;
}