#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/path.h"


char **PATH = NULL;

void
path(char* cmd)
{
    // Obtém a variável de ambiente PATH
    char *original_PATH = cmd;
    if (original_PATH == NULL) {
        printf("Variável de ambiente PATH não encontrada.\n");
        return;
    }

    // Faz uma cópia da string PATH
    // Isso é feito para evitar modificar a string original
    char *path = strdup(original_PATH);
    if (path == NULL) {
        printf("Falha na alocação de memória.\n");
        return;
    }

    // Aloca memória para o array de caminhos
    // Assumindo um máximo de 1024 caminhos
    if(PATH == NULL){
        PATH = (char **)malloc(sizeof(char *) * 1024);
        if (PATH == NULL) {
            printf("Falha na alocação de memória.\n");
            free(path); // Libera a memória alocada antes de retornar
            return;
        }
        
        // Parseia a string PATH
        char *token = strtok(path, ":");
        int count = 0;
        while (token != NULL) {
            // Faz uma cópia do caminho e armazena no array
            PATH[count] = strdup(token);
            token = strtok(NULL, ":");
            count++;
        }
        PATH[count] = NULL; // Termina o array com NULL
    }else{
        int count = 0;
        while(PATH[count] != NULL){
            count++;
        }

        char *token = strtok(path, ":");
        while (token != NULL) {
            // Faz uma cópia do caminho e armazena no array
            PATH[count] = strdup(token);
            token = strtok(NULL, ":");
            count++;
        }
        PATH[count] = NULL; // Termina o array com NULL
    }
    // // Loop pelos caminhos para encontrar o executável
    // for (int i = 0; path[i] != NULL; i++) {
    //     // Cria um buffer para o caminho do executável
    //     char buffer[1024];
    //     snprintf(buffer, sizeof(buffer), "%s/%s", path[i], argv[1]);
    //
    //     // Verifica se o arquivo é executável
    //     if (access(buffer, X_OK) == 0) {
    //         // Executa o arquivo com os argumentos a part
    //         ir do segundo elemento
    //         execv(buffer, &argv[1]);
    //         // Se execv() retornar, ocorreu um erro
    //         perror("execv");
    //     }
    // }
    //
    // // Libera a memória alocada
    // for (int i = 0; path[i] != NULL; i++) {
    //     free(path[i]);
    // }
    //
    int count = 0;
    while(PATH[count]!=NULL){
        printf("[%d]: %s\n", count+1, PATH[count]);
        count++;
    }
    free(path);

}
