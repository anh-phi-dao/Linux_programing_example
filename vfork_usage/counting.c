#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    for (int i = 0; i < 5; i++)
    {
        sleep(1);
        printf("Value i=%d\n", i);
    }
    return 0;
}