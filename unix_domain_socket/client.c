#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*libray for socket structure*/
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

const char *SOCKNAME = "/tmp/sock";

char receive_buff[1024];
int cfd;
struct sockaddr_un addr;
socklen_t addr_len;
int val_write, val_read;
int main()
{
    addr_len = (socklen_t)sizeof(struct sockaddr_un);
    cfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (cfd == -1)
    {
        perror("socket");
        return -1;
    }

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKNAME, sizeof(addr.sun_path) - 1);

    if (connect(cfd, (struct sockaddr *)&addr, addr_len) == -1)
    {
        perror("connect");
        return -1;
    }

    do
    {
        val_read = read(cfd, receive_buff, 1024);
        if (val_read > 0)
        {
            printf("Received message:%s\n", receive_buff);
        }
        sleep(1);
    } while (val_read > 0);

    close(cfd);

    return 0;
}
