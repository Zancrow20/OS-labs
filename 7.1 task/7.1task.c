#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main() {
    pid_t child1, child2;
    child1 = fork();

    if (child1 == 0) {
        printf("Child 1: pid=%d, ppid=%d\n", getpid(), getppid());
        struct timeval tv;
        gettimeofday(&tv, NULL);

        printf("Time: %ld : %ld : %ld : %ld\n", tv.tv_sec / 3600, (tv.tv_sec % 3600) / 60, tv.tv_sec % 60, tv.tv_usec / 1000);

    } else {
        child2 = fork();
        if (child2 == 0) {
            printf("Child 2: pid=%d, ppid=%d\n", getpid(), getppid());
            struct timeval tv;
            gettimeofday(&tv, NULL);

            printf("Time: %ld : %ld : %ld : %ld\n", tv.tv_sec / 3600, (tv.tv_sec % 3600) / 60, tv.tv_sec % 60, tv.tv_usec / 1000);

        } else {

            printf("Parent: pid=%d\n", getpid());
            struct timeval tv;
            gettimeofday(&tv, NULL);

            printf("Time: %ld : %ld : %ld : %ld\n", tv.tv_sec / 3600, (tv.tv_sec % 3600) / 60, tv.tv_sec % 60, tv.tv_usec / 1000);

            system("ps -x");
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}