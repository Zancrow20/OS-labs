#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

FILE *fp1;
int listFiles(const char *catalog_name){
    long int sizeSum = 0L;
    int count = 0;
    int biggest_file_size = 0;
    char biggest_file_name[300] = "null";
    DIR *dr = opendir(catalog_name);
    if(dr == NULL){
        printf("Could not open %s directory", catalog_name);
        return 1;
    }    

    struct dirent *entity;
    struct stat s;
    entity = readdir(dr);
    while (entity != NULL) {
        char path[100] = {0};
        strcat(path, catalog_name);
        strcat(path, "/");
        strcat(path, entity->d_name);
        int is_not_cycle = strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0;
        if(entity->d_type == DT_DIR && is_not_cycle){
            int list = listFiles(path); 
            if(list != 0){
                return list;
            }
        }
        if(entity->d_type == DT_REG && is_not_cycle){
            stat(path, &s);
            if(s.st_size > biggest_file_size){
                biggest_file_size = s.st_size;
                strcpy(biggest_file_name, entity->d_name);
            }
            sizeSum += s.st_size;
            count++;
        }
        entity = readdir(dr);
    }
    
    int closeDir = closedir(dr);
    if(closeDir != 0){
        printf("Could not close %s directory\n", catalog_name); 
        return 1;
    }
    
    printf("Directory: %s. Count of files: %d. Summary size: %ld bytes. Biggest file: %s\n", catalog_name, count, sizeSum, biggest_file_name);
    fprintf(fp1,"Directory: %s. Count of files: %d. Summary size: %ld bytes. Biggest file: %s\n", catalog_name, count, sizeSum, biggest_file_name);
    sizeSum = 0;
    return 0; 
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    fp1=fopen(argv[2],"w");
    if(fp1==NULL){
        printf("Error in file %s opening...\n", argv[1]);
        return 1;
    }
    fprintf(fp1, "\n");

    int res = listFiles(argv[1]);
    if(res != 0){
        return res;
    }

    int closeRes1 = fclose(fp1);
    if(closeRes1 != 0){
        printf("Could not close %s file\n", argv[2]);
        return closeRes1;
    }
    return 0;
}