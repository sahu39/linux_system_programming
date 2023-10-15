#include<stdio.h>
#include<unistd.h>
int main()
{
    int pipefds[2];
    int returnstatus;
    char writemessage[2][20] = {"Vishnu","Brahma"};
    char readmessage[20];
    if((returnstatus = pipe(pipefds)) == -1)
    {
        printf("Pipe creation failed\n");
        return 1;
    }
    printf("writting to pipe- message_1:%s\n",writemessage[0]);
    write(pipefds[1],writemessage[0],sizeof(writemessage[0]));
    read(pipefds[0],readmessage,sizeof(readmessage));
    printf("readmessage value after reading from pipe:%s\n",readmessage);

    printf("writting to pipe- message_2:%s\n",writemessage[1]);
    write(pipefds[1],writemessage[1],sizeof(writemessage[1]));
    read(pipefds[0],readmessage,sizeof(readmessage));
    printf("readmessage value after reading from pipe:%s\n",readmessage);
    
    


    return 0;
}
