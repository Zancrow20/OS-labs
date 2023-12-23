#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

void compareFiles(char* file1, char* file2) {

    FILE *f1, *f2;
    int byteCount = 0;

    f1 = fopen(file1, "r");
    f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        printf("Error opening files\n");
        exit(1);
    }

    char ch1, ch2;
    while (((ch1 = fgetc(f1)) != EOF) && ((ch2 = fgetc(f2)) != EOF)) {
        if (ch1 != ch2) {

            printf("Files %s and %s are different. Total bytes compared: %d\n", file1, file2, byteCount);
            fclose(f1);
            fclose(f2);
            exit(0);
        }
        byteCount++;
    }

    printf("Files %s and %s are the same. Total bytes compared: %d\n", file1, file2, byteCount);

    fclose(f1);
    fclose(f2);
}



void compareFilesInDirectories(char* dir1, char* dir2, int maxProcesses) {

    DIR *d1, *d2;
    
    int currentProcesses = 1;

    d1 = opendir(dir1);
    d2 = opendir(dir2);

    if (d1 == NULL || d2 == NULL) {
        printf("Error opening directories\n");
        exit(1);
    }

    struct dirent *dirEntry1, *dirEntry2;
    while ((dirEntry1 = readdir(d1)) != NULL) {
        if (dirEntry1->d_type == DT_REG) { 
            char file1[512];

            snprintf(file1, sizeof(file1), "./%s/%s", dir1, dirEntry1->d_name);
            rewinddir(d2); 

            while ((dirEntry2 = readdir(d2)) != NULL) {

                if (dirEntry2->d_type == DT_REG) {
                    char file2[512];
                    snprintf(file2, sizeof(file2), "./%s/%s", dir2, dirEntry2->d_name);

                    if (currentProcesses = maxProcesses){ 
                        wait(NULL);
                        currentProcesses--;
                    }

                    pid_t child_pid = fork();

                    if (child_pid == -1) {
                        perror("fork");
                        exit(1);
                    } else if (child_pid == 0) {
                        currentProcesses++;
                        printf("Child pid=%d, comparing files %s and %s\n", getpid(), file1, file2);
                        compareFiles(file1, file2);
                        exit(0);
                    } else{ 
                        wait(NULL);
                        currentProcesses--;
                    }
                }
            }
        }
    }

    closedir(d1);
    closedir(d2);

    while(currentProcesses > 0){
        wait(NULL);
        currentProcesses--;
    }
}

int main(int argc, char* argv[]) {



    if (argc != 4) {

        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int maxProcesses = atoi(argv[3]);
    compareFilesInDirectories(argv[1], argv[2], maxProcesses);
    return 0;
}
