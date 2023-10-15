#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define MY_SOCKET "my_socket"
#define BUFFER_LENGTH 128
#define MAX_CLIENT_SUPPORTS 32

int monitor_fd_set[MAX_CLIENT_SUPPORTS] = {0};
int client_result[MAX_CLIENT_SUPPORTS] = {0};

static void initialize_fd_set(){
    int i;
    for(i = 0;i < MAX_CLIENT_SUPPORTS;i++){
        monitor_fd_set[i] = -1;
    }
}

static void add_to_monitor_fd_set(int skt_fd){
    int i;
    for(i = 0;i < MAX_CLIENT_SUPPORTS; i++){
        if(monitor_fd_set[i] != -1)
            continue;
        monitor_fd_set[i] = skt_fd;
        break;
    }
}

static void remove_from_monitored_fd_set(int skt_fd){
    int i;
    for(i = 0;i < MAX_CLIENT_SUPPORTS;i++){
        if(monitor_fd_set[i] != skt_fd)
            continue;
        monitor_fd_set[i] = -1;
        break;
    }
}

static refresh_fd_set(fd_set *fd_set_ptr){
    FD_ZERO(fd_set_ptr);
    int i = 0;
    for(;i < MAX_CLIENT_SUPPORTS; i++){
        if(monitor_fd_set[i] != -1){
            FD_SET(monitor_fd_set[i],fd_set_ptr);
        }
    }
}

static int get_max_fd(){
    int i = 0;
    int max = -1;
    for(;i < MAX_CLIENT_SUPPORTS;i++){
        if(monitor_fd_set[i] > max)
            max = monitor_fd_set[i];
    }
    return max;
}

int main(){
    int ret;
    int connection_socket;
    int data_socket;
    int result;
    int data;
    char buff[BUFFER_LENGTH];
    fd_set readfds;
    int comm_sock_fd,i;
    struct sockaddr_un name;
    
    initialize_fd_set();
    unlink(MY_SOCKET);

    connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if(connection_socket == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("Master Socket Created\n");

    memset(&name,0,sizeof(struct sockaddr_un));

    name.sun_family = AF_UNIX;
    strncpy(name.sun_path,MY_SOCKET,sizeof(name.sun_path)-1);

    ret = bind(connection_socket,(const struct sockaddr *)&name,sizeof(struct sockaddr_un));
    if(ret == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    ret = listen(connection_socket,20);
    if(ret == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    add_to_monitor_fd_set(connection_socket);

    for(;;){
        refresh_fd_set(&readfds);

        printf("Waiting for select() sys call....\n");

        select(get_max_fd() + 1, &readfds , NULL, NULL, NULL);

        if(FD_ISSET(connection_socket,&readfds)){
            printf("New connction recieved, accept the connection...\n");

            data_socket = accept(connection_socket,NULL,NULL);
            if(data_socket == -1){
                perror("data_socket");
                exit(EXIT_FAILURE);
            }
            
            add_to_monitor_fd_set(data_socket);
        }
        else if(FD_ISSET(0,&readfds)){
            memset(buff,0,BUFFER_LENGTH);
            ret = read(0,buff,BUFFER_LENGTH);
            printf("Input read from console...%s\n",buff);
        }
        else{
            i = 0;
            comm_sock_fd = -1;
            for(;i < MAX_CLIENT_SUPPORTS;i++){
                if(FD_ISSET(monitor_fd_set[i],&readfds)){
                    comm_sock_fd = monitor_fd_set[i];
                    memset(buff,0,BUFFER_LENGTH);
                    printf("Waiting Data from client....\n");
                    ret = read(comm_sock_fd,buff,BUFFER_LENGTH);
                    if(ret == -1){
                        perror("read");
                        exit(EXIT_FAILURE);
                    }
                    memcpy(&data,buff,sizeof(int));

                    if(data == 0){
                        memset(buff,0,BUFFER_LENGTH);
                        sprintf(buff,"Result is : %d\n",client_result[i]);
                        printf("Sending final result back to the client...\n");
                        ret = write(comm_sock_fd,buff,BUFFER_LENGTH);
                        if(ret == -1){
                            perror("write");
                            exit(EXIT_FAILURE);
                        }
                        close(comm_sock_fd);
                        client_result[i] = 0;
                        remove_from_monitored_fd_set(comm_sock_fd);
                        continue;
                    }
                    client_result[i] += data; 
                }
            }
        }

    }
    close(connection_socket);
    remove_from_monitored_fd_set(connection_socket);
    printf("connection closed...\n");

    unlink_socket(MY_SOCKET);
    exit(EXIT_SUCCESS);
}
