#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    const int bufferSize = 4096;
    char buffer[bufferSize];
    int currentFile = (argc > 1 ? 1 : 0);

    while (currentFile < argc)
    {
        if (argc > 1)
        {
            fp = fopen(argv[currentFile], "rb");
            if (fp == NULL)
            {
                fprintf(stderr, "%s: %s: No such file or directory", argv[0], argv[currentFile]);
                exit(1);
            }
        }

        while (fgets(buffer, bufferSize, (fp == NULL ? stdin : fp)))
        {
            int lenght = strlen(buffer);
            buffer[lenght -1] = '\0';
            fprintf(stdout, "%s\n", buffer);
        }

        fclose(fp);
        currentFile++;
    }
    return 0;
}

