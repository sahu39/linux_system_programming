/*
-This program reads the keyboard (standard input — file descriptor 0) with a timeout of 2.5 seconds.
-It reads the keyboard only when input is ready.
-It’s quite straightforward to extend it to include other descriptors, such as serial lines or pipes and sockets, depending on the application
*/

#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char buffer[128];
	int result, nread;
	fd_set inputs, testfds;
	struct timeval timeout;
	FD_ZERO(&inputs);
	//0--->Standard File Descriptor for Keyboard Input
	//0--->is added to fd_set input
	FD_SET(0,&inputs);
	//Wait for input on stdin for a maximum of 2.5 seconds:
	while(1) {
		testfds = inputs;
		timeout.tv_sec = 2;
		timeout.tv_usec = 500000;
		result = select(FD_SETSIZE, &testfds, (fd_set *)NULL, (fd_set *)NULL,&timeout);		
		switch(result) {
			case 0:
				printf("timeout\n");
				break;
			case -1:
				perror("select");
				exit(1);
			default:
				if(FD_ISSET(0,&testfds)) {
					ioctl(0,FIONREAD,&nread);
					if(nread == 0) {
						printf("keyboard done\n");
						exit(0);
					}
					nread = read(0,buffer,nread);
					buffer[nread] = 0;
					printf("read %d from keyboard: %s", nread, buffer);
				}
				break;
		}
	}
}
	
	
