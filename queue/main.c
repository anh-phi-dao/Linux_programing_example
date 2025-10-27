#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define QUEUE_NAME "/myqueue"

mqd_t mdq1;
struct mq_attr mdq1_atrb;

void *Thread1(void *arg)
{
    char *s = (char *)arg;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if (mq_send(mdq1, &s[i], 1, 0) == -1)
        {
            perror("mq_send");
            return NULL;
        }
    }
    return NULL;
}

void *Thread2(void *arg)
{
    struct mq_attr atrib;
    mq_getattr(mdq1, &atrib);

    char *buffer = (char *)malloc(atrib.mq_maxmsg + 1);
    int pos = 0;

    while (1)
    {
        char c;
        ssize_t bytes = mq_receive(mdq1, &c, atrib.mq_msgsize, NULL);
        if (bytes >= 0)
        {
            buffer[pos++] = c;
        }
        else
        {
            break;
        }
        if (pos >= atrib.mq_maxmsg)
            break;
    }

    buffer[pos] = '\0';
    printf("Receive message: %s\n", buffer);
    free(buffer);
    return NULL;
}

char string[] = "Hello world";

int main()
{
    mdq1_atrb.mq_flags = 0;
    mdq1_atrb.mq_maxmsg = 16;
    mdq1_atrb.mq_msgsize = 32;
    mdq1_atrb.mq_curmsgs = 0;

    mdq1 = mq_open("/mdq1", O_CREAT | O_RDWR, 0666, &mdq1_atrb);
    if (mdq1 == (mqd_t)-1)
    {
        perror("mq_open");
        return -1;
    }

    pthread_t t1, t2;

    pthread_create(&t1, NULL, Thread1, string);
    pthread_join(t1, NULL);

    printf("Done thread 1\n");

    pthread_create(&t2, NULL, Thread2, NULL);
    pthread_join(t2, NULL);

    printf("Done thread 2\n");

    mq_close(mdq1);
    mq_unlink("/mdq1");

    return 0;
}
