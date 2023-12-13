#include<stdio.h>
#include<dirent.h>

int readDirsAndPrint(char *catalog_name){
    DIR *dr = opendir(catalog_name);
    if(dr == NULL){
        printf("Could not open %s directory", catalog_name);
        return 1;
    }    
    struct dirent *d;
    while ((d = readdir(dr)) != NULL) 
        printf("%s\n", d->d_name);
    
    int closeDir = closedir(dr);
    if(closeDir != 0){
        printf("Could not close %s directory\n", catalog_name); 
        return 1;
    }
    return 0; 
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    printf("Current directory:\n");

    int currentDirRes = readDirsAndPrint(".");
    if(currentDirRes != 0){
        return currentDirRes;
    }
    printf("\n");
    printf("Directory %s:\n", argv[1]);

    int secondDirectory = readDirsAndPrint(argv[1]);
    if(secondDirectory != 0){
        return secondDirectory;
    }

    return 0;
}