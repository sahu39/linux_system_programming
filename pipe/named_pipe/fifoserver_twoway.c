#include<stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "/tmp/fifo_twoway"



int main()
{
        int fd;
        char readbuf[80];
        char end[10];
        int to_end;
        int read_bytes;

        mkfifo(FIFO_FILE,S_IFIFO | 0640);
        strcpy(end,"end");

        while(1)
        {
            fd = open(FIFO_FILE,O_RDONLY);
            read_bytes = read(fd,readbuf,sizeof(readbuf));
            readbuf[read_bytes] = '\0';
            printf("Received string:\"%s\" and length is %d\n",readbuf,(int)strlen(readbuf));
            to_end = strcmp(readbuf,end);
            if(to_end == 0)
            {
                close(fd);
                break;
            }
            strrev(readbuf);
            printf("FIFOSERVER: Sending reversed string:\"%s\" & length is %d\n",readbuf,(int)strlen(readbuf));
            write(fd,readbuf,strlen(readbuf));
            sleep(2);

        
        }
    return 0;
}
