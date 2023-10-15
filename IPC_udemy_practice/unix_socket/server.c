#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "my_socket"
#define BUFFER_SIZE 128

int main()
{
    struct sockaddr_un name;
    int ret;
    int connection_socket;
    int data_socket;
    int result;
    int data;
    char buffer[BUFFER_SIZE];
  /********Creating master socket file descriptor***********/
    unlink(SOCKET_NAME);
    printf("Creating Mater socket....\n");
    connection_socket = socket(AF_UNIX, SOCK_STREAM, 0); 
    if(connection_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);

    }

    printf("Mater socket created....\n");
  /********Creating master socket file descriptor***********/
  
  /********Specify the socket credential********************/  
    memset(&name,0,sizeof(struct sockaddr_un));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path,SOCKET_NAME,sizeof(name.sun_path)-1);
  /********Specify the socket credential********************/  

  /********binding the master socket file descriptor to socket credential****************/
    printf("binding call started....\n");
    ret = bind(connection_socket,(const struct sockaddr *)&name,sizeof(struct sockaddr_un));
    if(ret == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind call succeed....\n");
  /********binding the master socket file descriptor to socket credential****************/

  /*******listening to number of clients*********************/
    printf("listen call started....\n");
    ret = listen(connection_socket,20);
    if(ret == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("binding call succeed....\n");
  /*******listening to number of clients*********************/

  /*******Main loop for handling connection******************/
    while(1)
    {
        printf("Waiting on accept system call...\n");
        data_socket = accept(connection_socket,NULL,NULL);
        if(ret == -1)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        printf("connection accepted from client....\n");
        
        result = 0;
        for(;;)
        {
            memset(buffer, 0, BUFFER_SIZE);
            printf("Waiting for client to send the data...\n");
            ret = read(data_socket,buffer,BUFFER_SIZE);
            if(ret == -1)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }
            memcpy(&data, buffer, sizeof(int));//void * memcpy(void *to, const void *from, size_t numBytes);
            if(data == 0) break;
            result = result+data;


        }
        /**send result**/
        memset(buffer,0,BUFFER_SIZE);
        sprintf(buffer, "Result is = %d\n",result);

        printf("Sending final value back to the client\n");
        ret = write(data_socket, buffer, BUFFER_SIZE);
        if(ret == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        /**close client socket file descriptor**/
        close(data_socket);


    }
    /**close master socket file descriptor**/
    close(connection_socket);
    printf("connection closed....\n");
  /*******Main loop for handling connection******************/
    unlink(SOCKET_NAME);
    exit(EXIT_SUCCESS);
    return 0;
}
