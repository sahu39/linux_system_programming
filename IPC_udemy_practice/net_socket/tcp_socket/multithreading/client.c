#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <error.h>
#include <arpa/inet.h>

#define ADDR "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 120

int main()
{
    struct sockaddr_in servaddr;
    int data_socket;
    char buffer[BUFFER_SIZE];
    int ret;
    //socklen_t servaddlen = sizeof(servaddr);

    /***Create data/client socket******/
    printf("Creating client socket.....\n");
    data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(data_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("client socket created successfully");
    /***Create data/client socket******/

    /***create client credential******/
    memset(&servaddr, 0 , sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_aton(ADDR, &servaddr.sin_addr);
    /***create client credential******/

    /***connect system call to unblock the accept system call***/
    printf("connecting to server......\n");
    ret = connect(data_socket, (const struct sockaddr *)&servaddr, sizeof(struct sockaddr_in));
    if(ret == -1)
    {
        perror("connection");
        exit(EXIT_FAILURE);
    }
    printf("connection succesful to server\n");
    while(1)
    {
        printf("Sending msg to server....\n");
        printf("Enter msg to server:");
        fgets(buffer, sizeof(buffer), stdin);
        ret = send(data_socket, buffer, BUFFER_SIZE, 0);
        if(ret == -1)
        {
            perror("send");
            exit(EXIT_FAILURE);
        }
        printf("msg send to server succesfully\n");

        printf("receiving msg from server.....\n");
        ret = recv(data_socket, buffer, BUFFER_SIZE, 0);
        if(ret == -1)
        {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        printf("msg receiveed from server succesful\n");
    }
    close(data_socket);
    exit(EXIT_SUCCESS);
}

