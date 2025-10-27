#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int istack = 222;

    int a = vfork();

    switch (a)
    {
    case -1:
        perror("vfork");
        break;
    case 0:
        sleep(3);
        printf("Child executing ");
        istack *= 3;
        printf("istack=%d\n", istack);
        exit(EXIT_SUCCESS);

    default:
        printf("Parent executing ");
        printf("istack=%d\n", istack);
        exit(EXIT_SUCCESS);
    }
}
