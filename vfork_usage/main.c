#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int istack = 222;

    pid_t a = vfork();

    switch (a)
    {
    case -1:
        perror("vfork");
        break;
    case 0:
        /*vfork continue to use parents memory until child call execv*/
        if (execv("./counting", argv) == -1)
        {
            perror("execv");
            exit(EXIT_FAILURE);
        }
        printf("Escaping from %d process\n", getpid());
        exit(EXIT_SUCCESS);

    default:
        printf("Parent executing ");
        printf("istack=%d\n", istack);
        a = wait(NULL);
        printf("Escaping from %d process\n", getpid());
        exit(EXIT_SUCCESS);
    }
}
