// Alion Bujku

// info.c

#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/sysinfo.h>

int main(int argc, char* argv[])
{
    struct utsname uname_data;
    struct sysinfo sys_info;
    struct timespec current_time;

    if(clock_gettime(CLOCK_REALTIME, &current_time) == 0) {
        printf("Current Time (ns): %ld\n", current_time.tv_sec * 1000000000 + current_time.tv_nsec);
    } else {
        perror("clock_gettime");
    }

    if(uname(&uname_data) == 0) {
        printf("System Network Name: %s\n", uname_data.nodename);
        printf("Operating System Name: %s\n", uname_data.sysname);
        printf("OS Release: %s\n", uname_data.release);
        printf("OS Version: %s\n", uname_data.version);
        printf("Hardware Type: %s\n", uname_data.machine);
    } else {
        perror("uname");
    }

    printf ("Number of CPUs: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));

    if (sysinfo(&sys_info) == 0) {
        printf("Total Physical Memory: %ld bytes\n", sys_info.totalram);
        printf("Free Memory: %ld bytes\n", sys_info.freeram);
    } else {
        perror("sysinfo");
    }
    
    return 0;
}