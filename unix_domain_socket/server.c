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

#define MAX_LOG 5

const char *SOCKNAME = "/tmp/sock";

const char send_buff[] = "Fuck you client\n";
int sfd, cfd;
struct sockaddr_un addr;
socklen_t addr_len;
int val_write, val_read;
int main()
{

    addr_len = (socklen_t)sizeof(struct sockaddr_un);
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (sfd == -1)
    {
        perror("socket");
        return -1;
    }

    if (remove(SOCKNAME) == -1)
    {
        perror("remove");
    }

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKNAME, sizeof(addr.sun_path) - 1);

    if (bind(sfd, (struct sockaddr *)&addr, addr_len) == -1)
    {
        perror("Bind");
        return -1;
    }

    if (listen(sfd, MAX_LOG) == -1)
    {
        perror("listen");
        return -1;
    }

    cfd = accept(sfd, (struct sockaddr *)&addr, &addr_len);

    if (cfd == -1)
    {
        perror("accept");
        return -1;
    }

    val_write = write(cfd, send_buff, 17);

    printf("%d characters have been sent\n", val_write);

    close(cfd);
    close(sfd);

    if (remove(SOCKNAME) == -1)
    {
        perror("unlink");
        return -1;
    }

    return 0;
}
