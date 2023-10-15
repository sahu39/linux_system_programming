#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid;
    pid = fork();

    if (pid ==  0)
    {
         system("ps -eaf");
         sleep(10);
         system("ps -eaf");
    }
    else
    {
        sleep(3);
    }
    return 0;
}
