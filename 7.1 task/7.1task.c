#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main() {
    int hours;
    int minutes;
    int seconds;
    int milliseconds;

    pid_t child1, child2;
    child1 = fork();

    if (child1 == 0) {
        printf("Child 1: pid=%d, ppid=%d\n", getpid(), getppid());
        struct timeval tv;
        gettimeofday(&tv, NULL);
        hours = (int)(tv.tv_sec / 3600 % 24 + 3);
        minutes = (int)(tv.tv_sec / 60 % 60);
        seconds = (int)(tv.tv_sec % 60);
        milliseconds = (int)(tv.tv_usec % 1000);
        printf("Time: %d : %d : %d : %d\n", hours, minutes, seconds, milliseconds);
    } else {
        child2 = fork();
        if (child2 == 0) {
            printf("Child 2: pid=%d, ppid=%d\n", getpid(), getppid());
            struct timeval tv;
            gettimeofday(&tv, NULL);
            hours = (int)(tv.tv_sec / 3600 % 24 + 3);
            minutes = (int)(tv.tv_sec / 60 % 60);
            seconds = (int)(tv.tv_sec % 60);
            milliseconds = (int)(tv.tv_usec % 1000);
            printf("Time: %d : %d : %d : %d\n", hours, minutes, seconds, milliseconds);

        } else {

            printf("Parent: pid=%d\n", getpid());
            struct timeval tv;
            gettimeofday(&tv, NULL);

            hours = (int)(tv.tv_sec / 3600 % 24 + 3);
            minutes = (int)(tv.tv_sec / 60 % 60);
            seconds = (int)(tv.tv_sec % 60);
            milliseconds = (int)(tv.tv_usec % 1000);
            printf("Time: %d : %d : %d : %d\n", hours, minutes, seconds, milliseconds);

            system("ps -x | grep \"7_lab_1\" | grep -v \"grep\" ");
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}