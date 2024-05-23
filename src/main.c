#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/cd.h"
#include "../include/path.h"
#include "../include/execExtBin.h"

void ExecCommand (char** command);
void HandleFile (char* filename);

int main(int argc, char *argv[])
{
    char *dir;
    char *input;
    char *command[3];
    command[2]=NULL;
    dir = (char*)calloc(512, sizeof(char *));
    if (argc > 1){
        HandleFile(argv[1]);
    }
    printf("\t\t\t\tBem Vindo ao Nosso Shell!!\n");
    printf("\t\t\tEsperamos que você tenha uma boa experiencia.\n");
    while(1){
        printf("%s", getcwd(dir, 512));
        input = readline("> ");
        command[0] = strtok(input, " ");
        command[1] = strtok(NULL, " ");
        if(strcmp(command[0], "exit")==0)
        {
            break;
        }
        ExecCommand(command);


    }
    printf("Shell Finalizado com Sucesso. Obrigado por usar nosso programa.\n");

    free(dir);
    free(input);
    free(command[1]);

    return 0;
}

void ExecCommand (char** command){
    if(strcmp(command[0], "cd")==0){
        cd(command[1]);
    }
    else if(strcmp(command[0], "path")==0){
        path(command[1]);
    }
    else if(command[0]){
        execExtBin(command);
    }
}

void HandleFile(char* filename){
    FILE *fp;
    const int bufferSize = 4096;
    char *buffer;
    char *command[3];
    buffer = (char*)calloc(bufferSize, sizeof(char *));
    command[2]=NULL;
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "%s: %s: No such file or directory", "/bin/shell", filename);
        exit(1);
    }
    while(fgets(buffer, bufferSize, fp))
    {
        if(!(buffer[0] == '#' || buffer[0]=='\n'))
        {
            printf("%s", buffer);
            int lenght = strlen(buffer);
            buffer[lenght -1] = '\0';
            command[0] = strtok(buffer, " ");
            command[1] = strtok(NULL, " ");
            ExecCommand(command);
        }
    }
    fclose(fp);
    free(buffer);
}
