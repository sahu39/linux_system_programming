#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define IPADDR "127.0.0.1"
#define PORT 8080

int main()
{
    struct sockaddr_in ipaddr;
    struct sockaddr_in clientaddr;
    int addrlen = sizeof(clientaddr);
    int connection_socket,data_socket;
    char buffer_send[BUFFER_SIZE];
    char buffer_receive[BUFFER_SIZE];
    int recvlen;
    int sendlen;
    int ret;

    /*****Create server socket*****************/
    printf("Creating Master socket file descriptor......\n");
    connection_socket = socket(AF_INET, SOCK_DGRAM, 0);//SOCK_DGRAM--->UDP socket
    if(connection_socket == 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Master socket file descriptor created\n");

    /*****Create server socket*****************/

    /******Specifying Master Socket credential*****/
    //memset(&ipaddr,0,sizeof(struct sockaddr_in));
    ipaddr.sin_family = AF_INET;
    ipaddr.sin_port = htons(PORT);
    inet_aton(IPADDR, &ipaddr.sin_addr);
    /******Specifying Master Socket credential*****/

    /******bind socket credential to master file descriptor******/
    printf("bind call started.....\n");
    ret = bind(connection_socket, (const struct sockaddr *)&ipaddr, sizeof(struct sockaddr_in));
    if(ret == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind succesful\n");
    /******bind socket credential to master file descriptor******/
#if 0
    /*****listen to no of clients********************************/
    printf("listen system call started...\n");
    ret = listen(connection_socket,20);
    if(ret == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("listen succesful\n");
    /*****listen to no of clients********************************/
#endif    
    /******Main loop********************************************/
    for(;;)
    {
        printf("Waiting for data on port: %d........\n",PORT);
        memset(buffer_send, 0 , BUFFER_SIZE);
        memset(buffer_receive, 0 , BUFFER_SIZE);
        
        /****receving from client**********************/
        printf("server is waiting for receiving message from client........\n");
        recvlen = recvfrom(connection_socket, buffer_receive, BUFFER_SIZE, 0, (struct sockaddr *)&clientaddr, &addrlen );
        if(recvlen < 0)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }
        printf("received %d bytes\n",recvlen);
        if(recvlen > 0)
        {
            buffer_receive[recvlen] = '\0';
            printf("msg received from client:%s\n",buffer_receive);
        }
        
        printf("message received from client\n");
        /******receving from client*******************/

        /******sending packet to client***************/
        printf("sending msg to client.............\n");
        printf("serv_msg:");
        //scanf("%s",buffer_send);
        //gets(buffer_send);
        fgets(buffer_send, BUFFER_SIZE, stdin); 
        sendlen = sendto(connection_socket, buffer_send, BUFFER_SIZE, 0, (struct sockaddr *)&clientaddr, addrlen);
        if(sendlen < 0)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        printf("message sending to client succesful\n");
    }
    close(connection_socket);

    exit(EXIT_SUCCESS);
}
