/****link*****
https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_join.html
pthread_join example
*****link****/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>

typedef struct{
    int *ar;
    long n;
}subarray;

void *incer(void *arg)
{
    long i;
    subarray *s1 = (subarray *)arg;
    for(i=0;i<(s1->n)-1;i++)
    {
        printf("%d\n",(s1->ar[i])++);
    }
}

int main()
{
    int ar[] = {1,2,3,4,5,6,7,8,9,10};
    pthread_t th[2];
    subarray ar1,ar2;
    int rc;

    ar1.ar = &ar[0];
    ar1.n  = 10;

    rc = pthread_create(&th[0],NULL,incer,(void *)&ar1);
    if(rc != 0)
    {
        perror("thread error:");
        exit(1);
    }

    ar2.ar = &ar[5];
    ar2.n  = 10;
    rc = pthread_create(&th[0],NULL,incer,(void *)&ar2);
    if(rc != 0)
    {
        perror("thread error:");
        exit(1);
    }
 
    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    pthread_exit(NULL);
    return 0;
}
