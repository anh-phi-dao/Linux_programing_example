#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

long int glob = 0;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *threadFunc(void *arg)
{
    long int loops = *((int *)arg);
    long int j;
    int s;
    for (j = 0; j < loops; j++)
    {
        s = pthread_mutex_lock(&mtx);
        if (s != 0)
        {
            printf("Error locking mutex\n");
        }
        glob++;

        s = pthread_mutex_unlock(&mtx);
        if (s != 0)
        {
            printf("Error locking mutex\n");
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    long int loops, s;
    loops = 10000000;
    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
    {
        printf("Error on creating thread\n");
        return -1;
    }
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
    {
        printf("Error on creating thread\n");
        return -1;
    }
    s = pthread_join(t1, NULL);
    if (s != 0)
    {
        printf("Error on creating thread\n");
        return -1;
    }
    s = pthread_join(t2, NULL);
    if (s != 0)
    {
        printf("Error on creating thread\n");
        return -1;
    }
    printf("glob = %ld\n", glob);
    return 0;
}