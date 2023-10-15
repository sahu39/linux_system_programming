#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int mypid,myppid;
    printf("Program to know PID and PPID information.\n");
    mypid=getpid();
    myppid=getppid();
    printf("pid is:%d\n",mypid);
    printf("ppid is:%d\n",myppid);
    printf("Cross verification of PPID & PID");
    system("ps -eaf | grep a.out");
    return 0;

}

