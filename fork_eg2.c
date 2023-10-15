#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int child_pid,child_status;
int main()
{
    int ret;
    fork();
    fork();
    fork();
/*
    switch(ret)
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            printf("hello World child\n");
            exit(0);
        default:
            printf("hello World parent\n");

    }*/
    printf("Hello World\n");
    return 0;
}
