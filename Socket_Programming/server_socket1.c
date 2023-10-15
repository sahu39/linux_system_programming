#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>
#include <netinet/ip.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
int main(int argc,char *argv[])
{
    int sockfd,newsockfd,portno,clilen;
    char buffer[256];
    struct sockaddr_in serv_addr,cli_addr;
    int n;

    /*First call to Socket function*/
    sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("Error Opening Socket");
        exit(1);
    }

    /*Initialize the socket structure*/
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = 5001;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = atoi("127.0.0.1");
    serv_addr.sin_port = htons(portno);         //Host to Network Short

    /* Now bind the host address using bind() call.*/

    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr) )<0)
    {
        perror("Error on binding");
        exit(1);
    }
    /*Now start listening from client*/
    if(listen(sockfd,5)<0)
    {
        perror("error on listening");
        exit(1);
    }
   clilen = sizeof(cli_addr);
   newsockfd = accept (sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if(newsockfd<0)
    {
        perror("error on accepting");
        exit(1);
    }
   /* If connection is established then start communicating */
    printf("Waiting for client request.................\n");
    bzero(buffer,256);
    n = read (newsockfd,buffer,256);
    if(n<0)
    {
        perror("open failed");
        exit(1);
    }
    printf("Message from client:%s\n",buffer);
    /*Write a response to the client*/
    n = write(newsockfd,"I got your message",18);
    if(n<0)
    {
        perror("open failed");
        exit(1);
    }

    return 0;

        
}
