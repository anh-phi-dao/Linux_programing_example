#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *foo(void *arg)
{
    pthread_t thisThread = pthread_self();
    printf("Thread ID of foo is %lu\n", thisThread);
    printf("Thread is running.\n");

    // Explicity terminate thread
    pthread_exit(NULL);

    printf("This will not be executed.\n");
    return NULL;
}

void *count(void *arg)
{
    int count = (*((int *)arg));
    pthread_t thisThread = pthread_self();
    while (count < 50)
    {

        printf("Thread count with id: %lu is couting to %d\n", thisThread, count);
        count++;
        sleep(1);
    }
    return NULL;
}

void *count2(void *arg)
{
    int count = (*((int *)arg));
    pthread_t thisThread = pthread_self();
    while (count <= 20)
    {

        printf("Thread count2 with id: %lu is couting to %d\n", thisThread, count);
        count++;
        sleep(1);
    }
    return NULL;
}

int main()
{

    pthread_t thread1;
    pthread_create(&thread1, NULL, foo, NULL);

    // Wait for thread to finish
    pthread_join(thread1, NULL);

    pthread_t thread[2];
    int start_count = 5;
    pthread_create(thread, NULL, count, &start_count);
    int start_count2 = 10;
    pthread_create(thread + 1, NULL, count2, &start_count2);
    pthread_join(thread[1], NULL);
    pthread_detach(thread[0]);
    return 0;
}