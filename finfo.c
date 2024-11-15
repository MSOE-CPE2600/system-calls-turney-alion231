// Alion Bujku

// finfo.c

int main(in#define GNU_SOURCE
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat) != 0) {
        perror("stat");
        return 1;
    }

    printf("File Type: ");
    if (S_ISREG(file_stat.st_mode)) printf("Regular File\n");
    else if (S_ISDIR(file_stat.st_mode)) printf("Directory\n");
    else printf("Other\n");

    print_permissions(file_stat.st_mode);
    printf("Owner ID: %d\n", file_stat.st_uid);
    printf("Size: %ld bytes\n", file_stat.st_size);

    char time_buf[26];
    struct tm *mod_time = localtime(&file_stat.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", mod_time);
    printf("Last Modified: %s\n", time_buf);

    return 0;
}