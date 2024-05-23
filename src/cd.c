#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/cd.h"

void cd(char *cmd)
{
    if (cmd == NULL) {
        printf("cd: too little arguments.\n");
        return;
    }
    if(chdir(cmd)!=0){
        char errmsg[50]= {"cd: "};
        strcat(errmsg, cmd);
        perror(errmsg);
    }
}
