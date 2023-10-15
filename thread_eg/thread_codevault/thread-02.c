#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *thread_fun(void *);
sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main()
{
	int res;
	pthread_t t1;
	void *thread_result;
	
	res = sem_init(&bin_sem, 0 , 0);
	if(res != 0)
	{
		perror("semaphore init error");
		exit(EXIT_FAILURE);
	}

	res = pthread_create(&t1, NULL, thread_fun,NULL);
	if(res != 0)
	{
		perror("Thread Creation Failed");
		exit(EXIT_FAILURE);
	}
	printf("Input some text.Enter 'end' to finish\n");
	while(strncmp("end",work_area,3) != 0)
	{
		fgets(work_area,WORK_SIZE,stdin);
		sem_post(&bin_sem);
	}
	printf("Waiting for thread to finish...\n");
	res = pthread_join(t1,&thread_result);
	if(res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread_joined\n");
	sem_destroy(&bin_sem);
	exit(EXIT_SUCCESS);
}

void *thread_fun(void *arg)
{
	sem_wait(&bin_sem);
	while(strncmp("end",work_area,3) != 0)
	{
		printf("You input %ld characters\n",strlen(work_area)-1);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}


