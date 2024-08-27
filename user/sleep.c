#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Usage: sleep <time>\n");
        exit(1);
    }
    int t = atoi(argv[1]);
    if (t > 0)
    {
        sleep(t);
    }
    else
    {
        printf("Invalid time: %s\n", argv[1]);
        exit(1);
    }

    exit(0);
}