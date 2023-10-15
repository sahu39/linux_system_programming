#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter=0;

void *trythis(void *arg)
{
    unsigned long i=0;
    counter += 1;
    char *msg = (char *)arg;
    printf("\n%s\n",msg);
    printf("\nJob %d has started\n ",counter);
    for(i=0;i<(0xFFFFFFFF);i++);
    printf("\nJob %d has finished\n ",counter);
    return NULL;
}

int main()
{
    int i = 0;
    int error;
    char *message = "Thread.........";
    while(i<2)
    {
        error = pthread_create(&tid[i],NULL,&trythis,(void *)message);
  //      if(error != 0)
  //      {
  //          printf("\nthread can't be created:[%s]\n",stderror(error));
 //       }
        i++;
    }
    
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);



    return 0;
}


