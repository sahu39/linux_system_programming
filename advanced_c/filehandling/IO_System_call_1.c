#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <errno.h>
extern int errno;//from errno.h
int main()
{
    int fd=open("foo.txt",O_RDONLY | O_CREAT);//from fcntl.h
    printf("fd=%d\n",fd);
    if(fd == -1)
    {
        printf("Error number:%d\n",errno);
        perror("program");
    }
    

    return 0;
}
