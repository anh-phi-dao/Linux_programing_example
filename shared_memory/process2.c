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
struct stat sb;

int main()
{
    fd = shm_open(OBJECT_NAME, O_RDONLY, 0644);
    if (fd < 0)
    {
        perror("shm_open");
        return -1;
    }

    if (fstat(fd, &sb) == -1)
    {
        perror("fstat");
        return -1;
    }

    /*Ask the kernel to create a new virtual memory area*/
    ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    printf("Process 2 receive from process 1\n%s\n", ptr);

    return 0;
}