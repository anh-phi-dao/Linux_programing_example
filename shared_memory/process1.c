#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define OBJECT_NAME "/shared_zone"
#define SIZE 1024
int fd;
char *ptr;

int main()
{
    fd = shm_open(OBJECT_NAME, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        perror("shm_open");
        return -1;
    }
    /*Set the size of the object in bytes*/
    if (ftruncate(fd, SIZE) == -1)
    {
        perror("ftruncate");
        return -1;
    }
    /*Ask the kernel to create a new virtual memory area*/
    ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    sprintf(ptr, "Hello second process\n");

    printf("Process 1 has sent data to process2\n");

    return 0;
}