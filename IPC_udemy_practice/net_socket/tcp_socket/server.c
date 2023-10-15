#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 100
#define ADDRESS "127.0.0.1" //loopback address

int main(){
    struct sockaddr_in myaddr;
    int ret;
    int connection_socket;
    int data_socket;
    int result;
    int data;
    char buffer[BUFFER_SIZE];
    /*****Creating master socket file descriptor********/
    //unlink(connection_socket);
    printf("Creating master socket......\n");
    connection_socket = socket(AF_INET,SOCK_STREAM,0);
    if(connection_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    printf("Master file descriptor created\n");
    /*****Creating master socket file descriptor********/
    /*struct sockaddr_in {
            short            sin_family;   // e.g. AF_INET
            unsigned short   sin_port;     // e.g. htons(3490)
            struct in_addr   sin_addr;     // see struct in_addr, below
            char             sin_zero[8];  // zero this if you want to
    };

    struct in_addr {
            unsigned long s_addr;  // load with inet_aton()
    };*/

    /************specify the socket credentials**********/
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(PORT);
    inet_aton(ADDRESS,&myaddr.sin_addr);//Store ADDRESS to sockaddr_in.sin_addr
    /************specify the socket credentials**********/

    /***********binding socket credential to master file descriptopr**********/
    printf("bind call started........\n");
    ret = bind(connection_socket,(const struct sockaddr *)&myaddr,sizeof(struct sockaddr_in));
    if(ret == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind call succeed........\n");
    /***********binding socket credential to master file descriptopr**********/

    /**********listening to no. of clients***********************************/
    printf("listen call started.......\n");
    ret = listen(connection_socket,20);
    if(ret == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("listen call succceed.......\n");

    /**********listening to no. of clients***********************************/
    
    /**********main loop for handling connection****************************/
    while(1)
    {
        printf("waiting on accept system call.......\n");
        data_socket = accept(connection_socket,NULL,NULL);
        if(data_socket == -1)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        result = 0;
        for(;;)
        {
            memset(buffer,0,BUFFER_SIZE);
            printf("waiting for client to send data.....\n");
            ret = read(data_socket,buffer,BUFFER_SIZE);
            if(ret == -1)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }
            memcpy(&data,buffer,sizeof(int));//void * memcpy(void *to, const void *from, size_t numBytes);
            if(data == 0)
                break;
            result = result+data;
        }
        /****Send result******/
        memset(buffer,0,BUFFER_SIZE);
        sprintf(buffer,"Result is %d\n",result);
        printf("Sending summation result to client\n");
        ret = write(data_socket,buffer,BUFFER_SIZE);
        if(ret  == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        printf("Result send successfully\n");
        /****Send result******/

        /***Close client socket file descriptor*******/
        close(data_socket);

    }
    /**********main loop for handling connection****************************/

    /************close master socket file descriptor***********************/
    close(connection_socket);
    printf("connection closed....\n");
    exit(EXIT_SUCCESS);
}


