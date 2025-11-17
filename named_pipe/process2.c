#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FIFO_NAME "/tmp/myfifo"

int fd;
char buff[1024];
int main()
{

    mkfifo(FIFO_NAME, 0644);

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    memset(buff, 0, 1024);

    read(fd, buff, sizeof(buff));

    close(fd);

    // Print the read message
    printf("Read from process1: %s\n", buff);

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    memset(buff, 0, 1024);
    sprintf(buff, "Hello process q");
    write(fd, buff, strlen(buff));
    close(fd);

    return 0;
}