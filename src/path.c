#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
    // Obtém a variável de ambiente PATH
    char *original_PATH = getenv("PATH");
    if (original_PATH == NULL) {
        printf("Variável de ambiente PATH não encontrada.\n");
        return 1;
    }

    // Faz uma cópia da string PATH
    // Isso é feito para evitar modificar a string original
    char *PATH = strdup(original_PATH);
    if (PATH == NULL) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }

    // Aloca memória para o array de caminhos
    // Assumindo um máximo de 1024 caminhos
    char **path = (char **)malloc(sizeof(char *) * 1024);
    if (path == NULL) {
        printf("Falha na alocação de memória.\n");
        free(PATH); // Libera a memória alocada antes de retornar
        return 1;
    }

    // Parseia a string PATH
    char *token = strtok(PATH, ":");
    int count = 0;
    while (token != NULL) {
        // Faz uma cópia do caminho e armazena no array
        path[count] = strdup(token);
        token = strtok(NULL, ":");
        count++;
    }
    path[count] = NULL; // Termina o array com NULL

    // Loop pelos caminhos para encontrar o executável
    for (int i = 0; path[i] != NULL; i++) {
        // Cria um buffer para o caminho do executável
        char buffer[1024];
        snprintf(buffer, sizeof(buffer), "%s/%s", path[i], argv[1]);

        // Verifica se o arquivo é executável
        if (access(buffer, X_OK) == 0) {
            // Executa o arquivo com os argumentos a partir do segundo elemento
            execv(buffer, &argv[1]);
            // Se execv() retornar, ocorreu um erro
            perror("execv");
        }
    }

    // Libera a memória alocada
    for (int i = 0; path[i] != NULL; i++) {
        free(path[i]);
    }
    free(path);
    free(PATH); // Libera a string PATH copiada

    printf("Executável não encontrado em nenhum diretório do PATH.\n");
    return 1;
}
