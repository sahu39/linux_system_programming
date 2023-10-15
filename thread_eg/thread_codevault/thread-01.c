#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "my message";
int main()
{
	int res;
	pthread_t thread;
	void *thread_result;
	
	res = pthread_create(&thread, NULL, thread_function,(void *)message);
	if(res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for thread to finish\n");
	res = pthread_join(thread,&thread_result);
	if(res != 0)
	{
		perror("Thread loin failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined and returned %s\n",(char *)thread_result);
	printf("Message is now:%s\n",message);
	exit(EXIT_SUCCESS);
	
}

void *thread_function(void *arg)
{
	printf("Thread function is running, Argument was %s\n",(char *)arg);
	sleep(3);
	strcpy(message,"Bye!");
	pthread_exit("Thank you for the CPU time");
}
