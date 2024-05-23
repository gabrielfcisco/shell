#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/path.h"
#include "../include/execExtBin.h"

// Execução de programas externos
void execExtBin(char **command) {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork falhou");
        return;
    } else if (pid == 0) {
        // Processo filho
        char buffer[1024];
        int found = 0;

        if(PATH == NULL){
            fprintf(stderr, "Path nao esta configurado.\n");
            exit(EXIT_FAILURE);
        }

        // Loop pelos caminhos para encontrar o executável
        for (int i = 0; PATH[i] != NULL; i++) {
            snprintf(buffer, sizeof(buffer), "%s/%s", PATH[i], command[0]);
            // printf("tentando: %s\n", buffer);

            // Verifica se o arquivo é executável
            if (access(buffer, X_OK) == 0) {
                found = 1;
                // Executa o arquivo com os argumentos a partir do segundo elemento
                execv(buffer, command);
                // Se execv() retornar, ocorreu um erro
                perror("exec falhou");
                exit(EXIT_FAILURE);
            }
        }

        if(!found){
            fprintf(stderr, "Comando nao encontrado: %s\n", command[0]);
            exit(EXIT_FAILURE);
        }

    } else {
        // Processo pai
        int status;
        waitpid(pid, &status, 0);

        if(WIFEXITED(status)){
            // printf("Programa %s encerrado\n", command[0]);
        }
        else{
            printf("Programa terminado de forma anormal\n");
        }
    }
}
