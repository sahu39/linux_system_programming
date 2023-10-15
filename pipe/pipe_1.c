#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int pipefds[2];
    int returnstatus;
    char writemessage[2][20] = {"Hi","Hello"};
    char readmessage[20];
    returnstatus = pipe(pipefds);

    if (returnstatus == -1)
    {
        printf("Can't create pipe\n");
    }

    printf("writing to pipe- message 1 is %s\n",writemessage[0]);
    write(pipefds[1],writemessage[0],sizeof(writemessage[0]));
    read(pipefds[0],readmessage,sizeof(readmessage));
    printf("Reading from pipe – Message 1 is %s\n", readmessage);

    printf("writing to pipe- message 2 is %s\n",writemessage[1]);
    write(pipefds[1],writemessage[0],sizeof(writemessage[1]));
    read(pipefds[0],readmessage,sizeof(readmessage));
    printf("Reading from pipe – Message 2 is %s\n", readmessage);
    return 0;
}
