#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int glob = 0;
static void *threadFunc(void *arg)
{
    int loops = *((int *)arg);
    int loc, j;
    for (j = 0; j < loops; j++)
    {
        glob++;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;
    loops = 10000;
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
    printf("glob = %d\n", glob);
    return 0;
}