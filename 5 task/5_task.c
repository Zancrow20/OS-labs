#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;

    if (argc != 3) {
        printf("Usage: %s <source_file> <target_file>\n", argv[0]);
        return 1;
    }

    fp1=fopen(argv[1],"r");
    if(fp1==NULL){
        printf("Error in file %s opening...\n", argv[1]);
        return 1;
    }

    fp2=fopen(argv[2],"w");
    if(fp2==NULL){
        printf("Error in file %s opening...\n", argv[2]);
        fclose(fp1);
        return 1;
    }

    int ch;
    while((ch = fgetc(fp1)) != -1){
        fputc(ch, fp2);
    }

    int closeRes1 = fclose(fp1);
    int closeRes2 = fclose(fp2);

    if(closeRes1 != 0){
        return closeRes1;
    }
    if(closeRes2 != 0){
        return closeRes2;
    }

    struct stat s;
    if(stat(argv[1], &s) == 0 && chmod(argv[2], s.st_mode) == 0){
        printf("Contents and permissions copied to %s successfully", argv[2]); 
        return 0;
    }

    printf("An error occurred while copying the permissions!");
    return 1;
}