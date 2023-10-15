#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MY_FIFO"
int main()
{
    int fd;
    int end_process;
    int stringlen;
    int read_bytes;
    char readbuf[80];
    char end_str[5];

    printf("FIFO CLIENT:send message infinitely ,to end enter \"end\"\n");
    fd = open(FIFO_FILE, O_CREAT|O_WRONLY);
 //   if((open(FIFO_FILE,O_CREAT|O_WRONLY)) != 0)
 //   {
 //       perror("Error Open:");
 //       return -1;
 //   }
    strcpy(end_str,"end");

    while(1)
    {
        printf("Enter string:");
        fgets(readbuf,sizeof(readbuf),stdin);

        stringlen = strlen(readbuf);
        readbuf[stringlen-1] = '\0';

        end_process = strcmp(readbuf,end_str);
        if(end_process != 1)
        {
            write(fd, readbuf,strlen(readbuf));
            printf("sent string: \"%s\" and string length is %d\n",readbuf,(int)strlen(readbuf));
            read_bytes = read(fd, readbuf, sizeof(readbuf));
            readbuf[read_bytes] = '\0';
            printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        }
        else
        {
            write(fd, readbuf,strlen(readbuf));
            printf("sent string: \"%s\" and string length is %d\n",readbuf,(int)strlen(readbuf));
            close(fd);
            break;
        }
            
    
    }
    return 0;
}
