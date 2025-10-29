#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int numDead;
    pid_t childPID;
    pid_t childCurrentPID;
    int j;

    for (int i = 0; i < 3; i++)
    {
        childPID = fork();
        switch (childPID)
        {
        case -1:
            perror("fork");
            return -1;
            break;

        case 0:
            printf("child started with PID:%d is sleeping 2 seconds\n", getpid());
            sleep(2);
            return 0;

        default:
            break;
        }
    }

    numDead = 0;
    while (1)
    {
        childPID = wait(NULL);
        if (childPID == -1)
        {
            printf("No more child\n");
            break;
        }
        else
        {
            numDead++;
            printf("wait() returned child PID :%d\n", childPID);
            printf("Now the number of completed children is :%d\n", numDead);
        }
    }
    return 0;
}
