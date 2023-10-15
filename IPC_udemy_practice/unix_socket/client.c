#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME  "my_socket"
#define BUFFER_SIZE  128

int main(int argc,char *argv[])
{
    struct sockaddr_un addr;
    int i,ret,data_socket;
    char buffer[BUFFER_SIZE];

    /**Create data socket**/
    printf("Creating client data socket....\n");
    data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if(data_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("client data socket creation done....\n");

    memset(&addr,0,sizeof(struct sockaddr_un));//void *memset(void *ptr, int x, size_t n);
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SOCKET_NAME,sizeof(addr.sun_path)-1);

    ret = connect(data_socket,(const struct sockaddr *)&addr,sizeof(struct sockaddr_un));
    if(ret == -1)
    {
        fprintf(stderr,"The server is down...\n");
        exit(EXIT_FAILURE);
    }

    /**Send Arguments**/
    do
    {
        printf("Enter no. to send to the server:");
        scanf("%d",&i);
        ret = write(data_socket,&i,sizeof(int));
        if(ret == -1)
        {
            perror("write");
            break;
        }
        printf("No of bytes sent = %d, data sent = %d\n", ret, i);
    }while(i);
    /**Send Arguments**/

    /**Request Result**/
    memset(buffer, 0, BUFFER_SIZE);
    ret = read(data_socket, buffer, BUFFER_SIZE);
    if(ret == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("Received result from server : %s\n",buffer);
    /**Request Result**/

    /**close socket**/
    close(data_socket);
    exit(EXIT_SUCCESS);

}


