#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread_A_function(void *arg)
{
    printf("Thread A: Attempting to acquire Mutex 1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread A: Acquired Mutex 1. Sleeping...\n");
    sleep(1); // Simulate work

    printf("Thread A: Attempting to acquire Mutex 2...\n");
    pthread_mutex_lock(&mutex2); // This will block if Mutex 2 is held by Thread B
    printf("Thread A: Acquired Mutex 2.\n");

    // Critical section with both mutexes held
    printf("Thread A: Critical section with both mutexes.\n");
    pthread_mutex_unlock(&mutex2);
    printf("Thread A: Released Mutex 2.\n");
    pthread_mutex_unlock(&mutex1);
    printf("Thread A: Released Mutex 1.\n");
    return NULL;
}

void *thread_B_function(void *arg)
{
    printf("Thread B: Attempting to acquire Mutex 2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread B: Acquired Mutex 2. Sleeping...");
    sleep(1); // Simulate work

    printf("Thread B: Attempting to acquire Mutex 1...\n");
    pthread_mutex_lock(&mutex1); // This will block if Mutex 1 is held by Thread A
    printf("Thread B: Acquired Mutex 1.\n");

    // Critical section with both mutexes held
    printf("Thread B: Critical section with both mutexes.\n");

    pthread_mutex_unlock(&mutex1);
    printf("Thread B: Released Mutex 1.\n");
    pthread_mutex_unlock(&mutex2);
    printf("Thread B: Released Mutex 2.\n");
    return NULL;
}

int main()
{
    pthread_t threadA, threadB;

    pthread_create(&threadA, NULL, thread_A_function, NULL);
    pthread_create(&threadB, NULL, thread_B_function, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    printf("Main: All threads finished.\n");
    return 0;
}