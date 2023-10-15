#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *printhello(void *ptr)
{
    char *message = (char *)ptr;
    printf("%s\n",message);
}

int main()
{
    int rc;
    pthread_t t1;
    char * thread = "Thread_1";
    rc = pthread_create(&t1,NULL,printhello,(void *)thread);
    if(rc)
    {
        printf("Error in thread creation & return code is:%d\n",rc);
        exit(1);
    }
    printf("Thread id of t1 is %ld...\n",t1);
    pthread_exit(NULL);
}
/*******output**************
Thread id of t1 is 140455871153920...
Thread_1
*******output**************/
