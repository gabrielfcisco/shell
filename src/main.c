#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

void cd(char* cmd){
    chdir(cmd);
}

void path(char** cmd);

void execExtBin(char **cmd);
    //pid_t pid;
    //pid = fork();
    //if(pid<0){
    //    printf("Something went wrong.");
    //    exit(-1);
    //}
    //else if(pid==0){
    //}
    //else{
    //    wait(NULL);
    //}

int main()
{
    int i;
    char *dir;
    char *input;
    dir = (char*) calloc(100, sizeof(char *));
    input = (char*) calloc(100, sizeof(char *));
    char *command[3];
    for(i=0;i<3;i++){
        command[i] = (char*)calloc(30, sizeof(char *));
    }
    char* token;
    while(1){
        printf("%s>", getcwd(dir, 100));
        strcpy(input, readline(NULL));
        i=0;
        token = strtok(input, " ");
        while (token != NULL) {
            strcpy(command[i], token);
            i++;
            token = strtok(NULL, " ");
        }
        if(strcmp(command[0], "cd")==0){
            printf("cd");
            cd(command[1]);
        }
        else if(strcmp(command[0], "path")==0){
            path(command);
        }
        else if(strcmp(command[0], "exit")==0){
            break;
        }
        else
        {
            execExtBin(command);
        }
    }
    free(dir);
    free(input);
    for(int i=0;i<3;i++){
        free(command[i]);
    }
    return 0;
}
