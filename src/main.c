#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/cd.h"
#include "../include/path.h"

int main(int argc, char *argv[])
{
    int i;
    char *dir;
    char *input;
    char *command[2];
    dir = (char*)calloc(512, sizeof(char *));
    input = (char*)calloc(512, sizeof(char *));
    for(i=0;i<2;i++){
        command[i] = (char*)calloc(256, sizeof(char *));
    }
    //fopen(argv[1], "r");
    while(1){
        printf("%s>", getcwd(dir, 512));
        input = readline(NULL);
        command[0] = strtok(input, " ");
        command[1] = strtok(NULL, " ");
        if(strcmp(command[0], "cd")==0){
            cd(command[1]);
        }
        else if(strcmp(command[0], "path")==0){
            path(command[1]);
        }
        else if(strcmp(command[0], "exit")==0){
            break;
        }
        else
        {
            //execExtBin(command);
        }
    }
    free(dir);
    free(input);
    free(command[1]);
    return 0;
}
