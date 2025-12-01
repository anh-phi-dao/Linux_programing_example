#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

char string[20];

int main(int argc, char *argv[])
{

    pid_t childPid;
    pid_t temp;
    printf("Current parent pid: %d \n", getpid());

    childPid = fork();

    switch (childPid)
    {
    case -1:
        perror("fork fail");
        exit(1);

    case 0:

        sleep(2);
        printf("Parent of this pid :%d\n", getppid());
        sleep(1);
        printf("Child with PID:%d escaping\n", getpid());
        exit(EXIT_SUCCESS);

    default:
        printf("Parent escaping\n");
        break;
    }
    return 0;
}