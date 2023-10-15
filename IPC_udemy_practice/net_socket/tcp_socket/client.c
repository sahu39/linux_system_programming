#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{
    struct sockaddr_in myaddress;
    int i,ret,data_socket;
    char buffer[BUFFER_SIZE];
    
    /**Create client data Socket**/
    data_socket =  socket(AF_INET, SOCK_STREAM, 0);
    if(data_socket == -1)
    {
        perror("data_socket");
        exit(EXIT_FAILURE);
    }

    /**Create client data Socket**/

    /**Specifying Client credential**/
    memset(&myaddress,0,sizeof(struct sockaddr_in));
    myaddress.sin_family = AF_INET;
    myaddress.sin_port = htons(PORT);
    inet_aton(ADDRESS,&myaddress.sin_addr);

    /**Specifying Client credential**/

    /**Connect system call to unblock the accept in server**/
    ret = connect(data_socket,(const struct sockaddr*)&myaddress,sizeof(struct sockaddr_in));
    if(ret == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    /***Send values to server****/
    do{
        printf("Enter no. to send to server:");
        scanf("%d",&i);
        ret = write(data_socket,&i,sizeof(int));
        if(ret == -1)
        {
            perror("ret");
            break;
        }
        printf("No. of bytes send = %d, data sent = %d \n",ret,i);
    }while(i);
    /***Send values to server****/

    /**Request result**/
    memset(buffer,0,BUFFER_SIZE);
    ret = read(data_socket,buffer,BUFFER_SIZE);
    if(ret == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("Received result from server:%s\n",buffer);
    /**Request result**/

    //printf("No. of bytes send = %d, data sent = %d \n",ret,i);

    /***Close client filed descriptor*****/
    close(data_socket);
    /***Close client filed descriptor*****/

    /**Connect system call to unblock the accept in server**/
    exit(EXIT_SUCCESS);
}

