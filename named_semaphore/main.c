#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

#define SHARED_NAME "/shared_memmory"
#define SEMAPHORE_NAME "/semaphore"
#define SIZE 1024

sem_t *posix_semaphore;
char *ptr;
int shared_mem_fd;
int glob = 0;
pid_t process_PID;

int main()
{
    if (sem_unlink(SEMAPHORE_NAME) == -1)
    {
        perror("Semaphore does not exist");
    }
    posix_semaphore = sem_open(SEMAPHORE_NAME, O_CREAT | O_EXCL, 0644, 1);

    if (shm_unlink(SHARED_NAME))
    {
        perror("Shared memmory does not exist");
    }

    shared_mem_fd = shm_open(SHARED_NAME, O_CREAT | O_RDWR, 0644);

    if (shared_mem_fd < 0)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shared_mem_fd, SIZE) == -1)
    {
        perror("ftruncate");
        return -1;
    }

    ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shared_mem_fd, 0);
    sprintf(ptr, "%d", glob);
    process_PID = fork();
    switch (process_PID)
    {
    case -1:
        perror("fork->creating new process has failed");
        exit(EXIT_FAILURE);
        break;

    case 0:
        for (int i = 0; i < 1000000; i++)
        {
            sem_wait(posix_semaphore);
            glob = atoi(ptr);
            glob++;
            sprintf(ptr, "%d", glob);
            sem_post(posix_semaphore);
        }

        break;
    default:
        for (int i = 0; i < 1000000; i++)
        {
            sem_wait(posix_semaphore);
            glob = atoi(ptr);
            glob += 2;
            sprintf(ptr, "%d", glob);
            sem_post(posix_semaphore);
        }

        break;
    }

    if (process_PID == 0)
    {
        printf("Child pid escaping\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        pid_t child = wait(NULL);
        printf("Child %d has returned\n", child);
    }
    glob = atoi(ptr);
    printf("Value of shared memory after 2 process is %d\n", glob);

    if (sem_unlink(SEMAPHORE_NAME) == -1)
    {
        perror("Semaphore does not exist");
    }
}
