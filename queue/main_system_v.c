#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define QUEUE_NAME "/myqueue"

key_t key;
int msgid;
char string[] = "Hello world";

void *Thread1(void *arg)
{
    char *s = (char *)arg;
    int len = strlen(s);

    msgsnd(msgid, s, len, 0);

    return NULL;
}

void *Thread2(void *arg)
{
    char *s = (char *)malloc(sizeof(char) * 20);

    msgrcv(msgid, s, 20, 0, 0);

    printf("Received message: %s\n", s);
}

int main()
{

    key = ftok("msg1", 1);

    msgid = msgget(key, 0666 | IPC_CREAT);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, Thread1, string);
    pthread_join(t1, NULL);

    printf("Done thread 1\n");

    pthread_create(&t2, NULL, Thread2, NULL);
    pthread_join(t2, NULL);

    printf("Done thread 2\n");

    return 0;
}
