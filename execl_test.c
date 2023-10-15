#include<stdio.h>
#include<unistd.h>
void main()
{
    execl("./hello_world","./hello_world",(char *)0);
    printf("This would not print\n");
    return;
}
/*****************output*********************
 Hello world
 *******************************************/
