#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter=0;
pthread_mutex_t lock;
void *trythis(void *arg)
{
    pthread_mutex_lock(&lock);
    unsigned long i=0;
    counter += 1;
    char *msg = (char *)arg;
    printf("\n%s\n",msg);
    printf("\nJob %d has started\n ",counter);
    for(i=0;i<(0xFFFFFFFF);i++);
    printf("\nJob %d has finished\n ",counter);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    int i = 0;
    int error;
    char *message = "Thread.........";
    if(pthread_mutex_init(&lock,NULL) != 0)
    {
        printf("\nmutex creation failed\n");
        return 1;
    }
    while(i<2)
    {
        error = pthread_create(&tid[i],NULL,&trythis,(void *)message);
        if(error != 0)
        {
          printf("\nthread can't be created:[%s]\n",strerror(error));
        }
        i++;
    }
    
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_mutex_destroy(&lock);


    return 0;
}


