#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main()
{
    char **env = environ;
    for (int i = 0; i < 10; i++)
    {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}
