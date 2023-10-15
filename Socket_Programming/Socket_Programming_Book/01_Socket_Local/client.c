#include <sys/types.h>          
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch = 'A';
	
	//1st.Create socket for client
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("Socket");
		exit(EXIT_FAILURE);
	}

	//2nd.Name the socket as agreed with the server
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);

	//3rd.Connect the socket to the server's socket;
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1)
	{
		perror("connect error:");
		exit(EXIT_FAILURE);
	}

	//4th.You can now read and write via sockfd:
	write(sockfd,&ch,1);
	read(sockfd,&ch,1);
	printf("Character from server:%c\n",ch);
	close(sockfd);
	exit(0);
}

