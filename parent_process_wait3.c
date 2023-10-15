#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid;
    int status;
    pid = fork();

    if (pid ==  0)
    {
         printf("\n**********Child Process*********\n");
         system("ps -eaf");
         sleep(10);
         system("ps -eaf");
         printf("\n**********Child Process end*********\n");
         return 3;
    }
    else
    {
         printf("\n**********Parent Process*********\n");
         sleep(3);
         wait(&status);
         printf("In parent process exit status from the child is decimal %d, hexadecimal %0x\n",status,status);
         printf("\n**********Parent Process end*********\n");
    }
    return 0;
}
/*
op:
---
In parent process exit status from the child is decimal 768, hexadecimal 300
Even though child returns the exit status of 3, why the parent process sees that as 768. The status is stored in the higher order byte, so it is stored in hexadecimal format as 0X0300, which is 768 in decimal. 
*/
