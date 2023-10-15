#include<stdio.h>
#include<unistd.h>

int main()
{
    int returntype;
    char writemessage[2][20] = {"Hi","Hello"};
    char readmessage[20];
    int pipefds[2];
    int pid;

    returntype = pipe(pipefds);
    if(returntype == -1)
    {
        perror("Pipe Error: ");
        return(-1);
    }
    fork();
    
    pid = fork();

    if(pid == 0)
    {
        printf("Child process is writing message 1:%s\n ",writemessage[0]);
        write(pipefds[1],writemessage[0],sizeof(writemessage[0]));
    }
    else
    {
        printf("Parent process is reading message1:");
        read(pipefds[0],readmessage,sizeof(readmessage));
        printf("%s\n",readmessage);
    }
    return 0;
                                                                                                                                                                                                                                                                                                                                                                                                        
}
