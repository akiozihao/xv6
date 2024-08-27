#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int p1[2];
    pipe(p1);
    for (int i = 2; i < 35; i++)
    {
        write(p1[1], &i, sizeof(i));
    }

    int i = 0;
    write(p1[1], &i, sizeof(i));

    while (1)
    {
        int prime, n;
        int p2[2];
        pipe(p2);

        read(p1[0], &prime, sizeof(prime));
        if (prime == 0)
        {
            close(p1[0]);
            close(p1[1]);
            close(p2[0]);
            close(p2[1]);
            exit(0);
        }
        printf("prime %d\n", prime);
        while (read(p1[0], &n, sizeof(n)) && n)
        {
            if (n % prime != 0)
            {
                write(p2[1], &n, sizeof(n));
            }
        }
        write(p2[1], &n, sizeof(n));

        if (fork() == 0)
        {
            close(p1[0]);
            close(p1[1]);
            p1[0] = p2[0];
            p1[1] = p2[1];
            continue;
        }

        // 父进程已经完成读写，所以这里可以释放
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
        break;
    }
    wait(0);
    exit(0);
}