#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("shared_file.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[10];

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    { // Child process
        write(fd, "child", 5);
        lseek(fd, 0, SEEK_SET); // Seek to beginning
        read(fd, buffer, 5);
        printf("Child read: %s\n", buffer);
    }
    else
    { // Parent process
        write(fd, "parent", 6);
        lseek(fd, 0, SEEK_SET); // Seek to beginning
        read(fd, buffer, 6);
        printf("Parent read: %s\n", buffer);
    }

    close(fd);
    return 0;
}