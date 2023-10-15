#include<stdio.h>
#include<unistd.h>

int main()
{
    int pid;
    pid=fork();
    /* child process*/
    if(pid==0)
    {
        printf("Child process is running hello_world process.\n");
        execl("./hello_world","./hello_world",(char *)0);
        printf("This would not print\n");
    }
    else
    {
        sleep(3);
        printf("Parent process is running while_loop process.\n");
        execl("./while_loop","./while_loop",NULL);
        printf("This would not print\n");
    }
    return 0;
}
