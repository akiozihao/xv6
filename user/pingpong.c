
#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int p[2];
    char buf[5];
    pipe(p);
    if (fork() == 0)
    {
        // child
        read(p[0], buf, sizeof(buf));
        printf("%d: received %s\n", getpid(), buf);
        write(p[1], "pong", 5);
        close(p[0]);
        close(p[1]);
    }
    else
    {
        // parent
        write(p[1], "ping", 5);
        wait(0);
        read(p[0], buf, sizeof(buf));
        printf("%d: received %s\n", getpid(), buf);
        close(p[0]);
        close(p[1]);
    }
    exit(0);
}