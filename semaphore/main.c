#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

long int glob = 0;
sem_t sema;

void *threadFunc(void *arg)
{
    long int loops = *((int *)arg);
    long int j;
    int s;
    for (j = 0; j < loops; j++)
    {
        s = sem_wait(&sema);
        if (s != 0)
        {
            printf("Error on waiting semaphore\n");
            break;
        }
        glob++;

        s = sem_post(&sema);
        if (s != 0)
        {
            printf("Error on posting semaphore\n");
            break;
        }
    }
    return NULL;
}

int main()
{
    int a;
    a = sem_init(&sema, 0, 1);
    if (a != 0)
    {
        printf("Error on initializing semaphore\n");
    }
    pthread_t t1, t2;
    long int loop = 10000000;
    a = pthread_create(&t1, NULL, threadFunc, &loop);
    if (a != 0)
    {
        printf("Error on creating thread 1\n");
    }
    a = pthread_create(&t2, NULL, threadFunc, &loop);
    if (a != 0)
    {
        printf("Error on creating thread 2\n");
    }
    a = pthread_join(t1, NULL);
    if (a != 0)
    {
        printf("Error on joining thread 1\n");
    }
    a = pthread_join(t2, NULL);
    if (a != 0)
    {
        printf("Error on joining thread 2\n");
    }
    printf("Glob value after 2 thread is %ld\n", glob);
    return 0;
}