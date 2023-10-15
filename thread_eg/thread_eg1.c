#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *print_message_function(void *ptr);
int main()
{
    pthread_t thread1,thread2;
    const char *message1 = "thread 1";
    const char *message2 = "thread 2";
    int iret1,iret2;
    /*Create independent threads*/
    iret1 = pthread_create(&thread1,NULL,print_message_function,(void *)message1);
    if(iret1)
    {
        fprintf(stderr,"Error -pthread_create() return code:%d\n",iret1);
        exit(EXIT_FAILURE);
    }
    iret2 = pthread_create(&thread2,NULL,print_message_function,(void *)message2);
    if(iret2)
    {
        fprintf(stderr,"Error -pthread_create() return code:%d\n",iret2);
        exit(EXIT_FAILURE);
    }
    printf("pthread create() for thread 1 returns:%d\n",iret1);
    printf("pthread create() for thread 2 returns:%d\n",iret2);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    exit(EXIT_SUCCESS);
    

    return 0;
}
void *print_message_function(void *ptr)
{
    char *message;
    message = (char *)ptr;
    printf("%s\n",message);
}
