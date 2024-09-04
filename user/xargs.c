#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
        exit(0);
    char *params[MAXARG];
    int cnt = 0;
    for (int i = 1; i < argc; i++)
    {
        params[i - 1] = argv[i];
        cnt++;
    }
    char buf[2048];
    int idx = 0;
    char ch;
    int findFlag = 0;
    while (read(0, &ch, 1) > 0)
    {
        if (!findFlag && ch == ' ')
        {
            continue;
        }
        findFlag = 1;
        if (ch != '\n')
        {
            buf[idx++] = ch;
        }
        else
        {
            buf[idx] = 0;
            params[cnt] = buf;
            if (fork() == 0)
            {
                exec(params[0], params);
            }
            else
            {
                wait(0);
            }
            idx = 0;
            findFlag = 0;
        }
    }
    exit(0);
}