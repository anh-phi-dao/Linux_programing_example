#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS, EXIT_FAILURE

#define MAX_BUFFER_SIZE 256

int main()
{
    FILE *fp;
    char buffer[MAX_BUFFER_SIZE];
    int status;

    fp = popen("export LD_LIBRARY_PATH=\"$PWD\"", "r");
    if (fp == NULL)
    {
        perror("Failed to run command");
        return EXIT_FAILURE;
    }

    status = pclose(fp);
    if (status == -1)
    {
        perror("pclose error");
        return EXIT_FAILURE;
    }

    fp = popen("export", "r");
    if (fp == NULL)
    {
        perror("Failed to run command");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("%s", buffer);
    }

    status = pclose(fp);
    if (status == -1)
    {
        perror("pclose error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}