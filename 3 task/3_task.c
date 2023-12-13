#include<stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int ch;
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fp=fopen(argv[1],"w");
    if(fp==NULL){
        printf("Error in file opening...\n");
        return 1;
    }

    printf("Enter text. Press Ctrl-F to exit.\n");

    //ASCII code of Ctrl-F = 6
    while((ch = fgetc(stdin)) != 6){
        fputc(ch, fp);   
    }

    return fclose(fp);
}