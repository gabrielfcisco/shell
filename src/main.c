#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

char** str_split(char *str){
    char *cmd[3];
    cmd[0] = str;
    int j=1;
    for(int i=0; i<strlen(str); i++){
        if(str[i]==' '){
            str[i] = '\0';
            cmd[0][j++] = str[i+1];
        }
    }
    return cmd;
}

void cd(char* cmd);

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
    char path[50]="/";
    char input[30];
    char *command[3];
    while(strcmp(input, "exit")){
        printf("%s>", path);
        input = readline(NULL);
        command = str_split(input);
        if(strcmp(command[0], "cd")){
            cd(command[1]);
        }
    }
    return 0;
}
