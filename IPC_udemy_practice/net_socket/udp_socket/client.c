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
    //struct sockaddr_in serveraddr;
    int addrlen = sizeof(ipaddr);
    int connection_socket,data_socket;
    char buffer_send[BUFFER_SIZE];
    char buffer_receive[BUFFER_SIZE];
    int recvlen;
    int sendlen;
    int ret;

    /*****Create client socket*****************/
    printf("Creating client socket file descriptor......\n");
    data_socket = socket(AF_INET, SOCK_DGRAM, 0);//SOCK_DGRAM--->UDP socket
    if(connection_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Client socket file descriptor created\n");

    /*****Create client socket*****************/

    /******Specifying client Socket credential*****/
    memset(&ipaddr,0,sizeof(struct sockaddr_in));
    ipaddr.sin_family = AF_INET;
    ipaddr.sin_port = htons(PORT);
    inet_aton(IPADDR, &ipaddr.sin_addr);
#if 0    
    /******Specifying Master Socket credential*****/

    /******bind:wq socket credential to master file descriptor******/
    printf("bind call started.....\n");
    ret = bind(data_socket, (const struct sockaddr *)&ipaddr, sizeof(struct sockaddr_in));
    if(ret == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind succesful\n");
    /******connect socket credential to master file descriptor******/

    /*****listen to no of clients********************************/
    printf("listen system call started...\n");
    ret = listen(data_socket,20);
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
        //printf("Waiting on port:%d\n",PORT);
        memset(buffer_send, 0 , BUFFER_SIZE);
        memset(buffer_receive, 0 , BUFFER_SIZE);
        /******sending packet to server***************/
        printf("sending msg to server.............\n");
        printf("client_msg:");
        fgets(buffer_send, sizeof(buffer_send), stdin);
        //scanf("%s",buffer_send);
        sendlen = sendto(data_socket, buffer_send, BUFFER_SIZE, 0, (struct sockaddr *)&ipaddr, addrlen);
        if(sendlen == -1)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        printf("message sending to server succesful\n");
        
        
        /****receving from server**********************/
        printf("client is waiting for receiving message from server........\n");
        recvlen = recvfrom(data_socket, buffer_receive, BUFFER_SIZE, 0, (struct sockaddr *)&ipaddr, &addrlen );
        if(recvlen < 0)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }
        printf("received %d bytes\n",recvlen);
        if(recvlen > 0)
        {
            buffer_receive[recvlen] = '\0';
            printf("msg received from server:%s\n",buffer_receive);
        }
        
        printf("message received from server\n");
        /******receving from server*******************/
#if 0
        /******sending packet to client***************/
        printf("sending msg to client.............\n");
        printf("serv_msg:");
        scanf("%s",buffer_send);
        sendlen = sendto(connection_socket, buffer_send, BUFFER_SIZE, 0, (struct sockaddr *)&clientaddr, addrlen);
        if(sendlen < 0)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        printf("message sending to client succesful\n");
#endif
    }
    close(data_socket);

    exit(EXIT_SUCCESS);
}
