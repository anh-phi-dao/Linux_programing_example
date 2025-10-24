#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static int idata = 111;
char string[20];

int main(int argc, char *argv[])
{
    int istack = 222;

    pid_t childPid;

    childPid = fork();

    switch (childPid)
    {
    case -1:
        perror("fork fail");
        exit(1);

    case 0:
        idata *= 3;
        istack *= 3;
        break;

    default:
        sleep(3);
        break;
    }

    if (childPid == 0)
    {
        sprintf(string, "child");
    }
    else
    {
        sprintf(string, "parent");
    }

    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(), string, idata, istack);

    return 0;
}