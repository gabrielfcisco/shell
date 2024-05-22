#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/cd.h"

void cd(char *cmd)
{
    if(chdir(cmd)!=0){
        char errmsg[50]= {"cd: "};
        strcat(errmsg, cmd);
        perror(errmsg);
    }
}
