#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <libgen.h>
#include <signal.h>
#include <time.h>

char cmd[200];
pid_t childPID;

int main(int arg, char *argv[])
{
    childPID = fork();
    switch (childPID)
    {
    case -1:
        perror("fork");
        return -1;
        break;

    /*child process*/
    case 0:
        printf("Child PID %d exiting\n", getpid());
        return 0;

    /*parent process*/
    default:
        sleep(3);
        /*this command will show out running processes*/
        sprintf(cmd, "ps | grep %s", basename(argv[0]));
        printf("performing %s command \n", cmd);
        /*Execute command ps | grep main*/
        system(cmd);

        /*Send signal kill to zombie process*/
        if (kill(childPID, SIGKILL) == -1)
        {
            perror("kill");
        }
        sleep(3);
        printf("After sending SIGKILL to zombie PID=%d\n", childPID);
        system(cmd);
        break;
    }
}