#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int file_pipe[2];
pid_t child_pid;
int val_write, val_read;
char buff[20];

int main()
{
    if (pipe(file_pipe) == -1)
    {
        perror("pipe");
        return -1;
    }
    child_pid = fork();

    switch (child_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;

    case 0:
        if (close(file_pipe[1]) == -1)
        {
            perror("Close on child");
        }
        memset(buff, 0, 20);
        val_read = read(file_pipe[0], buff, 6);
        printf("Read %d bytes from pipe in child process: %s\n", val_read, buff);
        exit(EXIT_SUCCESS);
        break;

    default:
        if (close(file_pipe[0]) == -1)
        {
            perror("Close on parent");
        }
        sleep(1);
        memset(buff, 0, 20);
        snprintf(buff, 6, "Hello");
        val_write = write(file_pipe[1], buff, 5);
        printf("Write %d bytes\n", val_write);
        break;
    }

    child_pid = wait(NULL);
    printf("Child process %d has returned\n", child_pid);
    return 0;
}