#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define QUEUE_NAME "/my_posix_queue"
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

mqd_t mq;
struct mq_attr attr;
char buffer[] = "Hello thread 2 from thread 1";
unsigned int priority;

void *Thread1(void *arg)
{
    char *string = (char *)arg;
    pthread_t thisThread = pthread_self();
    for (int i = 0; i < 3; i++)
    {
        if (mq_send(mq, string, strlen(string) + 1, 10) == -1)
        {
            perror("mq_send");
            return NULL;
        }
        else
        {
            printf("Thread 1 with id=%lu has sent message: %s\n", thisThread, buffer);
        }
        sleep(1);
    }
    return NULL;
}

void *Thread2(void *arg)
{
    char *string = malloc(sizeof(char) * 256);
    pthread_t thisThread = pthread_self();
    for (int i = 0; i < 3; i++)
    {
        if (mq_receive(mq, buffer, MAX_MSG_SIZE, &priority) == -1)
        {
            perror("mq_receive");
            return NULL;
        }
        else
        {
            printf("Thread 2 with id=%lu  Received message: %s with priority %u\n", thisThread, buffer, priority);
        }
        sleep(1);
    }
    return NULL;
}

int main()
{

    // Set message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Create/open the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    pthread_t t1, t2;

    pthread_create(&t1, NULL, Thread1, buffer);

    pthread_create(&t2, NULL, Thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    if (mq_close(mq) == -1)
    {
        perror("mq_close");
    }
    if (mq_unlink(QUEUE_NAME) == -1)
    {
        perror("mq_unlink");
    }

    return 0;
}