#include<stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int ch;
    int line = 0;

    if (argc != 3) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fp=fopen(argv[1],"r");
    if(fp==NULL){
        printf("Error in file opening...\n");
        return 1;
    }

    int N = atoi(argv[2]);

    if(N < 0){
        printf("N shouldn't be less than 0!\n");
        return 1;
    }

    N = N == 0 ? -1 : N;

    while((ch = fgetc(fp)) != -1){
        if(line == N){
            fgetc(stdin);
            line = 0;
            continue;
        }
        if(ch == '\n')
            line++;
        fputc(ch, stdout);
    }

    return fclose(fp);
}