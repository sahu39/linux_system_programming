//link:https://dzone.com/articles/parallel-tcpip-socket-server-with-multi-threading
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 120
#define ADDR "127.0.0.1"
char buffer[BUFFER_SIZE] = {'\0'};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *socketthread(void *arg)
{
    int ret;
    int newsocket = *(int *)arg;
    pthread_mutex_lock(&lock);
    printf("message receiving from client.......\n");
    ret = recv(newsocket, buffer, BUFFER_SIZE, 0);//ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    if(ret == -1)
    {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    printf("client msg:%s\n",buffer);
    printf("msg received from client\n");

    memset(buffer, 0 , BUFFER_SIZE);
    printf("Sending msg to client......\n");
    printf("Server msg:");
    fgets(buffer, BUFFER_SIZE, stdin);
    //printf("Sending msg to client......\n");
    ret = send(newsocket, buffer, BUFFER_SIZE, 0);//ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    if(ret == -1)
    {
        perror("send");
        exit(EXIT_FAILURE);
    }
    printf("msg sending succesful to client....\n");
    pthread_mutex_unlock(&lock);

    close(newsocket);
    pthread_exit(NULL);

}

int main()
{
    int connection_socket, data_socket;
    int ret;
    struct sockaddr_in myaddr;
    socklen_t addrsize = sizeof(myaddr);
    /******Create master socket file descriptor********/
    printf("Creating master socket............\n");
    connection_socket = socket(AF_INET, SOCK_STREAM, 0); //SOCK_STREAM = TCP/IP(Connection oriented) SOCK_DGRAM = UDP(connectionless)
    if(connection_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Master socket file descriptor created\n");
    /******Create master socket file descriptor********/
    /*struct sockaddr_in {
                 short            sin_family;   // e.g. AF_INET
                 unsigned short   sin_port;     // e.g. htons(3490)
                 struct in_addr   sin_addr;     // see struct in_addr, below
                 char             sin_zero[8];  // zero this if you want to
          };
      
          struct in_addr {
                 unsigned long s_addr;  // load with inet_aton()
          };*/
      

    /*****Create socket credential*********************/
    memset(&myaddr, 0 ,sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(PORT);
    inet_aton(ADDR,&myaddr.sin_addr);
    /*****Create socket credential*********************/

    /*****Bind socket credential to master file descriptor*******/
    printf("bind call started....\n");
    ret = bind(connection_socket, (const struct sockaddr *)&myaddr, sizeof(struct sockaddr_in));
    if(ret == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind call succesful...\n");
    /*****Bind socket credential to master file descriptor*******/

    /*****Listening to no. of clients****************************/
    printf("listen call started.....\n");
    ret = listen(connection_socket,50);
    if(ret == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("listen call succesful\n");
    /*****Listening to no. of clients****************************/
    
    /*****main loop stars here***********************************/
    pthread_t tid[60];
    int i = 0;
    while(1)
    {
        printf("waiting on accept system call......\n");
        //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        data_socket = accept(connection_socket,(struct sockaddr *)&myaddr, &addrsize);
        if(data_socket == -1)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        if(pthread_create(&tid[i], NULL, socketthread, &data_socket) == -1)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
        if(i >= 50)
        {
            i = 0;
            while(i < 50)
            {
                pthread_join(tid[i++],NULL);                
            }
            i = 0;
        }


    }
    close(connection_socket);
    /*****main loop finishes*************************************/

    exit(EXIT_SUCCESS);
}
