#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MEM_REG_NAME "/sharedmemory"
#define MSG_SIZE 50

int main(){
	char msg[MSG_SIZE] = "\0";
	int shm_fd;
	/*****Create Shared Memory*********/
	shm_fd = shm_open(MEM_REG_NAME, O_CREAT | O_RDWR | O_TRUNC, 0660);
	if(shm_fd < 0){
		printf("Unable to create shared memory errno:%d\n", errno);
		exit(errno);
	}
	/****Assign size to the shared memory****/
	if((ftruncate(shm_fd, MSG_SIZE)) < 0){
		printf("Can't allocate size for shared memory errno:%d\n",errno);
		exit(errno);
	}
	/****Maping the shared memory region to VAS*****/
	void *shd_mem = mmap(NULL, MSG_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	/***Write into shared memory************/
	memset(shd_mem, 0, MSG_SIZE);
	printf("Enter message to write to shared memory:\n");
	fgets(msg, MSG_SIZE, stdin);
	printf("Message written into shared memory\n");
	
	/****Unmap the shared memory************/
	if((munmap(shd_mem, MSG_SIZE)) < 0){
		printf("munmap falilure errno:%d\n",errno);
		exit(errno);
	}

	/****close the shared memory file fd*****/
	close(shm_fd);
	return 0;
}
