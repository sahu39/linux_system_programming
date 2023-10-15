/*close system call*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <errno.h>
extern int errno;//from errno.h
int main()
{
    int fd=open("foo1.txt",O_RDONLY | O_CREAT);//from fcntl.h
    printf("fd=%d\n",fd);
//    if(fd == -1)
//    {
//        printf("Error number:%d\n",errno);
//        perror("program");
//    }
    int fd1=open("foo2.txt",O_RDWR | O_CREAT,0);
    printf("fd1=%d\n",fd1);

    return 0;
}
/*output:
rakesh@rakesh-desktop:~/Linux_system_programming/advanced_c/filehandling$ ./IO_System_call_2
fd=3
fd1=4
*/
